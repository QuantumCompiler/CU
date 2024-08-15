import sqlite3
import dbAPI
import os

''' test_category - Function to test the Category table
        Input:
            None
        Algorithm:
            * Delete the database if it exists
            * Create the database
            * Fill the database with sample data
            * Connect to the database
            * Query the Category table
            * Check the number of rows in the Category table
        Output:
            Prints the number of rows in the Store_Product table if the test fails
'''
def test_category():
    if os.path.exists('test.db'):
        os.remove('test.db')
    dbAPI.create('test.db')
    dbAPI.fill('test.db')
    conn = sqlite3.connect('test.db')
    c = conn.cursor()
    c.execute("SELECT * FROM Category")
    categories = c.fetchall()
    assert len(categories) == 3, "Expected 3 categories, got %d" % len(categories)
    conn.close()

''' test_store - Function to test the Store table
        Input:
            None
        Algorithm:
            * Delete the database if it exists
            * Create the database
            * Fill the database with sample data
            * Connect to the database
            * Query the Store table
            * Check the number of rows in the Store table
        Output:
            Prints the number of rows in the Store_Product table if the test fails
'''
def test_store():
    if os.path.exists('test.db'):
        os.remove('test.db')
    dbAPI.create('test.db')
    dbAPI.fill('test.db')
    conn = sqlite3.connect('test.db')
    c = conn.cursor()
    c.execute("SELECT * FROM Store")
    stores = c.fetchall()
    assert len(stores) == 3, "Expected 3 stores, got %d" % len(stores)
    conn.close()

''' test_product - Function to test the Product table
        Input:
            None
        Algorithm:
            * Delete the database if it exists
            * Create the database
            * Fill the database with sample data
            * Connect to the database
            * Query the Product table
            * Check the number of rows in the Product table
        Output:
            Prints the number of rows in the Store_Product table if the test fails
'''
def test_product():
    if os.path.exists('test.db'):
        os.remove('test.db')
    dbAPI.create('test.db')
    dbAPI.fill('test.db')
    conn = sqlite3.connect('test.db')
    c = conn.cursor()
    c.execute("SELECT * FROM Product")
    products = c.fetchall()
    assert len(products) == 3, "Expected 3 products, got %d" % len(products)
    conn.close()

''' test_store_product - Function to test the Store_Product table
        Input:
            None
        Algorithm:
            * Delete the database if it exists
            * Create the database
            * Fill the database with sample data
            * Connect to the database
            * Query the Store_Product table
            * Check the number of rows in the Store_Product table
        Output:
            Prints the number of rows in the Store_Product table if the test fails
'''
def test_store_product():
    if os.path.exists('test.db'):
        os.remove('test.db')
    dbAPI.create('test.db')
    dbAPI.fill('test.db')
    conn = sqlite3.connect('test.db')
    c = conn.cursor()
    c.execute("SELECT * FROM Store_Product")
    store_products = c.fetchall()
    assert len(store_products) == 3, "Expected 3 store products, got %d" % len(store_products)
    conn.close()

''' __main__ - Function to test the dbAPI.py functions
        Input:
            None
        Algorithm:
            * Call the test_category function
            * Call the test_product function
            * Call the test_store function
            * Call the test_store_product function
            * Print "All tests passed!" if all tests pass
        Output:
            Prints the number of rows in the Store_Product table if the test fails
'''
if __name__ == "__main__":
    test_category()
    test_product()
    test_store()
    test_store_product()
    print("All tests passed!")
    if (os.path.exists('test.db')):
        os.remove('test.db')