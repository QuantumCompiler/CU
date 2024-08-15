//We can use this in our project, it's from professor Nath. Just need the usernmane and password parts. Very helpful for user sessions

// ----------------------------------   DEPENDENCIES  ----------------------------------------------
const express = require('express');
const app = express();
const handlebars = require('express-handlebars');
const Handlebars = require('handlebars');
const path = require('path');
const pgp = require('pg-promise')();
const bodyParser = require('body-parser');
const session = require('express-session');

// -------------------------------------  APP CONFIG   ----------------------------------------------

// create `ExpressHandlebars` instance and configure the layouts and partials dir.
const hbs = handlebars.create({
  extname: 'hbs',
  layoutsDir: __dirname + '/views/layouts',
  partialsDir: __dirname + '/views/partials',
});

// Register `hbs` as our view engine using its bound `engine()` function.
app.engine('hbs', hbs.engine);
app.set('view engine', 'hbs');
app.set('views', path.join(__dirname, 'views'));

//creating session object lines 24-32
app.use(bodyParser.json());
// set Session
app.use(
  session({
    secret: 'XASDASDA',
    saveUninitialized: true,
    resave: true,
  })
);
app.use(
  bodyParser.urlencoded({
    extended: true,
  })
);

// -------------------------------------  DB CONFIG AND CONNECT   ---------------------------------------
const dbConfig = {
  host: 'db',
  port: 5432,
  database: process.env.POSTGRES_DB,
  user: process.env.POSTGRES_USER,
  password: process.env.POSTGRES_PASSWORD,
};
const db = pgp(dbConfig);

// db test
db.connect()
  .then(obj => {
    // Can check the server version here (pg-promise v10.1.0+):
    console.log('Database connection successful');
    obj.done(); // success, release the connection;
  })
  .catch(error => {
    console.log('ERROR', error.message || error);
  });

// -------------------------------------  ROUTES for login.hbs   ----------------------------------------------
const user = {
  student_id: undefined,
  username: undefined,
  first_name: undefined,
  last_name: undefined,
  email: undefined,
  year: undefined,
  major: undefined,
  degree: undefined,
};

const student_courses = `
  SELECT DISTINCT
    courses.course_id,
    courses.course_name,
    courses.credit_hours,
    students.student_id = $1 AS "taken"
  FROM
    courses
    JOIN student_courses ON courses.course_id = student_courses.course_id
    JOIN students ON student_courses.student_id = students.student_id
  WHERE students.student_id = $1
  ORDER BY courses.course_id ASC;`;

const all_courses = `
  SELECT
    courses.course_id,
    courses.course_name,
    courses.credit_hours,
    CASE
    WHEN
    courses.course_id IN (
      SELECT student_courses.course_id
      FROM student_courses
      WHERE student_courses.student_id = $1
    ) THEN TRUE
    ELSE FALSE
    END
    AS "taken"
  FROM
    courses
  ORDER BY courses.course_id ASC;
  `;

app.get('/login', (req, res) => {
  res.render('pages/login');
});

// Login submission
app.post('/login', (req, res) => {
  const email = req.body.email;
  const username = req.body.username;
  const query = 'select * from students where students.email = $1 LIMIT 1';
  const values = [email];

  // get the student_id based on the emailid
  db.one(query, values)
    .then(data => {
      user.student_id = data.student_id;
      user.username = username;
      user.first_name = data.first_name;
      user.last_name = data.last_name;
      user.email = data.email;
      user.year = data.year;
      user.major = data.major;
      user.degree = data.degree;

      req.session.user = user;
      req.session.save();

      res.redirect('/');
    })
    .catch(err => {
      console.log(err);
      res.redirect('/login');
    });
});

// Authentication middleware.
const auth = (req, res, next) => {
  if (!req.session.user) {
    return res.redirect('/login');
  }
  next();
};

app.use(auth);

// -------------------------------------  ROUTES for home.hbs   ----------------------------------------------

app.get('/', (req, res) => {
  res.render('pages/home', {
    username: req.session.user.username,
    first_name: req.session.user.first_name,
    last_name: req.session.user.last_name,
    email: req.session.user.email,
    year: req.session.user.year,
    major: req.session.user.major,
    degree: req.session.user.degree,
  });
});


// -------------------------------------  ROUTES for courses.hbs   ----------------------------------------------

app.get('/courses', (req, res) => {
  const taken = req.query.taken;
  // Query to list all the courses taken by a student

  db.any(taken ? student_courses : all_courses, [req.session.user.student_id])
    .then(courses => {
      console.log(courses)
      res.render('pages/courses', {
        email: user.email,
        courses,
        action: req.query.taken ? 'delete' : 'add',
      });
    })
    .catch(err => {
      res.render('pages/courses', {
        courses: [],
        email: user.email,
        error: true,
        message: err.message,
      });
    });
});

app.post('/courses/add', (req, res) => {
  const course_id = parseInt(req.body.course_id);
  db.tx(async t => {
    // This transaction will continue iff the student has satisfied all the
    // required prerequisites.
    const {num_prerequisites} = await t.one(
      `SELECT
        num_prerequisites
       FROM
        course_prerequisite_count
       WHERE
        course_id = $1`,
      [course_id]
    );

    if (num_prerequisites > 0) {
      // This returns [] if the student has not taken any prerequisites for
      // the course.
      const [row] = await t.any(
        `SELECT
              num_prerequisites_satisfied
            FROM
              student_prerequisite_count
            WHERE
              course_id = $1
              AND student_id = $2`,
        [course_id, req.session.user.student_id]
      );

      if (!row || row.num_prerequisites_satisfied < num_prerequisites) {
        throw new Error(`Prerequisites not satisfied for course ${course_id}`);
      }
    }

    // There are either no prerequisites, or all have been taken.
    await t.none(
      'INSERT INTO student_courses(course_id, student_id) VALUES ($1, $2);',
      [course_id, req.session.user.student_id]
    );
    // TODO(corypaik): Update with query from /courses.
    return t.any(all_courses, [req.session.user.student_id]);
  })
    .then(courses => {
      //console.info(courses);
      res.render('pages/courses', {
        email: user.email,
        courses,
        message: `Successfully added course ${req.body.course_id}`,
      });
    })
    .catch(err => {
      res.render('pages/courses', {
        email: user.email,
        courses: [],
        error: true,
        message: err.message,
      });
    });
});

// -------------------------------------  ROUTES for logout.hbs   ----------------------------------------------

app.get('/logout', (req, res) => {
  req.session.destroy();
  res.render('pages/logout');
});

// -------------------------------------  START THE SERVER   ----------------------------------------------

app.listen(8080);
console.log('Server is listening on port 3000');
