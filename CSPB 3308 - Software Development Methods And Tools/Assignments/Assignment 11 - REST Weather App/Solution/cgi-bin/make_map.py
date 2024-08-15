#!/usr/bin/python3

# Import necessary modules
import os

# Define the path to the SVG file
svg_file_path = os.path.join(os.path.dirname(__file__), '..', 'images', 'Blank_US_Map.svg')

# Ensure the SVG file exists
if not os.path.isfile(svg_file_path):
    print("Content-type: text/html")
    print()  # This extra newline is important!
    print("<html><body><h1>Error: SVG file not found</h1></body></html>")
    exit(1)

# Print the content-type header
print("Content-type: text/html")
print()  # This extra newline is important!

# Print the HTML header and include the JavaScript code in the <head>
print('''<!DOCTYPE html>
<html>
<head>
    <title>US Map Lab by Larrechea</title>
    <link rel="icon" href="data:,">
        <script>
            window.onload = function() {
            var elements = document.getElementsByClassName('co') // returns a list of elements
            elements[0].setAttribute('fill', '#CFB87C');         // set the color in the first element returned
            };
        </script>
</head>
<body>
''')

# Read and print the SVG file contents
with open(svg_file_path, 'r') as svg_file:
    for line in svg_file:
        print(line, end='')

# Print the closing tags for body and html
print('''
</body>
</html>
''')