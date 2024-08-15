# CSPB-3308  Lab 2 :  Creating Scripts
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>

For many course projects you will need to obtain data to use.  Often that data is only available from a website that displays the information using a web browser.  The information sent to a web browser is HTML (Hypertext Markup Language). HTML is a text-based approach to describing how content contained within an HTML file is structured, how it should be displayed, and how the components of the page can interact with the user.


Web scraping is the practice of sifting through a web page's HTML to gather data that you need and place it in a format useful to you.  In this assignment you will perform tasks to scrape data from an HTML page that has been downloaded.
In the previous assignment you extracted the lines from the HTML file that were relevant for the data being extracted.  You were able to extract the categories and the clues for the three different rounds of the game.  You also were able to download the HTML page from a URL using a command on the command line.

<hr>
In this assignment you will create a script to perform multiple tasks and to explore regular expressions.
There are two parts to this assignment

1. The commands that you used to create the data files in the last assignment will be combined into a single script.  The scripts can be run from the command line, essentially creating new commands.   You will extend the scripts to use parameters so you can pass information into the script. You will modify the development environment to be able to find these scripts by name (without path) even when they are not in the current working directory.  You will be able to access the scripts without needing to specify a full pathname to the script. 

Your final version of your script for data extraction will create the correct directory within the hierarchical storage organization, download an HTML file from a given URL, and extract data from the downloaded HTML file. You do not need to understand the HTML files, only that they are lines of text as we will use the commands that you created in the last assignment.

2. In the second part of the assignment, you will explore the use of regular expressions.  You will need to write a script to search a file for different complex patterns.  You are given a set of questions to answer about the number of occurrences of patterns within a data file.

<hr>

## This lab is a tutorial which will provide the steps needed to complete the assignment.
    
In the previous lab we ran a set of commands that would extract various lines from a data file.  In this lab we will create a new command that can combine all those individual commands into a single command.   We need to create a script file that specifies the set of commands to be run. Then we need to tell the operating system that the script is an executable file.  Finally, we can tell the shell how to find our newly created sript so we can easialy use the script from anywhere in the directory structure.

Remember that we ran the command `grep "clue_text" game_6692.html` to extract some lines that contained a specific text string.  We captured that output and eventually created a number of different files.  When we downloaded another data file (another HTML file), we needed to run all those commands again to pull out the lines of the new file that we wanted for data.   Step 1 will  create a script that will run all those commands for us.
<hr>

### Step 1 - Combine your previous set of commands into one script
Change your directory into the `Data/1994/Game_6692` directory.  You should see the HTML file and all the files that you created by extracting lines from the HTML file.
Create a new file named `extract.sh`.  This file will be the name of our script and we will be able to issure the following command to run that script: `./extract.sh`.

<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
Comments can be added to the scripts by using a `#` at beginning of the line.  Add some comments to the script to indicate that it was written by you.  The following would be a good first comment.

```
#
# This script was written by: <your name here>
# Date:  
# Purpose: <your description to describe the purpose of this script>
# 
```

<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
Now add in the commands that you used to create the four files in the last assignment:

```
grep ... > categories.txt
grep ... > clues_DJ.txt
grep ... > clues_FJ.txt
grep ... > clues_J.txt
```
    
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
We should add one more line to this script to make sure it is working correctly.  We can print out the number of lines in each file.

```
wc -l *.txt
```

From the command line of the terminal, have the shell run the script using the `./extract.sh` command.  This instructs the shell to run the commands in the script.

```
$ ./extract.sh
bash: ./extract.sh: Permission denied
```

The shell is telling your that the file is not executable. Remember that every file has a set of permissions and one of those permiissions indicates if the file can be executed.  We need to set the permissions for the script file to include execution.

```
$ ls -l
total 92
-rw-r--r-- 1 jovyan users   457 May  5 18:50 extract.sh
-rw-r--r-- 1 jovyan users 86514 May  1 18:54 game_6692.html
	
$ chmod +x extract.sh 

$ ls -l
total 92
-rwxr-xr-x 1 jovyan users   457 May  5 18:50 extract.sh*
-rw-r--r-- 1 jovyan users 86514 May  1 18:54 game_6692.html
```

You will notice that the permission for the file have changed and that the `extract.sh` script that we added to our development environment has added a `*` character to the name,
which indicates that the file is executable.  
Now we can run the script using `./extract.sh` command.  
The output of the script is the output from each of the commands in the script.  
In this case we only see the output of the `wc` command because all the other commands are capturing the output into a file. 

