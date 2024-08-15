# CSPB-3308  Lab 4 :  Version Control System (VCS)
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>
<br>
    
An important aspect of successful team projects is using a tool for managing your shared resources.  These resources include code, scripts, documentation, and other files that need to be available to all team members and may change over time.  Managing these resources can be accomplished by using a Version Control System (VCS) to manage all your development and deployment.   `Git` is a widely used VCS application that is web based and can support hundreds of individual contributors to a project.  The same features that make it great for projects with hundreds of developers also makes it great for small teams of developers.

The VCS application allows multiple developers to simultaneously work on the same project files.  The VCS manages the versions of the files so you always know which is the latest version.  But it also remembers all the previous versions of a file.  You can always get an older version of a file or of all the files at a specific time in the development. When two of more developers are making changes to the same files, the VCS will know that a simultaneous change has occurred and will indicate a conflict.  The conflict is resolved by merging the two simultaneous versions into one new version.
<br>

<IMG SRC="images/commit_history.png" WIDTH=75% >

`Git` also allows developers to manage working on multiple project features at the same time.  `Git` can create individual branches from the main code development source tree where changes can be tried out before merging back into the shared source.  Developers can move between these branches and the VCS will remember the state of each source file and restore that state when changing branches.

This assignment is in the form of a tutorial that will walk through a scenario with making changes to files in multiple branches.  Then it will walk through the merge process of combining new code back into the main shared branch of the source tree.

**Objectives**
	
* use VCS to manage changes to project files
* using `Git` to create and manage development branches
* manage merge conflicts that arise when there are multiple developers
* brief introduction to HTML

<hr>

Project has following folder tree:
```
.  
├── images  
|   └── ...  
├── README.md  
└── LAB_4_STEPS.md
```

| File | Description |
|---|---|
| images                  | directory holding images for README.md |
| &nbsp;&nbsp;&nbsp;&nbsp;...        |  |
| __README.md__           | __Readme file you are viewing here__ |
| LAB_4_STEPS.md         | Readme file with Lab-4 tutorial instructions |

<hr>

### This assignment will focus on introducing  you to branches and merging branches

### Getting Started

<IMG SRC="images/commit_4.png" WIDTH=25% ALIGN="right">

You will create a new file,  `sample.html`, in your repository to be modified and saved as commits to your repository.  We will simulate multiple developers using multiple branches of the repository to isolate the changes being made.  This is often done when a developer is fixing a bug or adding a new feature.  While that bug fix or feature development is in progress, we do not want to interfere with the working code in the main branch of the repository. We also do not want new features placed in the main branch to change the code in our development environment until we are ready.  

To coordinate the changes to the source code, we can create branches of the source tree to temporarily make changes.  When we have completed the bug fix or new feature, we can merge our code back into the main branch.  We will be creating a number of different versions of the same file and each of these variations will be **committed** to the local repository in the steps of the tutorial.
We can use the **log** command in `git` to see the history and changes made in the branches of the repository.
<br><br>

For this assignment you will be using a command line to perform the `git` commands.  Although most of these commands can be performed through the GUI interface, the command lines are much more more explicit.   You will need to open a terminal window and use the linux commands.  We recommend that you use the [csel.io](https://coding.csel.io/) JupyterHub environment.  This development environment provides you with a virtual machine that you can access from any computer.  It maintains the storage of your files and provides needed libraries and applications for the course.  There is also a `git` interface that will allow you to make the commits and to view the history in a graphical form.
<hr>

## CSPB-3308  [Lab 4 :  Version Control System (VCS)](LAB_4_STEPS.md)
The Lab 4 `LAB_4_STEPS.md` contains the instructions for completing the lab.

### When you have completed the Lab tutorial
Your submission will consist of two items:
   1. Your remote repository for the assignment. It should have the commits and merges that you performed in the assignment.  Remember that you must **push** your local repository changes to the remote repository. 
   1. Information to be submitted to the assignment page in Moodle.

We suggest that you **push** your changes often.  Each time you complete a step of the tutorial and **commit** the changes with the commit message indicating the step, you should also **push** the changes to the remote repository.

**IMPORTANT**: Make sure that all your changes are **pushed** to the remote repository before going to Moodle to submit your completion information in the Moodle assignment.

Here is what you should have accomplished in Lab-4:
	
	1. Created development branches on local and remote
	2. Merged branches locally
	3. Resolved merge conflicts
    4. Removed branches that are no longer relevant
	
<hr><hr><hr>

[Continue on to the Lab4 Steps](LAB_4_STEPS.md) ==>
