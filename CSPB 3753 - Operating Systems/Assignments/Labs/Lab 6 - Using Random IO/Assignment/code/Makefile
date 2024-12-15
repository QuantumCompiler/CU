ALL: example_cmd_handler

example_cmd_handler: example_cmd_handler.c debug_3753.h
	gcc -g  -o example_cmd_handler example_cmd_handler.c

test1: example_cmd_handler
	cp data_orig.txt data.txt
	./example_cmd_handler < sample_1.cmd 2>log.txt

test2: example_cmd_handler
	cp data_orig.txt data.txt
	./example_cmd_handler < sample_2.cmd 2>log.txt

clean:
	rm -f ./example_cmd_handler data.txt log.txt
