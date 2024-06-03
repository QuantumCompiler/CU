// 
// tsh - A tiny shell program with job control
// 
// <Put your name and login ID here>
//

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h"
#include "jobs.h"
#include "helper-routines.h"

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];

    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}
  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
/* eval - Executes a built in command or forks a child process if it is not a built in command
  Input:
    cmdline - Character that represents what type of execution needs to take place
  Algorithm:
    * Check that the command is not a built in command
      * If it is, block certain processes from exectuting
      * Fork a child process
      * If the process is invalid, output that a unix error has occurred
      * If the process is valid
        * Handle the case were the ID is invalid
        * Load and run the job if it is valid
          * If it is not, output that the command is not found
    * If the command is a built in command
      * Add the job as either a background or foreground process
      * Unblock the signal
      * If the job is a foreground process
        * Wait for it to finish executing
      * Otherwise
        * Output the background process with ID
  Output:
    This is a void function and does not return any values
*/
void eval(char *cmdline) 
{
  /* Parse command line */
  //
  // The 'argv' vector is filled in by the parseline
  // routine below. It provides the arguments needed
  // for the execve() routine, which you'll need to
  // use below to launch a process.
  //
  char *argv[MAXARGS];
  //
  // The 'bg' variable is TRUE if the job should run
  // in background mode or FALSE if it should run in FG
  //
  int bg = parseline(cmdline, argv); 
  if (argv[0] == NULL)  
    return;   /* ignore empty lines */
  // Check that the command is not a built in command
  if (!builtin_cmd(argv)) { 
    // Signal mask
    sigset_t mask;
    // Block SIGCHLD, SIGINT, and SIGSTP until job is added due to possible race conditions
    if (sigemptyset(&mask) < 0) {
      unix_error("sigemptyset error");
    }
    if (sigaddset(&mask, SIGCHLD)) {
      unix_error("sigaddset error");
    }
    if (sigaddset(&mask, SIGINT)) {
      unix_error("sigaddset error");
    }
    if (sigaddset(&mask, SIGTSTP)) {
      unix_error("sigaddset error");
    }
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
      unix_error("sigprocmask error");
    }
    // Create child process
    pid_t pid = fork();
    // Check for invalid child process
    if (pid  < 0) {
      unix_error("fork error");
    }
    // Check for valid child process
    if (pid == 0) {
      // Unblock signals
      sigprocmask(SIG_UNBLOCK, &mask, NULL);
      // Error handling if ID is invalid (can't send ctrl-c and ctrl-z)
      if (setpgid(0, 0) < 0) {
        unix_error("setpgid error"); 
      }
      // Command is not found
      if (execve(argv[0], argv, environ) < 0) {
        printf("%s: Command not found\n", argv[0]);
        exit(0);
      }
    }
    // Job is a background process
    if (bg) {
      addjob(jobs, pid, BG, cmdline);
    }
    // Job is a foreground process
    else {
      addjob(jobs, pid, FG, cmdline);
    }
    // Unblock the signal by referencing the mask
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    // Wait for foreground job to finish execution
    if (!bg)  {
      waitfg(pid);
    }
    // Output background job
    else {
      printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
    }
  }
  return;
}
////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
/* builtin_cmd - Executes built in commands of this shell
  Input:
    argv - Argument that is being checked if it is a built in command
  Algorithm:
    * Cast the input as a C++ string
    * Exit the execution if the command is "quit"
    * List the jobs if the command is "jobs"
    * Call "do_bgfg" if the command is either "bg" or "fg"
  Output:
    This is a void function and does not return a value
*/
int builtin_cmd(char **argv) {
  string cmd(argv[0]);
  if (cmd == "quit") {
    exit(0);  
  }
  if (cmd == "jobs") {
    listjobs(jobs);
    return 1;    
  }
  if (cmd == "bg" || cmd == "fg") {
    do_bgfg(argv);
    return 1;
  }
  return 0;     /* not a builtin command */
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
/* do_bgfg - Changes the state of a job to either background or foreground
  Input:
    argv - Argument that is being fed into the function
  Algorithm:
    * Cast the input argument as a C++ string
    * Check if the command is a background process
      * If it is, check for the invalid killing of the process
        * It is is invalid, output that a unix error has occurred
      * Change the state of the job to background
      * Output that the state has changed to background
    * Check if the command is a foreground process
      * If it is, check for the invalid killing of the process
        * It is is invalid, output that a unix error has occurred
      * Change the state of the job to foreground
      * Wait for the foreground process to finish executing
    * Handle the exception that an error has occurred
  Output:
    This is a void function and does not return a value
*/
void do_bgfg(char **argv) {
  struct job_t *jobp=NULL;
  /* Ignore command if no argument */
  if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid_t pid = atoi(argv[1]);
    if (!(jobp = getjobpid(jobs, pid))) {
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {
    int jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }
  // the variable 'jobp' is the job pointer
  //
  // Your actions will depend on the specified command
  // so we've converted argv[0] to a string (cmd) for
  // your benefit.
  //
  // Cast the input parameter as a C++ string
  string cmd(argv[0]);
  // Command is for a background process
  if (cmd == "bg") {
    // Check if the killing of all the processes of a specific ID that belong to the job is invalid
    if (kill(-(jobp->pid), SIGCONT) < 0) {
      unix_error("kill (bg) error");
    }
    // Change the state of the job to background
    jobp->state = BG;
    printf("[%d] (%d) %s", jobp->jid, jobp->pid, jobp->cmdline);
  }
  // Command is for a foreground process
  else if (cmd == "fg") {
    // Check if the killing of all the processes of a specific ID that belong to the job is invalid
    if (kill(-(jobp->pid), SIGCONT) < 0) {
      unix_error("kill (fg) error");
    }
    // Change the state of the job to foreground
    jobp->state = FG;
    // Wait for foreground process to finish executing
    waitfg(jobp->pid);
  }
  // Error has occurred
  else {
    printf("do_bgfg: Internal error\n");
    exit(0);
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
/* waitfg - Blocks until a process is no longer considered the foreground process
  Input:
    pid - pid_t that represents the process in question
  Algorithm:
    * Create a variable to represent the job in question
    * Check if the job is not valid
      * If it isn't valid, end the execution
    * Pause the execution until the foreground process is no more
    * Check if the verbose flag is currently set
      * If it is, output that the process is no longer a foreground process with its corresponding ID
  Output:
    This is a void function and does not return a variable, it pauses execution
*/
void waitfg(pid_t pid) {
  // Get the present job ID
  struct job_t *j = getjobpid(jobs, pid);
  // Check if the job is not valid
  if (!j) {
    return;
  }
  // Pause while the process is currently a foreground process
  while (j->pid == pid && j->state == FG) {
    pause();
  }
  // Check if the verbose flag is currently set
  if (verbose) {
    printf("waitfg: Process (%d) no longer the fg process\n", pid);
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//

/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
/* sigchld_handler - Handles child processes by tracking certain aspects about them
  Input:
    sig - Integer value that represents the signal that is to be tracked
  Algorithm:
    * Create a variable for the child process with its ID
    * Create a variable for the child processes job ID
    * Create a variable for the status of the process
    * Loop until the child process is no longer valid (terminated or exited)
      * Check if the child process was stopped
        * If it was, grab the job ID
        * Check if the job status is not valid
          * If it is not, output that it was lost and terminate the loop
        * Change the state of the job to stopped
        * Ouput what signal caused it to stop
      * Check if the child process was terminated
        * If it was, grab the job ID of the process
        * Check if the job was successfully deleted
          * If it was, check for if the verbose flag was set
            * It it was, output to console that the job was deleted by its corresponding signal
          * Output that the job was terminated by its corresponding signal
      * Check for if the job was terminated successfully
        * If it was, get the job ID 
        * Check if the job was successfully deleted
          * If it was, check if the verbose flag was set
            * It it was, output to console that the job was successfully terminated by the specific job ID
        * It it wasn't, output that a unix error has occurred
    * Check for termination of waitpid by checking if there are no zombie children, or if there were not children at all
      * If this fails, output that a unix error has occurred
    * Check for if the verbose flag was set
      * It it is, output that the function is exiting
  Output:
    This is a void function and does not return a value
*/
void sigchld_handler(int sig) {
  pid_t child_pid;
  int child_jid;
  int status;
  // While the child process is still valid, execute the following
  while ((child_pid = waitpid(-1, &status, WNOHANG|WUNTRACED)) > 0) { 
    // Check if the child process was stopped
    if (WIFSTOPPED(status)) {
      // Grab the job ID
      struct job_t *j = getjobpid(jobs, child_pid);
      // If the job is not valid, indicate it was lost
      if (!j) {
        printf("Lost track of (%d)\n", child_pid);
        return;
      }
      // Change the state of the job to stopped
      j->state = ST;
      // Output that the job was stopped and by what signal
      fprintf(stdout, "Job [%d] (%d) stopped by signal %d\n", pid2jid(child_pid), child_pid, WSTOPSIG(status));
    }
    // Check if the child process was terminated
    else if (WIFSIGNALED(status)) { 
      // Get job ID of process
      child_jid = pid2jid(child_pid);
      // Check for valid job deletion
      if (deletejob(jobs, child_pid)) {
        // Check for verbose flag being set
        if (verbose) {
          printf("sigchld_handler: Job [%d] (%d) deleted\n", child_jid, child_pid);
        }
        // Output what signal terminated the job
        fprintf(stdout, "Job [%d] (%d) terminated by signal %d\n", child_jid, child_pid, WTERMSIG(status));
      }
    }
    // Check for if the job was terminated normally
    else if (WIFEXITED(status)) {
      // Get job ID of process
      child_jid = pid2jid(child_pid);
      // Check for valid deletion
      if (deletejob(jobs, child_pid)) {
        // Check for verbose flag being set
        if (verbose) {
          printf("sigchld_handler: Job [%d] (%d) terminates OK (status %d)\n", child_jid, child_pid, WEXITSTATUS(status));
        }
      }
    }
    // Job was not terminated successfully
    else {
      unix_error("waitpid error");
    }
  }
  // Handle instance that waitpid was not terminated successfully
  if (!((child_pid == 0) || (child_pid == -1 && errno == ECHILD))) {
    unix_error("sigchld_handler wait error");
  }
  // Check for verbose flag being set
  if (verbose) {
    printf("sigchld_handler: exiting\n");
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
/* sigint_handler - Terminates a process
  Input:
    sig - Integer value that represents the signal process that was caught
  Algorithm:
    * Create a variable called "pid" that represents the ID of the foreground job that needs to be terminated
    * Check if the verbose flag is set
      * If it is, then output a message to console indicating that sigstp_handler is starting
    * Get the ID from the foreground jobs that are running, check if it is greater than 0
      * If the termination of the current process is less than zero
        * Use "unix_error" to output that an error has occurred
      * Check again if the verbose flag is set
        * If it is, output to console the process ID
    * Check for verbose again
      * If true, signal that the suspension has concluded
  Output:
    This is a void function and does not return a value, it terminates a foreground process if present
*/
void sigint_handler(int sig) {
  // ID of foreground job
  pid_t pid;
  // Check for verbose flag
  if (verbose) {
    printf("sigint_handler: entering\n");
  }
  // Check for valid foreground process
  if ((pid = fgpid(jobs)) > 0) {
    // Kill the process if for all processes that belong to the PID (that is what the negative sign means)
    if (kill(-pid, SIGINT) < 0) {
      unix_error("kill (sigint) error");
    }
    // Check for verbose flag again
    if (verbose) {
      printf("sigint_handler: Job (%d) killed\n", pid);
    }
  }
  // Check for verbose flag once again
  if (verbose) {
    printf("sigint_handler: exiting\n");
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
/* sigtstp_handler - Suspsends a process without completely terminating it
  Input:
    sig - Integer value that represents the signal process that was caught
  Algorithm:
    * Create a variable called "pid" that represents the ID of the foreground job that needs to be suspended
    * Check if the verbose flag is set
      * If it is, then output a message to console indicating that sigstp_handler is starting
    * Get the ID from the foreground jobs that are running, check if it is greater than 0
      * If the termination of the current process is less than zero
        * Use "unix_error" to output that an error has occurred
      * Check again if the verbose flag is set
        * If it is, output to console the process ID
    * Check for verbose again
      * If true, signal that the suspension has concluded
  Output:
    This is a void function and does not return a value, it suspends a foreground process if present
*/
void sigtstp_handler(int sig) {
  // ID of foreground job
  pid_t pid;
  // Check for verbose flag
  if (verbose) {
    printf("sigtstp_handler: entering\n");
  }
  // Check for valid foreground process
  if ((pid = fgpid(jobs)) > 0) {
    // Kill the process if for all processes that belong to the PID (that is what the negative sign means)
    if (kill(-pid, SIGTSTP) < 0) {
      unix_error("kill (tstp) error");
    }
    // Check for verbose flag again
    if (verbose) {
      printf("sigtstp_handler: Job [%d] (%d) stopped\n", pid2jid(pid), pid);
    }
  }
  // Check for verbose flag once again
  if (verbose) {
    printf("sigtstp_handler: exiting\n");
  }
  return;
}