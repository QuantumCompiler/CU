#!/usr/bin/env python3
import os
import sys
import sqlite3

#print (os.getcwd(),"\n", sys.path)
#print (sys.path)

if __name__ == "__main__":
    sys.path.append(".")

    print ("\n"*5)
    print ("*"*80)
    print ("*"*80)
    print ("RUNNING IN:", os.getcwd())
    print ("IMPORTING dbAPI")

# import the student's solution
import dbAPI
print ("*"*80)
print ("IMPORT dbAPI completed")

tables = []

def print_tables(dbname):
    conn = sqlite3.connect(dbname)
    c = conn.cursor()
    c.execute("SELECT name FROM sqlite_master WHERE type='table';")

    print ("\nTables:")
    for t in c.fetchall() :
        print ("\t[%s]"%t[0])
        
        tables.append(t[0])

     ##   print ("\tColumns of", t[0])
        c.execute("PRAGMA table_info(%s);"%t[0])
        for attr in c.fetchall() :
            print ("\t\t", attr)
        
        print ("")
        
        
def print_tables_rows(dbname):
    conn = sqlite3.connect(dbname)
    c = conn.cursor()
    c.execute("SELECT name FROM sqlite_master WHERE type='table';")

    print ("\nTable Values:")
    for t in tables :
        print ("\t[%s]"%t)
        
        sql = "SELECT * from %s ;"%t
        print ("\t\t\t<%s>"%sql)
        c.execute(sql)
        for row in c.fetchall() :
            print ("\t\t", row)
       
        print ("")     
        
def copy_source(filename):
    print (f"[{filename}]")
    print ("    ", "v"*80)
    count = 0
    try:
        with open(filename) as file:
            lines = file.readlines()
            for line in lines:
                count += 1
                print ("%4d "%count, "*"*4, line.strip("\n"))
    except FileNotFoundError as e:
        print ("File not found:", filename)
    print ("    ", "^"*80)
    

def grader():

    dbname = "dbAPI.db"

    if (True) :
        try:
            os.remove(dbname)
        except:
            pass
        
    if (True) :
        print ("*** Create DATABASE:", dbname)
        print ("dbAPI. fill({dbname})")
        try:
            dbAPI. create(dbname)
        except Exception as e:
            print ("*********** Error creating database", e)
        print_tables(dbname)

        print ("*** fill DATABASE:", dbname)
        print ("dbAPI. fill(dbname)")
        try:
            dbAPI. fill(dbname)
        except Exception as e:
            print ("*********** Error filling database", e)
            
        print_tables_rows(dbname)

        
    if (True) :
        print ("    ", "*"*80)
        print ("    ", "*"*80)

        # Show dbAPI.py file
        copy_source("dbAPI.py")
 
        print ("    ", "*"*80)
        print ("    ", "*"*80)

        # Show test_dbAPI.py file
        copy_source("test_dbAPI.py")
 
        print ("    ", "*"*80)
        print ("    ", "*"*80)

        # Show test.py file
        copy_source("test_addProduct.py")

        print ("    ", "*"*80)
        print ("    ", "*"*80)
        
    if (True) : 
        print ("Runing TESTS:", os.getcwd())
        print ("*"*80)
        
        # make sure the store.db file is not created.
        try:
            os.remove(dbname)
        except:
            pass
        
        sys.stdout.flush()
        os.system("python test_addProduct.py")
        sys.stdout.flush()

        print ("Completed:", os.getcwd())
        print ("*"*80)

if __name__ == "__main__":
    grader()
