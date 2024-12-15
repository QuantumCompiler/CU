ALL: get_sys_info get_process_info
PID=1

get_process_info: get_process_info.c 
	gcc -g -o get_process_info get_process_info.c

get_sys_info: get_sys_info.c 
	gcc -g -o get_sys_info get_sys_info.c
	
clean:
	rm ./get_process_info ./get_sys_info
	
test:
	./get_sys_info > results.txt
	./get_process_info PID >> results.txt