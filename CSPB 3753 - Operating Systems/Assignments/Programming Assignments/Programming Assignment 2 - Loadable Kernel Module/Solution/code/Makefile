obj-m += char_dev.o

# Default target to build 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Loads and creates the device
build: load device

# Removes the device and unloads the module
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Cleans the directory, removes the device, and unloads it
destroy: clean remove unload

# Creates the device
device:
	@if [ ! -e /dev/char_dev ]; then \
		sudo mknod /dev/char_dev c 374 0; \
		sudo chmod 666 /dev/char_dev; \
	else \
		echo "/dev/char_dev already exists"; \
	fi

# Loads the module
load:
	sudo insmod char_dev.ko

# Removes the device
remove:
	sudo rm -f /dev/char_dev

# Unloads the module
unload:
	sudo rmmod char_dev