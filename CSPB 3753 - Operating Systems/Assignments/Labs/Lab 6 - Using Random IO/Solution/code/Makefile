# Run the example_cmd_handler
ALL: example_cmd_handler

# Compile the example_cmd_handler
example_cmd_handler: example_cmd_handler.c debug_3753.h
	gcc -g  -o example_cmd_handler example_cmd_handler.c

taylor_example: example.c
	gcc -g -o example example.c
	./example

# Run the example_cmd_handler with the sample_1.cmd
test1: example_cmd_handler
	cp data_orig.txt data.txt
	./example_cmd_handler < sample_1.cmd 2>log.txt

# Run the example_cmd_handler with the sample_2.cmd
test2: example_cmd_handler
	cp data_orig.txt data.txt
	./example_cmd_handler < sample_2.cmd 2>log.txt

# Clean the unnecessary files
clean:
	rm -f ./example_cmd_handler data.txt log.txt
	rm -f ./example
	rm -rf ./example_cmd_handler.dSYM
	rm -rf ./example.dSYM
