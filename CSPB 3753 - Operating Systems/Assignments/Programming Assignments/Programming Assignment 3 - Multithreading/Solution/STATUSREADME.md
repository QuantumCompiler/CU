# Status Update README - PA-3 Update

## <span style="color: red;">Status Update</span> - 11/4/24 - 11/10/24

A small preface, after touching down in Utah after my move my job became extremely demanding and I have been playing catch up in various areas of life. I have finally got myself back into a routine and I expect my performance to improve significantly.

However, in the meantime I initially spent the Monday and Tuesday of this week reviewing the mutex lab as well as the semaphore lab. Today (11/6/24) this is what I did step by step:

After reviewing the two labs and understanding the mistakes from your feedback, I began by moving the input files of this project around to a different location in the repository. I then created a makefile to compile the project when all the files are created for the project. The default target in the makefile 

```
# Make file for PA-3

all:
	@echo "\nTITLE: PA-3 - Multi-threaded DNS Lookup\n"
	@echo "AUTHOR: Taylor Larrechea\n"
	@echo "NAME:\n"
	@echo "	multi-lookup - A multi-threaded C program that resolves domain names to their IP addresses.\n"
	@echo "SYNOPSIS:\n"
	@echo "	./multi-lookup <# of parser threads> <# of converter threads> <input files> <parsing log> <converter log> [ <datafile> ...]\n"
	@echo "DESCRIPTION:\n"
	@echo "	This program when ran with its parameters will take file(s) and pass them into a parser thread where"
	@echo "	the information from these threads will be stored in the shared resource. The converter threads will"
	@echo "	then take the information from the shared resource and find the corresponding IP address.\n"
	@echo "	This program is designed to run with multiple parser and converter threads where safe access to the"
	@echo "	shared resource that is created from the parser thread(s) is ensured.\n"
	@echo "	<# parsing threads > - Integer number of parser threads to place into pool"
	@echo "	<# converter threads> - Integer number of converter threads to place into pool"
	@echo "	<parsing log> - File name to where the pareser status will be written to"
	@echo " 	<conversion log> - File name to where the converter status will be written to"
	@echo "	<datafile> - File name(s) (a list of) to where the domain names are stored\n"
```

can be seen above. The idea is to include the description and usage of the program once the program is compiled. I then proceeded to create the parser thread function and the test for it.


## <span style="color: red;">Step 1 Checkpoint</span> - Parser Thread Function

The files that were produced to accomplish the requirements for this parser thread function were created in ```pa3-QuantumCompiler/code```. The files that were created are as follows:

- ```buffer.h```: Header file that contains the necessary includes and globals for the project.
- ```custom.c```: Source file that contains the implementation of the custom helper functions.
- ```custom.h```: Header file that contains the function prototype(s) for the custom helper functions.
- ```parser.c```: Source file that contains the implementation of the parser thread function.
- ```parser.h```: Header file that contains the function prototype(s) for the parser thread function.
- ```parser_test.c```: Source file that contains the test for the parser thread function.

The parser thread function was written so that it would first validate that the file was able to be opened. Once the file was confirmed to be able to be opened, it proceeds to parse through the file line by line such that the domain names are being stored in the shared buffer. In the midst of adding the domain names to the shared buffer, the parser thread function locks a mutex, adds the domain name to the shared buffer, prints that the domain name was added, and then proceeds to log the message as well.

In the event that the buffer is full, the function will wait until it is not full. It then adds the domain to the buffer, sends a signal, and unlocks the mutex. This process is repeated over and over until all lines are read from the file. Once all lines are read, the file is closed, the log file is updated, and the parser thread function exits.

## <span style="color: red;">Step 2 Checkpoint</span> - Converter Thread Function

The files that were produced to accomplish the requirements for this converter thread function were created in ```pa3-QuantumCompiler/code```. The files that were created are as follows:

- ```converter.c```: Source file that contains the implementation of the converter thread function.
- ```converter.h```: Header file that contains the function prototype(s) for the converter thread function.
- ```converter_test.c```: Source file that contains the test for the converter thread function.

Similar to the parser function, the converter function has some auxiliary files that are used to create its functionality. The converter function essentially reads
from the shared buffer, locks a mutex, reads the domain name from the shared buffer, and then proceeds to take items (domain names) out of the buffer while the mutex is locked. Once this process completes, a signal is sent indicating that the buffer is no longer full, and the mutex is unlocked. This process is repeated until the buffer is empty. During all of this, logs are being constantly kept to make sure that the program status is being stored.

## <span style="color: red;">Step 3 Checkpoint</span> - Mutex Protection

To address the issue of protecting critical sections of the program, the mutex protection was implemented in the parser and converter functions (I actually subconsciously did this before in going over the previous steps). The tests for each of these individually can be seen in the prior checkpoints. For the cohesive nature of the two, the file:

- ```mutex-3.c```: Source file that contains the implementation of the mutex protection for the parser and converter functions in step 3.

The previous source file is designed to test the implementation of the two previous functions that were developed in checkpoints 1 and 2. At the current time of writing this, the tests are currently having a compiling error that is being worked through.