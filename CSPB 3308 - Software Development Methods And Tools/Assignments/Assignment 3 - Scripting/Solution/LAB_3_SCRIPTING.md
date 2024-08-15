 # CSPB-3308  Lab 3 :  More Scripting
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>

There are two parts to this assignment: team and individual.  This document describes the individual activity to create more scripts for processing data. You will continue to write scripts to perform more complex tasks. 
In the previous lab you created a script that validated that a filename given as a parameter existed and then extracted files from that file into the current working directory (cwd).  
 
In this lab you will create new scripts to build the directory structure, download the html file, and generate the clue files. Your new scripts will be given two parameters that will allow you to:
    
* create the correct directory within the hierarchical storage organization
* download the correct HTML file from the Jarchive URL
* extract the data from the downloaded HTML file into the correct directory within the hierarchical storage organization. 

The two scripts that you will write:
* A script to create the correct subdirectories from a given `year` and `game id`.  It must validate that the parameters are correct format and print error message if when they are not valid.
    
* A script given `year` and `game id` that will create the correct subdirectories, download the correct HTML file, and create the extracted data in the correct subdirectory. This script *must* validate that the parameters are correct format, print error message if when they are not valid, and call your previously written scripts.
    
Make sure to take advantage of scripts already written when creating the last script.
It **must** use the previously written scripts (call the other scripts, do not copy the commands from previous script into new script).  
**All the scripts must be commented with at least author, purpose, and usage statements to receive credit.**
<hr>


<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
1. Write a script to create the correct subdirectories in the storage hierarchy  The script will be given two parameters for the `year` and the `game id` to be downloaded.  The parameters should be check for validity (both parameters must be all digits, year should be within range of when games were broadcast).

The script should be placed in your `bin` directory of the repository.  You must make your script look for the `Data` directory in the *cwd* and print an error if it does not exist.  Given the parameters are correct, create the appropriate subdirectories required.  The script must indicate the directories that are actually created (did not already exist).
<br><br>

<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
    
2. Write script to create the extracted data files for a given `year` and `game id`.  The parameters should be validated by assuring that the directories exist and download the specific HTML file from the Jarchive website the correct directory. 
* If the script does not have the two required parameters, it must print an error message that includes the correct usage of the script. 
* Script must print message(s) for any directory created and produce an error message if the download fails. 
* The script will extract the data from the downloaded file into the same subdirectory as the file (not the cwd).
* The script must take advantage of the previous scripts written to extract data and to create subdirectories.  This means you must call the scripts that have already been designed to solve part of the processing of this script.  You must only use the name of the script (no path information) and let the shell use its PATH variable to find the correct script file.
* Script must print a message when the whole processing has completed without any errors. It must not print the message if any errors occur throughout the processing.
* The script must call your previously created scripts from within the new script.
* All scripts must be commented with at least author, purpose, and usage statements to receive credit.
* All paths in the scripts must be relative (not absolute) paths.  Assume that the current working directory has the subdirectory `Data`. Do not add absolute paths to the scripts being called, let the PATH variable be used to find them.<br>(*Remember that a relative path describes the location of a file or directory relative to the **current (working) directory** and an absolute path describes the location from the **root directory** .*)
<hr>

### You have completed the Individual activity for Lab-3.  
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
    
**IMPORTANT**: The grading will be done by accessing your Git Classroom remote repository. Make sure that all your added files and changes are **pushed** to the remote repository.

<hr><hr><hr>

