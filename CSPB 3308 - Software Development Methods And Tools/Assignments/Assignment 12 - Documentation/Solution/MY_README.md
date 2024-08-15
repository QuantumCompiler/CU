# Documentation

This lab is an introduction to the basics of Flask.

## Purpose Of This Lab

This lab serves as an introduction to Flask. It will cover the basics of Flask and how to set up a simple application that will render HTML files. The lab will also cover how to render static files and how to use a CSS file to style the application. One will learn how to create routes using Flask and how to use a base template for other html files so that little code is written as possible.

## What Is Flask?

Flask is a micro web framework written in Python. It is classified as a microframework because it does not require particular tools or libraries. It has no database abstraction layer, form validation, or any other components where pre-existing third-party libraries provide common functions. However, Flask supports extensions that can add application features as if they were implemented in Flask itself. Extensions exist for object-relational mappers, form validation, upload handling, various open authentication technologies, and several common framework related tools.

## Directories / Files In This Lab

- images: Directory for the images that are used in the README of the lab.

- static: Contains the CSS file for the Flask application.
    - css: The directory for the css of the application
        - style.css: The css file that is used to style the application.
    - images: The directory for the images of the application
        - prefix.png: An image that is used to display that something is currently under construction.

- templates: Contains the HTML files for the Flask application.
    - about.html: The HTML that was used to create the about page.
    - base.html: This file primarily contains the routes that are found in the application.
    - hello.html: A simple HTML file that displays hello world.
    - index.html: A landing page in HTML for the application.
    - prefix_test.html: A simple HTML file that is used to test the rendering of a prefix and the implementation of a css file.
    - projects.html: Displays links for other pages found in the application.
    - static_page.html: A simple HTML file that displays a static page that is rendered with Flask.
    - static_text.txt: A text file that is used in a page that is rendered with Flask.

- .gitignore: A file that is used to ignore certain files from being pushed to the repository.
- LAB_6_ROUTE_DESC.md: Markdown file that explains what is to be done for the lab.
- lab6_app.py: The main file that is used to run the Flask application.
- MY_README.md: The file that you are currently reading.
- prefix.py: This serves as the backend file for the application.
- README.md: The file that is provided by the instructor that explains the lab.
- setup.cmds: A file that contains the commands that are used to set up the virtual environment for the application.
- setup.sh: A shell file that will set up the virtual environment for the application.

## App Routes For Application

In total, there are 11 routes for this application. Below is an explanation of each route:

- /: The landing page for the application.
- /hello: A simple route that displays hello world.
- /projects: A route that displays links to other pages in the application.
- /about: A route that displays information about the application (just details about the creator of the application).
- /user/username: A route that displays a message that greets the user.
- /post/int:post_id: A route that displays a message that shows the post id.
- /path/path: A route that displays a message that shows the path that was entered.
- /static_text: A route that displays the contents of a text file.
- /static_html: A route that displays a static HTML file.
- /dynamic_list: A route that displays a list of items that are rendered dynamically.
- /login: A route that displays a login page.

## Details About The Application

One can access the application on a local host with the IP address of 0.0.0.0/3308 if on a local development server. On CSEL it would be 0.0.0.0/5000.

## How To Run The Application

To run the application, simply type the following command in the terminal:

~~~
python3.11 lab6_app.py
~~~