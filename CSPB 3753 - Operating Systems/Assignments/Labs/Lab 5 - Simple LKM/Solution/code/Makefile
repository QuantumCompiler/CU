# Changed from hello-1.c to sample_hello.c (File included with assignment)
obj-m += sample_hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	