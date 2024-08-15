###############################################################################
## This is starter code for your Lab 6 Flask application
##
## The **prefix.py** code is included to allow you to develop your code within
## the **csel.io** environment.  There is a required prefix to be used when
## pages access the **csel.io** virtual machine from your local machine browser.
## 
## The prefix code will have no effect when running Flask on your local machine
## as it looks to make sure you are running on **csel.io** virtual machine.
##
## Author: Knox - Sept 2022
##
###############################################################################


###############################################################################
## Import "prefix" code into your Flask app to make your app usable when running
## Flask either in the csel.io virtual machine or running on your local machine.
## The module will create an app for you to use
import prefix

from flask import Flask, render_template_string, request, url_for, render_template

# create app to use in this Flask application
app = Flask(__name__)

# Insert the wrapper for handling PROXY when using csel.io virtual machine
# Calling this routine will have no effect if running on local machine
prefix.use_PrefixMiddleware(app)

# test route to show prefix settings
@app.route('/prefix_url')
def prefix_url():
    return 'The URL for this page is {}'.format(url_for('prefix_url'))

###############################################################################
## Required Routes from Flask Tutorial for Lab include:
##     1. static text page, "index"   @app.route('/')
##     2. static text page, "hello"   @app.route('/hello')
##     3. static text page, "project" @app.route('/projects/')
##     4. static text page, "about"   @app.route('/about')
##     5. dynamic text, route parameter, string  @app.route('/user/<username>')
##     6. dynamic text, route parameter, int     @app.route('/post/<int:post_id>')
##     7. dynamic text, route parameter, subpath @app.route('/path/<path:subpath>')
##
## Place your required routes here
##

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/hello')
def hello():
    return render_template('hello.html')

@app.route('/projects')
def project():
    return render_template('projects.html')

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/user/<username>')
def user(username):
    return render_template_string('<h1>Username: {{ username }}</h1>', username=username)

@app.route('/post/<int:post_id>')
def post(post_id):
    return render_template_string('<h1>Post ID: {{ post_id }}</h1>', post_id=post_id)

@app.route('/path/<path:subpath>')
def subpath(subpath):
    return render_template_string('<h1>Subpath: {{ subpath }}</h1>', subpath=subpath)


###############################################################################
## Place your optional routes here

@app.route('/static_text')
def static_text():
    with open('templates/static_text.txt', 'r') as file:
        content = file.read()
    return render_template_string('<pre>{{ content }}</pre>', content=content)

@app.route('/static_html')
def static_html():
    with open('templates/static_page.html', 'r') as file:
        content = file.read()
    return render_template_string(content)

@app.route('/dynamic_list')
def dynamic_list():
    items = ['This is pi: 3.14159', 'This is energy: e=mc^2', 'This is force: F=ma']
    html_content = """
    <title>Optional Route - Dynamic List Page</title>
    <div style="text-align: center">
        <h1>Dynamic List Page</h1>
        <ul style="margin: auto; display: inline-block; list-style-type: none; padding: 0;">
            {% for item in items %}
                <li>{{ item }}</li>
            {% endfor %}
        </ul>
    </div>
    """
    return render_template_string(html_content, items=items)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_the_login_form()

def do_the_login():
    return "do_the_login() called"

def show_the_login_form():
    return "show_the_login_form() called"

###############################################################################
# main driver function
if __name__ == '__main__':
    # run() method of Flask class runs the application 
    # on the local development server using port 3308 instead of port 5000.
    app.run(host='0.0.0.0', port=3308, debug=True)