# Default target - Builds program and shows options for use
build:
	gcc -o main main.c lib/read.c lib/write.c -lpthread
	@echo ""
	@echo "Build complete, run the following commands to execute the program:"
	@echo "		make: Builds the program and displays this messsage"
	@echo "		make clean: Removes excess files"
	@echo "		make print: Prints the tests to text files"
	@echo "		make test: Tests the program with default parameters"
	@echo ""
	@echo "Manual use of this program consists of ./main <number of readers> <number of writers>"

# Removes excess files
clean:
	rm -f main
	rm -f *.txt

# Prints the tests to text files
print:
	./main 2 1 > test_2readers_1writer.txt
	@echo "Two readers one writer complete"
	./main 4 2 > test_4readers_2writers.txt
	@echo "Four readers two writers complete"
	./main 8 4 > test_8readers_4writers.txt
	@echo "Eight readers four writers complete"

# Tests the program with default parameters
test:
	@echo ""
	@echo "Executing test with two readers and one writer"
	@echo ""
	./main 2 1
	@echo ""
	@echo "Test with two readers and one writer complete"
	@echo ""
	@echo "Executing test with four readers and two writers"
	@echo ""
	./main 4 2
	@echo ""
	@echo "Test with four readers and two writers complete"
	@echo ""
	@echo "Executing test with eight readers and four writers"
	@echo ""
	./main 8 4
	@echo ""
	@echo "Test with eight readers and four writers complete"
	@echo ""
	@echo "All tests complete"