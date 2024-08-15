import unittest
import dbAPI
import sqlite3
import os

class TestAddProduct(unittest.TestCase):
    def setUp(self):
        if os.path.exists('test.db'):
            os.remove('test.db')
        dbAPI.create('test.db')
        dbAPI.fill('test.db')

    def tearDown(self):
        try:
            os.remove('test.db')
        except OSError:
            pass

    def test_addProduct_name(self):
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', '', 100.0, 1, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', None, 100.0, 1, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 100, 100.0, 1, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 200, 100.0, 1, 'Test Product')

    def test_addProduct_description(self):
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 1, '')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 1, None)
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 1, 100)
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 1, -100)

    def test_addProduct_price(self):
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', -100.0, 1, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', '100.0', 1, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', '', 1, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', -100, 1, 'Test Product')

    def test_addProduct_category(self):
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 314, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 4, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, 6, 'Test Product')
        with self.assertRaises(ValueError):
            dbAPI.addProduct('test.db', 'Test', 100.0, None, 'Test Product')

    def test_addProduct_success(self):
        dbAPI.addProduct('test.db', 'Test Product', 25.0, 1, 'Description')
        conn = sqlite3.connect('test.db')
        c = conn.cursor()
        c.execute("SELECT * FROM Product WHERE Name = 'Test Product'")
        product = c.fetchone()
        self.assertIsNotNone(product)
        self.assertEqual(product[1], 'Test Product')
        self.assertEqual(product[2], 25.0)
        self.assertEqual(product[3], 1)
        self.assertEqual(product[4], 'Description')
        conn.close()

if __name__ == "__main__":
    unittest.main()