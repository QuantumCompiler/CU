const difficulties = ["Easy", "Medium", "Hard", "Fact"];
const goalString = ["CS 3308",
  "This is not a test.",
  "42 is the answer to the Ultimate Question of Life, the Universe, and Everything.",
  "The Javascript Lab is kinda fun!"
  ];

var i = 0;

window.addEventListener("keypress", function (event) {
  const textbox = document.getElementById("userinput");
  textbox.textContent = textbox.textContent + event.key;
  if (textbox.textContent == goalString[i]) {
    const result = document.getElementById("result");
    result.textContent = "You Win!";
    textbox.textContent = "";
    i = i+1;
    lvl = document.getElementById("level")
    lvl.textContent = difficulties[i]
    goal = document.getElementById("goal")
    goal.textContent = goalString[i]
  }
})
