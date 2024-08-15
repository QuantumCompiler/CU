import sqlite3

''' create - Function to create the database schema
        Input:
            db_filename - the filename of the database
        Algorithm:
            * Connect to the database
            * Create the Category table
                idCategory - The primary key for the table that represents the category
                Name - The name of the category
                Description - A description of the category
            * Create the Store table
                idStore - The primary key for the table that represents the store
                SquareFeet - The square footage of the store
                StoreType - The type of store
                LocationType - The type of location
                Address - The address of the store
                City - The city of the store
                StoreState - The state of the store
                ZipCode - The zip code of the store
            * Create the Product table
                idProduct - The primary key for the table that represents the product
                Name - The name of the product
                Price - The price of the product
                CategoryID - The foreign key to the Category table
                Description - The description of the product
                CategoryID is a foreign key to the Category table
            * Create the Store_Product table
                ProductID - The foreign key to the Product table
                StoreID - The foreign key to the Store table
                Quantity - The quantity of the product in the store
                ProductID and StoreID are the primary key for the table
                ProductID is a foreign key to the Product table
                StoreID is a foreign key to the Store table
        Output:
            Creates the database schema mentioned above
'''
def create(db_filename):
    conn = sqlite3.connect(db_filename)
    c = conn.cursor()
    # Create the category table
    c.execute('''CREATE TABLE Category (
        idCategory INTEGER PRIMARY KEY AUTOINCREMENT,
        Name VARCHAR(45) NOT NULL,
        Description VARCHAR(90)
    )
    ''')
    # Create the store table
    c.execute('''CREATE TABLE Store (
        idStore INTEGER PRIMARY KEY AUTOINCREMENT,
        SquareFeet INTEGER,
        StoreType VARCHAR(45),
        LocationType CHAR(1),
        Address VARCHAR(45),
        City VARCHAR(45),
        StoreState VARCHAR(45),
        ZipCode VARCHAR(10)
    )
    ''')
    # Create the product table
    c.execute('''CREATE TABLE Product (
        idProduct INTEGER PRIMARY KEY AUTOINCREMENT,
        Name VARCHAR(30) NOT NULL,
        Price DECIMAL NOT NULL,
        CategoryID INTEGER,
        Description VARCHAR(90),
        FOREIGN KEY (CategoryID) REFERENCES Category (idCategory)
    )
    ''')
    # Create the Store_Product table
    c.execute('''CREATE TABLE Store_Product (
        ProductID INTEGER,
        StoreID INTEGER,
        Quantity INTEGER,
        PRIMARY KEY (ProductID, StoreID),
        FOREIGN KEY (ProductID) REFERENCES Product (idProduct),
        FOREIGN KEY (StoreID) REFERENCES Store (idStore)
    )
    ''')
    conn.commit()
    conn.close()

''' fill - Function to fill the database with sample data
        Input:
            db_filename - the filename of the database
        Algorithm:
            * Connect to the database
            * Insert sample data into the Category table
            * Insert sample data into the Store table
            * Insert sample data into the Product table
            * Insert sample data into the Store_Product table
        Output:
            Fills the database with sample data
'''
def fill(db_filename):
    conn = sqlite3.connect(db_filename)
    c = conn.cursor()
    # Insert sample data into the Category table
    c.executemany('''INSERT INTO Category (Name, Description) VALUES (?, ?)''', [
        ('Electronics', 'Devices, gadgets, and other useful items.'),
        ('Clothing', 'Apparel and accessories.'),
        ('Books', 'Printed and digital reading materials.')
    ])
    # Insert sample data into the Store table
    c.executemany('''INSERT INTO Store (SquareFeet, StoreType, LocationType, Address, City, StoreState, ZipCode) VALUES (?, ?, ?, ?, ?, ?, ?)''', [
        (25000, 'Retail', 'A', '12345 Main St', 'Boulder', 'CO', '80309'),
        (20000, 'Retail', 'B', '456 North Ave', 'Grand Junction', 'CO', '81501'),
        (10000, 'Book Store', 'C', '789 Railroad', 'Rifle', 'CO', '81650')
    ])
    # Insert sample data into the Product table
    c.executemany('''INSERT INTO Product (Name, Price, CategoryID, Description) VALUES (?, ?, (SELECT idCategory FROM Category WHERE Name = ?), ?)''', [
        ('MacBook Pro', 1999.99, 'Electronics', 'The best laptop available.'),
        ('Camiseta', 29.99, 'Clothing', 'Un camiesta roja bonita.'),
        ('Harry Potter And The Goblet Of Fire', 19.99, 'Books', 'Fourth installment into the Harry Potter series.')
    ])
    # Insert sample data into the Store_Product table
    c.executemany('''INSERT INTO Store_Product (ProductID, StoreID, Quantity) VALUES (?, ?, ?)''', [
        (1, 1, 10),
        (2, 2, 20),
        (3, 3, 20)
    ])
    conn.commit()
    conn.close()

''' addProduct - Function to add a product to the database
        Input:
            db_filename - the filename of the database
            productName - the name of the product
            price - the price of the product
            categoryID - the category ID of the product
            description - the description of the product
        Algorithm:
            * Connect to the database
            * Check if the product name is valid
            * Check if the description is valid
            * Check if the price is valid
            * Check if the category ID is valid
            * Insert the product into the Product table
        Output:
            Adds the product to the database
'''
def addProduct(db_filename, productName, price, categoryID, description):
    if not isinstance(productName, str) or not productName:
        raise ValueError("Product name must be a non-empty string")
    if not isinstance(description, str) or not description:
        raise ValueError("Description must be a non-empty string")
    if not isinstance(price, (int, float)) or price < 0:
        raise ValueError("Price must be a non-negative number")
    conn = sqlite3.connect(db_filename)
    c = conn.cursor()
    c.execute("SELECT idCategory FROM Category WHERE idCategory = ?", (categoryID,))
    if not c.fetchone():
        conn.close()
        raise ValueError("Invalid category ID")
    c.execute('''INSERT INTO Product (Name, Price, CategoryID, Description) VALUES (?, ?, ?, ?)''', (productName, price, categoryID, description))
    conn.commit()
    conn.close()