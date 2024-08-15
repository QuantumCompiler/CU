# CSPB-3308  Lab 9 :  Javascript
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>
<hr>

Javascript is a dynamic computer programming language. It is lightweight and most commonly used as a part of web pages, whose implementations allow client-side script to interact with the user and make dynamic pages. It is an interpreted programming language with object-oriented capabilities.

Client-side JavaScript is the most common form of the language. The scripts can be
included in or referenced by an HTML document and the code is interpreted by
the browser.
It means that a web page does **not** need to be a static HTML page, but can include programs that
interact with the user, control the browser, and dynamically create HTML content.
The JavaScript client-side mechanism provides many advantages over traditional CGI
server-side scripts. For example, you might use JavaScript to check if the user has
entered a valid e-mail address in a form field before sending the form to the server.

For this project you are making a simple JavaScript **typing game**.     

### Play the game
* Start the Flask app `lab9_app.py`.
* Load the HTML file in your browser (url is .../game).
* Start typing on the keyboard and see what happens.
* Refresh the page if you get stuck.
* Notice that the backspace and return keys do not work as expected
* Look at the HTML and JavaScript files and make sure you understand what is happening.
<hr>


### Step 1 - Add a Cascading Style Sheet to your repository
 *  Create a new file `static/css/lab_javascript.css`
 * In the head element of your html add a CSS link: `<link rel="stylesheet" href="static/css/lab_javascript.css">`
     * Add styling (your choice) to userinput, result, level, and goal.
     * You will need an id selector for the objects and styles
     * `#myid` to modify styles:
```
           #userinput {
                 background-color : lightgray
            }
```
<hr>

### Step 2 - Add Comments to the JavaScript file, Add Support for Special Keystrokes, and Create More Challenges
   1. There are no comments in the JavaScript starter file.
      * Create good comments that explain the concepts.
      * Provide comments that explain the algorithm.

   2. The game currently has 4 challenge levels and strings.
      * Add more difficulty levels so that there are at least six. 
      * You can change any of the `goalStrings` and `difficulties` strings as you wish.

   3. The keystoke handling is rudimentary.
      * Support the BACKSPACE key
      * Have the ENTER key reset the level (clear the string)

<hr>

### Step 3 - Add a Restart Button
* Add a new button element to HTML file
* Give it attribute `id="restartButton"`
* Define a new function `restart()` , in the JavaScript file:
```
               function restart() {
                       // In here set i=0
                       // find the level, result, and goal elements and reset their textContent
                }
```
* Add an eventListener
* Note `document.querySelector` uses the same selector syntax as your CSS file.
```
             restartButton = document.querySelector("#restartButton")
             restartButton.addEventListener('click', restart) // this is your restart func
```
<hr>

### Step 4 - Add a Next Challenge Button
* Show a "Next Challenge" button. 
* Clicking the button should start the next challenge.
* Add the button dynamically so that it only appears when the user completes the challenge.
* The game should dynamically display "You Win!" when you complete the challenge.
* Add this code to the keypress listener:
```
    next = document.createElement('button')
    document.body.appendChild(next)
    next.addEventListener('click', nextChallenge)
```

A good way to implement this change is to move the code in the keypress listener that sets up the next challenge into a new function called "nextChallenge".
<hr>


### Step 5 - Add a Timer Mechanism
Create a timer to record the length of time needed to complete a level.  Display the elapsed time to the user once they have completed a level. 
You can display a timer to the user that updates constantly until the level is completed (adds more stress to the user).
* In JavaScript `Date.now()` returns a timestamp in milliseconds.
* To start timing, record the timestamp with a variable:
```
               start = Date.now()
```
* To stop timing, get a second timestamp and report the difference:
```
              end = Date.now()
              diff = (end - start)/1000
              timing = document.createElement('p')
              timing.textContent = diff
              document.body.appendChild(timing)
```
* Determine where these lines should go in your JavaScript file.
* Make sure timing works correctly with the "restart" and "nextChallenge" buttons.
<hr>


### Step 6 -  Make one more improvement to the game of your choice.
It can be any improvement you like, but should be enough work to show me that you can make substantive changes to the game.  Make sure you comment the source and the `about` page to specify which changes are being made.

Some suggestions:

   - Detect and highlight user's typos
   - Let user input goal strings
   - A leaderboard for fastest finishes
   - Add random challenges using Math.random()
   - unique CSS style changes for each challenge
   - Improve html document structure so it's not random `h3` and `p` tags in the document body
   - Give it an makeover, add some graphics

<hr>

<img src="static/images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" style="margin:10px" />

### Modify the `lab9_app.py` Flask application to include these required routes

      1. static text page, "index"   @app.route('/')       - list of all routes supported.
      2. static text page, "about"   @app.route('/about')  - list author information and changes implemented.
      3. static text page, "game"    @app.route('/game')   - access to the game

<img src="static/images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" style="margin:10px" />

### Make sure to add **comments** to your files showing where you made improvements  and what functionality those improvements perform.

<hr>

Although the grading will be done by accessing your Git Classroom remote repository, <br>
you must submit the following to Moodle Assignment:

    * Your name:
    * CU ID: (4 letters - 4 digits)
    * GitHub Username:
    * Hours to complete lab:


**IMPORTANT**: Make sure that all your added files and changes are **pushed** to the remote repository before going to Moodle to submit your completion information in the Moodle assignment.

<hr><hr><hr>
