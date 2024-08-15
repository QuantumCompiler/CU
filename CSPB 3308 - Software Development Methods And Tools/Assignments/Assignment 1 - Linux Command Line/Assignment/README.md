# CSPB-3308  Lab 1 & 2 :  Using Command Line Interface and Creating Scripts
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>

For many course projects you will need to obtain data to use.  Often that data is only available from a website that displays the information using a web browser.  The information sent to a web browser is HTML (Hypertext Markup Language). HTML is a text-based approach to describing how content contained within an HTML file is structured, how it should be displayed, and how the components of the page can interact with the user.

Web scraping is the practice of sifting through a web page's HTML to gather data that you need and place it in a format useful to you.  In this assignments you will perform tasks to scrape data from an HTML page that has been downloaded.      

<hr>
In these two assignments you will use a set of unix commands from the command line of a terminal window.  From the command line you will extract data from a given file, access other web pages, and create a hierarchical storage structure to organize the data.

You do not need to understand the HTML files, only that they are lines of text.  We will use commands to take advantage of the format of the text files to extract the data.

Objectives
* extract data from a file
* create scripts that will process individual pages
* create a hierarchy for the storage of extracted data
* build reusable scripts for processing a file
* customize the development environment 

<hr><hr><hr>

Project has following folder tree:
```
.  
├── images  
|   ├── Commit.jpeg  
|   ├── deliverable.png  
|   ├── Push.jpeg  
|   ├── Staged.jpeg  
|   └── Unstaged.jpeg  
├── Lab_2_data
|   ├── answer1.txt  
|   ├── regex_data1.txt  
|   └── template.sh 
├── README.md  
├── LAB_1_README.md  
├── LAB_2_README.md  
└── game_6692.html  
```

| File | Description |
|---|---|
| images                  | directory holding images for README.md |
| &nbsp;&nbsp;&nbsp;&nbsp;Commit.jpeg        | image of the **commit** GUI interface for Git |
| &nbsp;&nbsp;&nbsp;&nbsp;deliverable.png    | icon used to show deliverable items in the instructions |
| &nbsp;&nbsp;&nbsp;&nbsp;Push.jpeg          | image of the **push** and **pull* icons |
| &nbsp;&nbsp;&nbsp;&nbsp;Staged.jpeg        | image of the **Staged** files in the GUI interface for Git |
| &nbsp;&nbsp;&nbsp;&nbsp;Commit.jpeg        | image of the **Unstaged** files in the GUI interface for Git |
| Lab_2_data              | directory holding data used in Lab-2.  There may be multiple data files of each type in the directory |
| &nbsp;&nbsp;&nbsp;&nbsp;answers1.txt       | answers for regex_data1 processing |
| &nbsp;&nbsp;&nbsp;&nbsp;regex_data1.txt    | data on which to apply regex solutions |
| &nbsp;&nbsp;&nbsp;&nbsp;template.sh        | template script for writing regex solutions |
| __README.md__           | __Readme file you are viewing here__ |
| LAB_1_README.md         | Readme file for Lab-1 instructions |
| LAB_2_README.md         | Readme file for Lab-2 instructions |
| game_6692.html          | An HTML file that has been downloaded from a web site.  It holds the data we want to extract.  |


<hr>

### Your submission for this assignment
For your submission you **commit** all the files that have been created or modified.  The **commit** will update your local repository, but not the remote classroom repository.  You must **push** your local repository changes to the remote repository. You will also need to submit information in the Moodle assignment.

We suggest that you **commit** and **push** your changes often.  Each time you complete a step of the tutorial, **commit** the changes with a commit message indicating the step that has been completed. 

### Getting Started
You will be using a command line to perform the tasks.  You will need to open a terminal window and use the linux commands.  We recommend that you use the [csel.io](https://coding.csel.io/) JupyterHub environment.  This development environment provides you with a virtual machine that you can access from any computer.  It maintains the storage of your files and provides needed libraries and applications for the course.

JupyterHub has a Graphical User Interface for browsing the file system as well as accessing Git functionality.  It also supports the use of Visual Studio Code, which is an Integrated Development Environment (IDE) used widely in industry and  academia.   

You must **clone** this repository  on to your virtual csel.io machine and/or your local machine.  This can be accomplished using the GUI interface (see videos provided in Moodle) or using the command line.  To **clone** this repository from the command line, change directory to where you want to create the new repository directory and use the command below which will create a directory and populate it with any files and directories in the repository :
```
  git clone https://github.com/cu-cspb-3308-software-dev-<semester-year>/<your repository name>.git
```
You should visit your remote repository to get the actual **URL** for that repository. This is the same **URL** of the repository that you received when you accepted the assignment in GitHub Classroom.   Use your personal repository **URL** in **clone** command listed above.
<hr>

## CSPB-3308  [Lab 1 :  Using Command Line Interface](LAB_1_README.md)  (due in Week 2)
In this assignment you will use a set of unix commands from the command line of a terminal window.  From the command line you will extract data from a given file, access other web pages, and create a hierarchical storage structure to organize the data.    
<hr>

## CSPB-3308  [Lab 2 :  Creating Scripts](LAB_2_README.md)   (due in Week 3)
In this assignment you will create a set of scripts that can be run from the command line of a terminal window.  You will modify the development environment to be able to find these scripts when the current working directory is not in the directory with the scripts.

<hr>

### When you have completed each Lab tutorial
**IMPORTANT**: Make sure that all your changes are **pushed** to the remote repository before going to Moodle to submit your completion information in the Moodle assignment.

<hr><hr><hr>
