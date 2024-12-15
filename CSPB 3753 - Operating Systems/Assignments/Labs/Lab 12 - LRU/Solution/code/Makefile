# Bio of assignment
ALL:
	@echo "\nLab 12 - LRU Cache Data Structure\n"
	@echo "Author: Taylor Larrechea"
	@echo "Date: 11/20/24"
	@echo "Course: CSPB 3753 - Operating Systems"
	@echo "Instructor: Dr. David Knox\n"
	@echo "Makefile Options:\n"
	@echo "  make build - Build the LRU Cache executable"
	@echo "  make clean - Remove all .txt and executables"
	@echo "  make test - Run the test suite\n"
	@echo "Executable Usage:\n"
	@echo "  ./LRUCache <cache_size> <input_file>\n"

# Build the LRU Cache executable
build:
	@echo "\nBuilding LRU Cache...\n"
	@gcc main.c util.c -o LRUCache
	@echo "LRU Cache built.\n"

# Remove all .txt and executables
clean:
	@rm -f *.txt
	@rm -f test
	@rm -f LRUCache

# Run the test suite, output to results.txt
test:
	@echo "\nBuilding test executable...\n"
	@gcc test.c evictTest.c insertTest.c retrieveTest.c util.c -o test
	@echo "Running tests...\n"
	@echo "Tests output to results.txt\n"
	./test > results.txt
	@echo "\nTests completed.\n"