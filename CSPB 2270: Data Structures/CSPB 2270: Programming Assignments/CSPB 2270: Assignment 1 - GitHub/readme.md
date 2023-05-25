# CSCI 2270 – Data Structures - Assignment 0
## Overview
Welcome to your first CSCI 2270 assignment! This is a preview assignment to get you acquainted with the workflow of the coding assignments for this class. While the coding aspect of this assignment is trivial, it is still very important that you complete it to so you are ready to tackle the challenges of the future assignments. GitHub Classroom will be used to distribute the assignments to a privite repository for you.  The private respoitory will be used to grade your assignment.

## Objectives

1. Accept the assignment from Github Classroom
2. Clone the assignment to your local work environment
3. Learn the basics of committing and checking-in changes with git
4. Understand how to receive points for completing the coding problems


## Where to Start
Having accepted your assignment in GitHub Classroom, a "private" repository has been automatically created for you. The repository can only be viewed by you and the CSCI 2270 teaching team. Other students cannot see your repo. You can view the contents of your repo by going to the link which was created for you upon accepting the assignment. Once you are ready to begin working on the assignment you will need to *clone* the repository into a suitable development environment. We recommend that you use JupyterHub as your coding environment, and the instructions are provided below. Alternatively, you can use your personal Linux/Mac/Windows machine, but you are on your own as far as setting up the environment (If you are using Windows, you should have the Windows Subsystem for Linux and Ubuntu installed.)

1. Got to JuptyerHub in your browser by navigating to https://coding.csel.io/
2. Choose the CSCI 2270 Data Structures environment
3. Select `File -> New -> Terminal`
4. Now you are ready to *clone* your repository from the remote GitHub repo to your local JupyterHub directory. You can do so by issuing the following command, replacing the SSH URL with your personal one. You can find your unique URL by clicking on the green *Code* icon on your GitHub page.  
```console
jovyan@jupyter-yourcuid:~$ git clone https://github.com/cu-cspb-2270-Spring-2022/assignment-0-<your_github_handle>.git
```
 * You can also clone a repository within the JupyterHub graphical interface.  See video https://youtu.be/M293X5ssks4 for an example of cloning a repository using the built-in interface to Git.

5. At this point you can begin working with your code. We recommend that you use the VSCode editor environment. Go to `File -> New -> Launcher` and click on `VS Code IDE`. This opens a new browser tab.
6. Within VS-Code, select `File -> Open` and then find the directory you just cloned. It should be `/home/jovyan/Assignment-0-username`. 
7. Before we start writing any code, let's compile the starter code and see how we can run the executables.
    * Open up the terminal: `Terminal > New Terminal`
    * Navigate to `build` directory
    ```console
    jovyan@jupyter-yourcuid:~$ cd build/
    ```  
    * Run `CMake` to set up the build environment (creates files in _build_ subdirectory that are needed to build the application)
    ```console
    jovyan@jupyter-yourcuid:~$ cmake ..
    ``` 
    * Now compile and build the executables:
    ```console
    jovyan@jupyter-yourcuid:~$ make
    ``` 
    * Now we have two executable ready to run, `run_app_1` and `run_tests_1` (Note: in future assignments, you will sometimes have more than one `run_app` and run_tests executable.) 
        * `run_app_1` is the executable that was build using your `/app_1` and `/code_1` source code files. You can use this to try a `Hello World` type of program to get familiar with the framework. 
        * `run_tests_1` is the executable containing the test cases that will be used for your assignment. Running this prior to solving any of the required problems should give you a score of 0.
        * Both executables will be located within the build directory, so run the following terminal command to execute:  
    ```console
    jovyan@jupyter-yourcuid:~$ ./run_app_1
    ``` 
    
8. Each time you modify one of the source files (i.e. main_1.cpp) you must rebuild the executables. Each one of these steps is critical to getting your changed code to be executed. 
    * Save your changes to disk.  The compiler will only see the changes that have been saved to disk.
    * Issue ```make``` command (must be run from the ```build``` directory).  This  will recompile the needed source files and rebuild the executables.
    * Run the application or run the tests.  

## Completing the Assignment
For this assignment, we intentionally made this part trivial. In the future assignments, the initial setup steps described above should only take a moment to complete for any assignment.  The bulk of your required work will be described in this section.
1. After running the application, determine what is being tested for this assignment See the __Test Cases__ section below.
2. Make a modification to the code to __Pass__ the test. (hint: each time you make changes to the code, be sure to save your edits to the code, _make_ the application with the new code, and then test the resulting application)
3. We suggest that you save your save the version of your code each time you get a test to pass. Make sure to save it both locally and on the GitHub server. 

### Checking code into GitHub
**Important:** one of the main advantages of using git and GitHub is that it gives you a very convenient way to back up your changes. For now, you will only need to know how to `add`, `commit`, and `push`.  (You are encouraged to learn further git commands throughout the semester.) Any time you get to a point where you want to save your code (for example, you got a function to pass a test case), do the following in the terminal:
1. Stage your changes for a commit. This means that any changes you want to save, need to be added explicitly. (Note that you have all kinds of files that are present in your repository. You only need to add the ones you have changed and want to save.) For example, let's say we want to stage the changes we made in `functions.cpp`. 
    ```console
    $ git add functions.cpp
    ```
2. Commit the changes to our local repository. The ```-m``` option allows you to add the required commit comment on the cmmand line.  Use a short comment that has meaning about what changes were made (e.g. "fixed output for test 2" or "added comments to all functions") 
    ```console
    $ git commit -m 'this is my first commit'
    ```
3. Finally, push the changes from your local version of the repo to the remote repo on GitHub. 
    ```console
    $ git push
    ```
You can run the above steps as many times as you want. Each time you commit/push your changes, a new commit number will be added to your repository. If ever you need to go back to a previous commit, you can fairly easily. However, further git discussion is beyond the scope of this course. 

### Test Cases
Open up the test code file `/tests/test_preview.cpp` to see what test cases you need to pass to get points on the assignment. 

#### Part 1
In `test_preview.cpp` scroll down until you find the test function labeled `TestFooA`. You can see that this is a unit test for the `fooA()` function. An assert is used to check the output for correctness. Go to `/code_1/functions.cpp` to see if you can implement this function to return the correct output (again, this is intentionally trivial.) Once you have written the code and you want to check your solution, run `make` (remember to stay in the `build` directory). Then run the test executable `run_tests_1` and see if you pass the first test case. *If you are happy with your code, go ahead and run through the steps described above in the Checking code into GitHub section.*

#### Part 2
Now let's take a look at the next test case, `TestApp_1`. This one actually runs your `main()` function to check whether it prints the desired results in `stdout`. Look at the test case to see what the desired result needs to be, then go into `/app_1/main_1.cpp` and add the code to get a matching result.


## Submission
In order to submit your assignment, paste your GitHub repository link into the INGInious item for Assignment-0 provided on Moodle. Make sure you do submit your assignment prior to the deadline specified on Moodle. INGInious will pull the files from `code_1` and `app_1` directories and grade them using the same set of test cases as given in `test_preview.cpp`. 