```
$ ./extract.sh 
  13 categoies.txt
  30 clues_DJ.txt
   1 clues_FJ.txt
  30 clues_J.txt
  61 total
```

You should validate that the files are really being built by the script.  Remove the `*.txt` files and run the script again.  This will make sure you can write the files.
Now change directory to one of the other game directories you created.  We will run the script in this directory to generate the files.  My second HTML file was from 1996 with game id of 4206.  After we `cd` to the directory using a relative path, we need to specify the location of the script which is still back in the Game_6692 directory.  We can use a relative path to execute it.

```
$ cd ../../1996/Game_4206
$ ../../1994/Game_6692/extract.sh 
grep: game_6692.html: No such file or directory
grep: game_6692.html: No such file or directory
grep: game_6692.html: No such file or directory
grep: game_6692.html: No such file or directory
0 categoies.txt
0 clues_DJ.txt
0 clues_FJ.txt
0 clues_J.txt
0 total
```

Notice that the script did not try to process the `game_4206.html` file in the current directory because we had explicitly told it to run on the `game_6609.html` file.  We can modify the script to explicitly run on the new game filename, but that means we would need to edit the script to run each new filename.   The best way to solve this is using a parameter to the script.  We can specify the file to be processed on the command line along with the name of the script.  Using `../../1994/Game_6692/extract.sh game_4206.html` to run the script given by a relative pathname,  on the local file named `game_4206.html`. 

<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
Add a parameter to the script that specifies the filename to be processed.
	
Parameters to a sript are accessed by using the `$` symbol followed by the position of the parameter.  In our case above, parameter `$0` is the name of the script, and parameter `$1` is the name of the file we specified.  We can use that parameter in all the commands accessing the filename.  Below we call the script and pass a parameter to the script.

```
$  ./extract.sh file.html
```

Inside the `extrach.sh` file, we can use that given filename in the lines of the script instead of the hard coded filename.  Everywhere we had the filename, we would replace it with the parameter symbol.

```
grep . . . $1 >  categoies.txt
grep . . . $1 >  clues_DJ.txt
grep . . . $1 >  clues_FJ.txt
grep . . . $1 >  clues_J.txt
```

After making the change to the script so it uses the first parameter as the filename in all the `grep` calls,  the files get created.

```
$ ../../1994/Game_6692/extract.sh  game_4206.html 
  13 categoies.txt
  29 clues_DJ.txt
   1 clues_FJ.txt
  30 clues_J.txt
  73 total
```

Once your script is running correctly, make sure to **commit** and **push** your script files to your local and remote repositories.  We will grade the version of your script in your remote repository.	
<hr>

### Step 2 - Create directory for all your scripts and add it to the search path
Now we can run the script from any directory and give it the filename to process.  The difficult part is remembering where the script file is located.  If we were to go back to the top level directory of the repository, we would need to remember adirrerent path to get to the script.  The shell knows how to access many scripts or binary executables located in many different locations without needed to specify the whole path.  The shell uses an environment variable that has been set to specify all the locations of common commands.  Try the command `ls /usr/bin` to see all the standard commands available.  The full pathname `/usr/bin` starts at the top of the file system, for the `usr` directory and its `bin` subdirectory.  The list of files is long and you will see that most of thesm have the `*` indicator of being executable (you should also see the files in a different color).  

The shell knows how to find all those commands because it looks at the PATH variable in the environment to see where to search.  The `echo $PATH` command will list out the current value for the path variable.
```
$ echo $PATH
~CS-3308/venv/bin:/opt/conda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
```
The value of PATH is a list of directories that will be searched in the order that they will be searched.  Each directory is separated from the next in the list by a `:` character.  You can see above that the first place the shell looks will be in my virtual python environment directory `~CS-3308/venv/bin`.  You will learn mot about virtual environments later in the course.  The next directory is `/opt/conda/bin` a  directory of the python installed on my machine.
	
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
We can add to the list of directories that will be searched.  Create a new directory called `bin` in the top directory of your project.  You should now have two directories that you have created in the top level, `Data` and `bin`.  Move the script that we created into that directory.
 
```
$ ls -l bin
total 4
-rwxr-xr-x 1 jovyan users 409 May  5 19:31 extract.sh*
```

