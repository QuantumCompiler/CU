from flask import Flask
import sqlite3

app = Flask(__name__)

DB_PATH = 'BasketballBase.db'

def connect_db():
    try:
        return sqlite3.connect(DB_PATH)
    except sqlite3.Error as e:
        return None

@app.route('/')
def hello_world():
    return 'Hello World from Taylor Larrechea in 3308'

@app.route('/db_test')
def db_test():
    try:
        conn = connect_db()
        if conn is None:
            return "Database connection failed!"
        conn.execute('SELECT 1')
        conn.close()
        return "Database connection successful!"
    except Exception as e:
        return f"Error: {str(e)}"

@app.route('/db_create')
def db_create():
    try:
        conn = connect_db()
        if conn is None:
            return "Database connection failed!"
        conn.execute('''
            CREATE TABLE IF NOT EXISTS Basketball(
                First TEXT,
                Last TEXT,
                City TEXT,
                Name TEXT,
                Number INTEGER
            );
        ''')
        conn.commit()
        conn.close()
        return "Basketball table created successfully!"
    except Exception as e:
        return f"Error: {str(e)}"

@app.route('/db_insert')
def db_insert():
    try:
        conn = connect_db()
        if conn is None:
            return "Database connection failed!"
        conn.execute('''
            INSERT INTO Basketball (First, Last, City, Name, Number)
            VALUES
            ('Jayson', 'Tatum', 'Boston', 'Celtics', 0),
            ('Stephen', 'Curry', 'San Francisco', 'Warriors', 30),
            ('Nikola', 'Jokic', 'Denver', 'Nuggets', 15),
            ('Kawhi', 'Leonard', 'Los Angeles', 'Clippers', 2);
        ''')
        conn.commit()
        conn.close()
        return "Basketball table populated successfully!"
    except Exception as e:
        return f"Error: {str(e)}"

@app.route('/db_select')
def db_select():
    try:
        conn = connect_db()
        if conn is None:
            return "Database connection failed!"
        cur = conn.cursor()
        cur.execute("SELECT * FROM Basketball;")
        records = cur.fetchall()
        conn.close()

        response = "<h1>Basketball Players</h1><table border='1'>"
        response += "<tr><th>First</th><th>Last</th><th>City</th><th>Name</th><th>Number</th></tr>"
        for row in records:
            response += "<tr>"
            for column in row:
                response += f"<td>{column}</td>"
            response += "</tr>"
        response += "</table>"
        return response
    except Exception as e:
        return f"Error: {str(e)}"

@app.route('/db_drop')
def db_drop():
    try:
        conn = connect_db()
        if conn is None:
            return "Database connection failed!"
        conn.execute("DROP TABLE IF EXISTS Basketball;")
        conn.commit()
        conn.close()
        return "Basketball table dropped successfully!"
    except Exception as e:
        return f"Error: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)