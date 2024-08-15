###############################################################################
## Import this file into your lab_6_app.py file to make it usable in Flask when
## running either in the csel.io virtual machine or running on your local machine.
## This code will provide a prefix for any url's that is accessing files in your 
## code tree.  For instance, to access a local image in your web page you will 
## need to ask for the HTML URL to that resource using the url_for() function.  
## The module will create an app for you to use.  
## Example:
##   import prefix
##   app = prefix.app
##
##   @app.route('/prefix_working')  
##   def prefix_working():
##      return 'The URL for this page is {}'.format(url_for('prefix_url'))
##
###############################################################################

from flask import Flask, url_for, make_response, render_template
import os

#  if running this file as main Flask application
#  we need to create the Flask app to use 
if __name__ == '__main__':
    app = Flask(__name__)

###############################################################################
## This section allows us to set the prefix information to access
## url's that access our JupyterHub environment.
##
## Every call to url_for will be given the prefix for accessing via PROXY.
## If not in a JupyterHub environment, the prefix will be empty allowing access
##    to the local machine's Flask task.
##

class PrefixMiddleware(object):

    def __init__(self, app, prefix=''):
        self.app = app
        self.prefix = prefix

    def __call__(self, environ, start_response):
        # Here we check to see if we are .
        # If we are in a JupyterHub environment, the OS environment variable will be 
        #    set with the user's info.
        # If we are not in a JupyterHub environment, the function will return None.

        # get the prefix for the JupyterHub URL to access the user's virtual machine
        service_prefix = os.getenv('JUPYTERHUB_SERVICE_PREFIX', default=None)
        print (f"Service Prefix: {service_prefix}")
        if (service_prefix):
            # set the prefix for all url's to access the JupyterHub URL for current user's virtual machine.
            # the SCRIPT_NAME needs the following format:  "/usr/<user_id>/proxy/<port no>"
            # the OS environment variable JupyterHub_SERVICE_PREFIX contains the "/usr/<user_id>"
            # the Flask environment variable SERVER_PORT contains the port used by Flask
            environ['SCRIPT_NAME'] = service_prefix + "proxy/" + environ['SERVER_PORT']
            print(f"Setting SCRIPT_NAME to {environ['SCRIPT_NAME']}")
            
        # call the default processing
        return self.app(environ, start_response)

# Insert our proxy setting url class as wrapper to the app
def use_PrefixMiddleware(app):
    app.wsgi_app = PrefixMiddleware(app.wsgi_app)
    

###############################################################################
# main driver function
#    Connect prefix handler to our Flask application
#    Define Flask routes for testing prefix handler
#
if __name__ == '__main__':

    # Insert the wrapper for handling PROXY when using csel.io virtual machine
    # Calling this routine will have no effect if running Flask on local machine
    use_PrefixMiddleware(app)    

    ###############################################################################
    ## simple routines to test parameters to the route method
    ##
    @app.route('/')  
    def index():
        # use <pre> tag to specify preformatted text
        resp = '''<pre>
                This is a test page for prefix.py
                There are 4 routes defined:
                    /
                    /prefix_url
                    /prefix_css
                    /prefix_link
                </pre>
                '''
        return resp
    
    @app.route('/prefix_url')  
    def prefix_url():
        resp = '''<pre>
                This is a test page for prefix.py
                The URL for this page is {}
                The URL for local resource static/image/prefix.jpg is {}
                </pre>
                '''
        return resp.format(url_for('prefix_url'), url_for('static', filename="image/prefix.jpg"))

    @app.route('/prefix_css')
    def prefix():
        return make_response(render_template("prefix_test.html"))

    @app.route('/prefix_link')
    def prefix_test():
            resp =  ''' 
                    <div>
                        <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=50 ALIGN="left">
                        CU logo image from specific url address
                    </div><br><hr><br>
                    '''
            local_url = url_for("static", filename="images/prefix.jpg") 
            resp += "<div>" 
            resp +=  '<a href="' + local_url + '" > Click here to access image:</a>'
            resp += "&nbsp;&nbsp;" + local_url
            resp += "<br>"
            resp += f'<IMG SRC="static/images/prefix.jpg" WIDTH=50 ALIGN="left">'
            resp += '<br><br>Accessing local image in the "static/images" directory of the flask environment code<br>'
            resp +=  "</div>"

            return resp

    @app.route('/prefix_env')
    def prefix_environ():

        resp = ""

        # DEBUG Code: to list all the environment variables
        resp += "<h3>OS Environment Variables</h3>"
        for name, value in os.environ.items():
            if (name.startswith('FLASK') or name.startswith('JUPYTER')): 
                resp += "&nbsp;&nbsp;&nbsp;{0}: {1}<br>".format(name, value)

        resp += "<br><hr><br>"

        # DEBUG Code: to list all the flask environment settings
        resp += "<h3>Flask Configuration Variables</h3>"
        for key in app.config.keys():
            resp += f"&nbsp;&nbsp;&nbsp;{key} = {app.config[key]}<br>"

        resp += "<br><hr><br>"

        return resp

    ######################################################################
    # run() method of Flask class runs the application 
    # on the local development server using port 3308 instead of port 5000.
#    app.run(host='0.0.0.0', port=3308)
    app.run(host='localhost', port=3308)
    