Now we need to put the directory into the path.  You will need the full path to the bin directory.  In my case it is `/home/jovyan/CS-3308/3308-lab-1/bin`.  We need the full path name so that we will find that explicit directory no matter where are current working directory is located.  `export PATH=$PATH:<new path>` will append the <new directory> to the end of the search list.  The `which command will tell you where the shell would find a given command.
```
$ export PATH=$PATH:/home/jovyan/CS-3308/3308-lab-1/bin
~CS-3308/venv/bin:/opt/conda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin$:/home/jovyan/CS-3308/3308-lab-1/bin

$ which extract.sh
/home/jovyan/CS-3308/3308-lab-1/bin/extract.sh
```
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
Now we can go to any directory and run the script.  We are in the top level directory, try `extract.sh myfile` and the script will run but will not find the file specified.  
The script runs, but we are getting messages from the commands that the file does not exist.  It would be nice to check that the file exist before running all the commands.  Similar to other programming languages, shell scripts can also perform conditionals (See chapter 27 of the TLCL book for more details).  Here we will check to make sure the file exists.  If it does not exist or is not a regular file, write out a usage message and exit.

```
# Check that the file in parameter 1 exists
if [ -f $1 ]; then
	grep . . . $1 > categoies.txt
	grep . . . $1 | grep "_DJ_" > clues_DJ.txt 
	grep . . . $1 | grep "_FJ" > clues_FJ.txt 
	grep . . . $1 | grep "_J_" > clues_J.txt 

	wc -l *.txt
else
	echo "Invalid or Missing filename"
	echo -n "Usage: "
	echo "$0 <filename>"
	echo ""
fi
```
	
Moving back into the directory of our second game, we can execute the script on the local HTML file.
```
$ cd Data/Year/1996/Game_4206/

$ extract.sh game_4206.html 
  13 categoies.txt
  29 clues_DJ.txt
   1 clues_FJ.txt
  30 clues_J.txt
  73 total
```
	
The last thing we need to do is make that PATH variable change be avilable every time we start up a terminal window.  Like the aliases we created in the last assignment, the update to the path is only for the terminal window where we created it.  The PATH variable is set for each individual terminal window.  To get the new directory to be added every time we start a new terminal window, we need to edit the `~/.bashrc` file and add the `export PATH=$PATH: ...` command. Save the file and now every time a new terminal window is created, the new directory will be part of the path.  Try it now, create a new terminal and `echo $PATH` in the new window.

Once your script is running correctly, make sure to **commit** and **push** your script files to your local and remote repositories.  We will grade the version of your script in your remote repository.	

<hr>

### Step 3 - Part 2: Use RegEX to search for lines with specific patterns

You already created some scripts that you can run to process data.  Now you are going to update an existing script to count the lines in a file that match different criteria.  Copy the template.sh script in the Lab-2 data directory into a file named `lab2.sh` in the `bin` directory of your project.  Modify the `lab2.sh` file to use Regular Expressions to search the file for matching lines and then count those lines.  We have already given you some clues about how to do this in the template shell.
	
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
You can run your data on the test data in the Lab-2 data directory.  There are files for testing (`regex_data*.txt`) and the answers to the questions for each data file are given in `answers*.txt` files.  You can check your results with the results that we think are correct.  There are also some clues in the answer files about common errors in creating your regular expressions.  You will notice that there is one more data file than answers.  We will grade your regular expression using that extra data set.  You should get your code running correctly for all the other data sets.  Run the test data set to make sure you come up with the some answers.

Once your script is running correctly, make sure to **commit** and **push** your script files to your local and remote repositories.  We will grade the version of your script in your remote repository.
<hr>

### You have completed the Lab-2 tutorial.  
**IMPORTANT**: Make sure that all your changes are **pushed** to the remote repository before going to Moodle to submit your completion information in the Moodle assignment.

Here is what you should have accomplished.

1. Created `extract.sh` and placed it in the `bin` directory at the top of your repository.  Script will create the extracted data files needed.
1. Created extracted data files for at least one other game besides the original 4206 game.
1. Created another script `lab2.sh` from the template that will count the number of lines containing each one of the pattens given.
```
.  
├── bin
|   ├── extract.sh
|   └── lab2.sh 
├── Data
|   └── . . . (including newly generated files)
├── images  
|   └── . . .
├── Lab_2_data
|   └── . . .
. . .
	
```
<hr><hr><hr>



