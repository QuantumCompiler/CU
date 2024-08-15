//Connects the SQL database to Node.Js

// Import sqlite3 module and enable verbose mode for debugging
const sqlite3 = require('sqlite3').verbose();
const fs = require('fs');
const path = require('path');

// Path to the SQLite database file
const dbFile = path.join(__dirname, './recipe_genie.db');

// Path to the SQL schema file
const schemaFile = path.join(__dirname, 'create_database.sql');

// Read the SQL schema file
const schema = fs.readFileSync(schemaFile, 'utf8');

// Connect to the database
let db = new sqlite3.Database('./recipe_genie.db', (err) => {
    if (err) {
        console.error(err.message);
    }
    console.log('Connected to the recipe_genie database.');
});

// Execute the schema
db.exec(schema, (err) => {
    if (err) {
        return console.error('Error executing schema:', err.message);
    }
    console.log('Database schema created successfully.');
});

// Export the database connection
module.exports = db;
