ALL: split_cmdline shell 

shell: shell.c split_cmdline.o
	gcc -g split_cmdline.o -o shell shell.c

split_cmdline: split_cmdline.c split_cmdline.h
	gcc -g -c split_cmdline.c

    
test: shell
	echo "this is a test | with other items" > test.sh
	./shell < test.sh

clean: 
	rm *.o 
	rm shell
