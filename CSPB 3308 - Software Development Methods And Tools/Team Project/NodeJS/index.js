const express = require('express');
const cors = require('cors');
const bcrypt = require('bcrypt');

// Imports the database connection
const db = require('./database'); 

const app = express();
//The port variable 3000 will change as we run on a a real server 
const port = process.env.PORT || 3308;

// Middleware to parse JSON requests
app.use(express.json());
app.use(cors());

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
//
//  Generic Functions
//
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

// Define a simple route to display the header
app.get('/', (req, res) => {
    res.send(`
        <html>
            <head>
                <title>NodeJS Server</title>
            </head>
            <body>
                <h1>NodeJS Server</h1>
            </body>
        </html>
    `);
});

app.listen(port, async () => {
    console.log(`Server running on port ${port}`);
});

// Handle POST request from React
app.post("/post", (req, res) => {
    console.log("Connected to React!!!!!");
    console.log("Data received:", req.body);
    // res.json({ message: "Data received successfully" });
    res.send("Hello from Node!!!");
});

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
//
//  User Management Functions
//
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 


// Route to test the database connection by fetching all users. Tests SQLite and Node.JS.connection 
app.get('/test-db', (req, res) => {
    console.log('GET /test-db request received');
    db.all(`SELECT id, username FROM Users`, [], (err, rows) => {
        if (err) {
            console.error('Database query error:', err.message);
            return res.status(500).json({ error: err.message });
        }
        console.log('Database query successful:', rows);
        res.json({ users: rows });
    });
});

app.post('/users', async (req, res) => {
    const { username, password } = req.body;
    console.log('POST /users request received with data:');
    try {
        const hashedPassword = await bcrypt.hash(password, 10);
        db.run(`INSERT INTO Users (username, password) VALUES (?, ?)`, [username, hashedPassword], function(err) {
            if (err) {
                console.error('Database insert error:', err.message);
                return res.status(500).json({ error: err.message });
            }
            console.log('User inserted with ID:', this.lastID);
            res.status(201).json({ id: this.lastID });
        });
    } catch (error) {
        console.error('Error hashing password:', error.message);
        res.status(500).json({ error: error.message });
    }
});


// Example route to get all users
app.get('/users', (req, res) => {
    console.log('GET /users request received');
    db.all(`SELECT id, username FROM Users`, [], (err, rows) => {
        if (err) {
            console.error('Database query error:', err.message);
            return res.status(500).json({ error: err.message });
        }
        console.log('Database query successful:', rows);
        res.json({ users: rows });
    });
});

// Recieve Username and Password from React
// Requires input in format 

async function isCorrectLogin(username, password) {
    console.log(`Checking login for user: ${username}`);

    return new Promise((resolve, reject) => {
        db.get(`SELECT password FROM Users WHERE username = ?`, [username], async (err, row) => {
            if (err) {
                console.error('Database query error:', err.message);
                return reject(err);
            }
            if (!row) {
                console.log('Username not found:', username);
                return resolve(false); // Username not found
            }
            try {
                const match = await bcrypt.compare(password, row.password);
                console.log(`Password match for user ${username}:`, match);
                resolve(match);
            } catch (error) {
                console.error('Error comparing passwords:', error.message);
                reject(error);
            }
        });
    });
}

app.get("/login", async (req, res) => {
    const { username, password } = req.query; // Use req.query for GET request
    console.log("Username: ", username)
    console.log("Password: ", password)
    try {
        const isLoggedIn = await isCorrectLogin(username, password);
        res.status(200).json({ isLoggedIn });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
//
//  Recipe Functions
//
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

// Add Recipe Method
app.post('/add-recipe', (req, res) => {
    const { user_id, ingredients, result } = req.body;
    db.run(`INSERT INTO Recipes (user_id, ingredients, result) VALUES (?, ?, ?)`, [user_id, ingredients, result], function(err) {
        if (err) {
            console.error(err);  // Log the error
            return res.status(500).json({ error: err.message });
        }
        res.status(201).json({ id: this.lastID });
    });
});

// Delete all recipes
app.post('/delete-all-recipes', (req, res) => {
    const { user_id } = req.body;
    db.run(`DELETE FROM Recipes WHERE user_id = ?`, [user_id], function(err) {
        if (err) {
            console.error(err);
            return res.status(500).json({ error: err.message });
        }
        if (this.changes > 0) {
            res.json({ success: true, message: `${this.changes} recipes deleted.` });
        } else {
            res.json({ success: false, message: 'No recipes found to delete.' });
        }
    });
});

// Search Recipe Method
app.post('/search-recipe', (req, res) => {
    const { user_id, ingredients } = req.body;
    db.get(`SELECT * FROM Recipes WHERE user_id = ? AND ingredients = ?`, [user_id, ingredients], (err, row) => {
        if (err) {
            console.error(err);  // Log the error
            return res.status(500).json({ error: err.message });
        }
        if (row) {
            res.json({ exists: true, recipe: row });
        } else {
            res.json({ exists: false, recipe: 'DNE' });
        }
    });
});

// Grab all recipes
app.post('/grab-all-recipes', (req, res) => {
    const { user_id } = req.body;
    db.all(`SELECT * FROM Recipes WHERE user_id = ?`, [user_id], (err, rows) => {
        if (err) {
            console.error(err);
            return res.status(500).json({ error: err.message });
        }
        if (rows.length > 0) {
            res.json({ notEmpty: true, recipes: rows });
        } else {
            res.json({ notEmpty: false, recipes: [] });
        }
    });
});

// Return JSON String Method
app.post('/get-recipe-json', (req, res) => {
    const { user_id, ingredients } = req.body;
    db.get(`SELECT result FROM Recipes WHERE user_id = ? AND ingredients = ?`, [user_id, ingredients], (err, row) => {
        if (err) {
            console.error(err);  // Log the error
            return res.status(500).json({ error: err.message });
        }
        if (row) {
            res.json({ recipe: row.result });
        } else {
            res.status(404).json({ error: 'Recipe not found' });
        }
    });
});

// Combined Method
app.post('/add-or-get-recipe', (req, res) => {
    const { user_id, ingredients, result } = req.body;
    db.get(`SELECT result FROM Recipes WHERE user_id = ? AND ingredients = ?`, [user_id, ingredients], (err, row) => {
        if (err) {
            console.error(err);  // Log the error
            return res.status(500).json({ error: err.message });
        }
        if (row) {
            res.json({ recipe: row.result });
        } else {
            db.run(`INSERT INTO Recipes (user_id, ingredients, result) VALUES (?, ?, ?)`, [user_id, ingredients, result], function(err) {
                if (err) {
                    console.error(err);  // Log the error
                    return res.status(500).json({ error: err.message });
                }
                res.status(201).json({ id: this.lastID });
            });
        }
    });
});