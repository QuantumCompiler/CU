# Builds the shell program and runs it
all: build-shell run-shell

# Build the shell program and change permissions
build-shell:
	gcc -o shell shell.c
	chmod +x shell

# Clean up the directory of excess files and or directories
clean: 
	rm -f *.o
	rm -f shell
	rm -f test.sh
	rm -rf shell.dSYM

# Run the shell program
run-shell:
	./shell