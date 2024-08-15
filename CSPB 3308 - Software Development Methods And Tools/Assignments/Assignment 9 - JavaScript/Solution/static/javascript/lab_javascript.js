document.addEventListener('DOMContentLoaded', function() {
  const difficulties = ["Easy", "Medium", "Hard", "Fact", "Harder", "Harderer", "Hardest"];
  const goalString = ["CS 3308",
    "This is not a test.",
    "42 is the answer to the Ultimate Question of Life, the Universe, and Everything.",
    "The Javascript Lab is kinda fun!",
    "So you have made it this far, huh? How about this one?",
    "You are uNsToPpAbLe! BuT yOu WoN't gEt ThIs OnE!",
    "Unbelievable, you should apply as a typist my friend!"
  ];
  const randomChallenges = ["This is a random challenge",
    "This is another random challenge",
    "Random random RANDOM",
    "..... ... ..... ....",
    "??? ?? ???? ?? ? ? ??",
    "!! ! !!!! !! ! ! !!!!"
  ];

  var i = 0;
  var start;
  var currentGoalText = goalString[i];

  /*  restart - This function is called when the user clicks the Restart button.
        Input:
          None
        Algorithm:
          * Set the index to 0
          * Get the textbox element from the HTML document
          * Set the textbox content to an empty string
          * Get the result element from the HTML document
          * Set the result content to "Type the Following text:"
          * Get the level element from the HTML document
          * Set the level content to the difficulty at the index
          * Get the goal element from the HTML document
          * Set the goal content to the goalString at the index
          * Get the nextChallenge element from the HTML document
          * If the nextChallenge exists, remove it
        Output:
          None
  */
  function restart() {
    i = 0;
    const textbox = document.getElementById("userinput");
    textbox.textContent = "";
    const result = document.getElementById("result");
    result.textContent = "Type the Following text:";
    const lvl = document.getElementById("level");
    lvl.textContent = difficulties[i];
    const goal = document.getElementById("goal");
    goal.textContent = goalString[i];
    currentGoalText = goalString[i];
    const nextChallenge = document.getElementById("nextChallenge");
    if (nextChallenge) {
      nextChallenge.remove();
    }
    clearTiming(); // Clear any existing timing elements
    start = Date.now();
  }

  /*  nextChallenge - This function is called when the user clicks the Next Challenge button.
        Input:
          None
        Algorithm:
          * If the index is less than the length of the goalString array:
            * Get the textbox element from the HTML document
            * Set the textbox content to an empty string
            * Get the result element from the HTML document
            * Set the result content to an empty string
            * Get the level element from the HTML document
            * Set the level content to the difficulty at the index
            * Get the goal element from the HTML document
            * Set the goal content to the goalString at the index
            * Get the nextChallenge element from the HTML document
            * If the nextChallenge exists, remove it
            * Reset the start time
          * Otherwise:
            * Get the result element from the HTML document
            * Set the result content to "You have completed all challenges!"
  */
  function nextChallenge() {
    if (i < goalString.length) {
      const textbox = document.getElementById("userinput");
      textbox.textContent = "";
      const result = document.getElementById("result");
      result.textContent = "";
      const lvl = document.getElementById("level");
      lvl.textContent = difficulties[i];
      const goal = document.getElementById("goal");
      if (i > 3) {
        goal.textContent = goalString[i];
        currentGoalText = goalString[i];
        var randInt = Math.floor(Math.random() * 10);
        if (randInt % 2 === 0) {
          var rand = Math.floor(Math.random() * randomChallenges.length);
          goal.textContent = randomChallenges[rand];
          currentGoalText = randomChallenges[rand];
        }
      } else {
        goal.textContent = goalString[i];
        currentGoalText = goalString[i];
      }
      const nextChallenge = document.getElementById("nextChallenge");
      if (nextChallenge) {
        nextChallenge.remove();
      }
      clearTiming();
      start = Date.now();
    } else {
      const result = document.getElementById("result");
      result.textContent = "You have completed all challenges!";
    }
  }

  /*  clearTiming - This function clears any existing timing elements.
        Input:
          None
        Output:
          None
  */
  function clearTiming() {
    const existingTiming = document.getElementById("timing");
    if (existingTiming) {
      existingTiming.remove();
    }
  }

  // Restart button event listener
  const restartButton = document.querySelector("#restartButton");
  restartButton.addEventListener('click', restart);

  start = Date.now();

  window.addEventListener("keydown", function(event) {
    // Textbox for the userinput field in the HTML file
    const textbox = document.getElementById("userinput");
    // Handle Backspace key
    if (event.key === "Backspace") {
      event.preventDefault(); // Prevent the default behavior of the Backspace key
      textbox.textContent = textbox.textContent.slice(0, -1);
    } else if (event.key.length === 1 || event.key === " ") {
      // Add the key pressed to the textbox by using the event object with key as the property
      textbox.textContent = textbox.textContent + event.key;
    }
    // If the textbox content equals the current goal text
    if (textbox.textContent === currentGoalText) {
      // Grab the result div from the HTML document
      const result = document.getElementById("result");
      // Set it to "You Win!"
      result.textContent = "You Win!";
      // Record the end time and calculate the difference
      const end = Date.now();
      const diff = (end - start) / 1000; // Convert milliseconds to seconds
      // Clear any existing timing elements
      clearTiming();
      // Display the elapsed time
      const timing = document.createElement('p');
      timing.id = "timing";
      timing.textContent = `Time taken for ${difficulties[i]}: ${diff} seconds`;
      document.body.appendChild(timing);
      // Increment the index
      i = i + 1;
      // Create and show the Next Challenge button if there are more challenges
      if (i < goalString.length) {
        // Create a button element
        const next = document.createElement('button');
        // Set the id of the button to "nextChallenge"
        next.id = "nextChallenge";
        // Set the text of the button to "Next Challenge"
        next.textContent = "Next Challenge";
        // Append the button to the body of the HTML document
        document.body.appendChild(next);
        // Add an event listener to the button that calls the nextChallenge function when clicked
        next.addEventListener('click', nextChallenge);
      } 
      // If there are no more challenges, display a message saying that all challenges have been completed
      else {
        result.textContent = "You have completed all challenges!";
      }
    }
  });
});