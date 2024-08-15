//Tests add recipe, search, and JSON methods

const request = require('supertest');
const { expect } = require('chai');
const app = require('./index');
const db = require('./database');

let server;

describe('Recipe Genie API', () => {
    before((done) => {
        process.env.PORT = 3309;  // Set a different port for testing
        server = app.listen(process.env.PORT, (err) => {
            if (err) return done(err);
            db.run('DELETE FROM Users', () => {
                db.run('DELETE FROM Recipes', done);
            }); // Clear Users and Recipes tables before running tests
        });
    });

    after((done) => {
        server.close(done);
    });

    it('should create a new user', (done) => {
        request(app)
            .post('/users')
            .send({ username: 'testuser', password: 'password' })
            .expect(201)
            .end((err, res) => {
                if (err) return done(err);
                expect(res.body).to.have.property('id');
                done();
            });
    });

    it('should add a new recipe', (done) => {
        request(app)
            .post('/users')
            .send({ username: 'recipeuser', password: 'password' })
            .end((err, res) => {
                if (err) return done(err);
                const userId = res.body.id;
                request(app)
                    .post('/add-recipe')
                    .send({ user_id: userId, ingredients: 'tomato, basil', result: 'Tomato Basil Soup' })
                    .expect(201)
                    .end((err, res) => {
                        if (err) return done(err);
                        expect(res.body).to.have.property('id');
                        done();
                    });
            });
    });

    it('should search for a recipe', (done) => {
        request(app)
            .post('/users')
            .send({ username: 'searchuser', password: 'password' })
            .end((err, res) => {
                if (err) return done(err);
                const userId = res.body.id;
                request(app)
                    .post('/add-recipe')
                    .send({ user_id: userId, ingredients: 'tomato, basil', result: 'Tomato Basil Soup' })
                    .end(() => {
                        request(app)
                            .post('/search-recipe')
                            .send({ user_id: userId, ingredients: 'tomato, basil' })
                            .expect(200)
                            .end((err, res) => {
                                if (err) return done(err);
                                expect(res.body.exists).to.be.true;
                                expect(res.body.recipe).to.have.property('result').equal('Tomato Basil Soup');
                                done();
                            });
                    });
            });
    });

    it('should return recipe JSON', (done) => {
        request(app)
            .post('/users')
            .send({ username: 'jsonuser', password: 'password' })
            .end((err, res) => {
                if (err) return done(err);
                const userId = res.body.id;
                request(app)
                    .post('/add-recipe')
                    .send({ user_id: userId, ingredients: 'tomato, basil', result: 'Tomato Basil Soup' })
                    .end(() => {
                        request(app)
                            .post('/get-recipe-json')
                            .send({ user_id: userId, ingredients: 'tomato, basil' })
                            .expect(200)
                            .end((err, res) => {
                                if (err) return done(err);
                                expect(res.body).to.have.property('recipe').equal('Tomato Basil Soup');
                                done();
                            });
                    });
            });
    });

    it('should add or get a recipe', (done) => {
    request(app)
        .post('/users')
        .send({ username: 'addorgetuser', password: 'password' })
        .end((err, res) => {
            if (err) return done(err);
            const userId = res.body.id;
            request(app)
                .post('/add-or-get-recipe')
                .send({ user_id: userId, ingredients: 'tomato, basil', result: 'Tomato Basil Soup' })
                .expect(201)  // Adjust expected status code if necessary
                .end((err, res) => {
                    if (err) return done(err);
                    // Adjust expectation based on actual response
                    expect(res.body).to.have.property('id'); // Assuming it returns an id
                    done();
                });
        });
});


});
