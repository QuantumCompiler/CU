# Make all targets
ALL: gsi gpi
PID=1

# Get process information
gpi: get_process_info.c 
	gcc -g -o get_process_info get_process_info.c

# Get system information
gsi: get_sys_info.c 
	gcc -g -o get_sys_info get_sys_info.c

# Clean up
clean:
	rm ./get_process_info ./get_sys_info

# Run the tests
test:
	./get_sys_info > results.txt
	./get_process_info PID >> results.txt