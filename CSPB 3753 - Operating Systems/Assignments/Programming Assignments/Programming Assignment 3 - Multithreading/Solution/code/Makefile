# Make file for PA-3

all:
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "TITLE: PA-3 - Multi-threaded DNS Lookup\n"
	@echo "AUTHOR: Taylor Larrechea\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "NAME:\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "	multi-lookup - A multi-threaded C program that resolves domain names to their IP addresses.\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "SYNOPSIS:\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "	./multi-lookup <# of parser threads> <# of converter threads> <input files> <parsing log> <converter log> [ <datafile> ...]\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "DESCRIPTION:\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "	This program when ran with its parameters will take file(s) and pass them into a parser thread where"
	@echo "	the information from these threads will be stored in the shared resource. The converter threads will"
	@echo "	then take the information from the shared resource and find the corresponding IP address.\n"
	@echo "	This program is designed to run with multiple parser and converter threads where safe access to the"
	@echo "	shared resource that is created from the parser thread(s) is ensured.\n"
	@echo "	<# parsing threads > - Integer number of parser threads to place into pool"
	@echo "	<# converter threads> - Integer number of converter threads to place into pool"
	@echo "	<parsing log> - File name to where the pareser status will be written to"
	@echo " 	<conversion log> - File name to where the converter status will be written to"
	@echo "	<datafile> - File name(s) (a list of) to where the domain names are stored\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "OPTIONS:\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"
	@echo "	make sinpar_sincov - Test the single parser single converter thread with prebuilt tests."
	@echo "	make sinpar_mulcov - Test the single parser multiple converter threads with prebuilt tests."
	@echo "	make mulpar_sincov - Test the multiple parser single converter thread with prebuilt tests."
	@echo "	make mulpar_mulcov - Test the multiple parser multiple converter threads with prebuilt tests.\n"
	@echo "	make build - Build the multi-lookup executable."
	@echo "	make clean - Remove all output files and executables."
	@echo "	make test - Run all tests with preconfigured files.\n"
	@echo "----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n"

# Single Parser Single Converter Thread Test
sinpar_sincov:
	@echo "\nRunning Test: Single parser and converter thread\n"
	@gcc sinpar_sincov.c parcov.c custom.c util.c -o sinpar_sincov -lpthread
	@chmod +rwx sinpar_sincov
	./sinpar_sincov output/SPSC_One_File_ParserLog_n1.txt output/SPSC_One_File_ConverterLog_n1.txt input/names1.txt
	./sinpar_sincov output/SPSC_One_File_ParserLog_n2.txt output/SPSC_One_File_ConverterLog_n2.txt input/names2.txt
	./sinpar_sincov output/SPSC_One_File_ParserLog_n3.txt output/SPSC_One_File_ConverterLog_n3.txt input/names3.txt
	./sinpar_sincov output/SPSC_One_File_ParserLog_n4.txt output/SPSC_One_File_ConverterLog_n4.txt input/names4.txt
	./sinpar_sincov output/SPSC_One_File_ParserLog_n5.txt output/SPSC_One_File_ConverterLog_n5.txt input/names5.txt
	./sinpar_sincov output/SPSC_Multi_File_ParserLog_n15.txt output/SPSC_Multi_File_ConverterLog_n15.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt input/names5.txt

# Single Parser Multiple Converter Thread Test
sinpar_mulcov:
	@echo "\nRunning Test: Single parser, multiple converter threads\n"
	@gcc sinpar_mulcov.c parcov.c custom.c util.c -o sinpar_mulcov -lpthread
	@chmod +rwx sinpar_mulcov
	./sinpar_mulcov 1 output/SPMC_One_File_ParserLog_n1-1.txt output/SPMC_One_File_ConverterLog_n1-1.txt input/names1.txt
	./sinpar_mulcov 2 output/SPMC_Multi_File_ParserLog_n12-2.txt output/SPMC_Multi_File_ConverterLog_n12-2.txt input/names1.txt input/names2.txt
	./sinpar_mulcov 3 output/SPMC_Multi_File_ParserLog_n13-3.txt output/SPMC_Multi_File_ConverterLog_n13-3.txt input/names1.txt input/names2.txt input/names3.txt
	./sinpar_mulcov 4 output/SPMC_Multi_File_ParserLog_n14-4.txt output/SPMC_Multi_File_ConverterLog_n14-4.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt
	./sinpar_mulcov 5 output/SPMC_Multi_File_ParserLog_n15-5.txt output/SPMC_Multi_File_ConverterLog_n15-5.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt input/names5.txt

# Multiple Parser Multiple Converter Thread Test
mulpar_mulcov:
	@echo "\nRunning Test: Multiple parser, multiple converter threads\n"
	@gcc mulpar_mulcov.c parcov.c custom.c util.c -o mulpar_mulcov -lpthread
	@chmod +rwx mulpar_mulcov
	./mulpar_mulcov 1 1 output/MPMC_One_File_ParserLog_n1-11.txt output/MPMC_One_File_ConverterLog_n1-11.txt input/names1.txt
	./mulpar_mulcov 2 2 output/MPMC_Multi_File_ParserLog_n12-22.txt output/MPMC_Multi_File_ConverterLog_n12-22.txt input/names1.txt input/names2.txt
	./mulpar_mulcov 3 3 output/MPMC_Multi_File_ParserLog_n13-33.txt output/MPMC_Multi_File_ConverterLog_n13-33.txt input/names1.txt input/names2.txt input/names3.txt
	./mulpar_mulcov 4 4 output/MPMC_Multi_File_ParserLog_n14-44.txt output/MPMC_Multi_File_ConverterLog_n14-44.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt
	./mulpar_mulcov 5 5 output/MPMC_Multi_File_ParserLog_n15-55.txt output/MPMC_Multi_File_ConverterLog_n15-55.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt input/names5.txt

# Multiple Parser Single Converter Thread Test
mulpar_sincov:
	@echo "\nRunning Test: Multiple parser, single converter thread\n"
	@gcc mulpar_sincov.c parcov.c custom.c util.c -o mulpar_sincov -lpthread
	@chmod +rwx mulpar_sincov
	./mulpar_sincov 1 output/MPSC_One_File_ParserLog_n1.txt output/MPSC_One_File_ConverterLog_n1.txt input/names1.txt
	./mulpar_sincov 2 output/MPSC_Multi_File_ParserLog_n12.txt output/MPSC_Multi_File_ConverterLog_n12.txt input/names1.txt input/names2.txt
	./mulpar_sincov 3 output/MPSC_Multi_File_ParserLog_n13.txt output/MPSC_Multi_File_ConverterLog_n13.txt input/names1.txt input/names2.txt input/names3.txt
	./mulpar_sincov 4 output/MPSC_Multi_File_ParserLog_n14.txt output/MPSC_Multi_File_ConverterLog_n14.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt
	./mulpar_sincov 5 output/MPSC_Multi_File_ParserLog_n15.txt output/MPSC_Multi_File_ConverterLog_n15.txt input/names1.txt input/names2.txt input/names3.txt input/names4.txt input/names5.txt

# Build
build:
	@echo "\nBuilding multi-lookup executable.\n"
	@gcc multi-lookup.c parcov.c custom.c util.c -o multi-lookup -lpthread
	@chmod +rwx multi-lookup

# Run All Tests
test:
	@echo "\nRunning All Tests With Preconfigured Files\n"
	make sinpar_sincov
	make sinpar_mulcov
	make mulpar_sincov
	make mulpar_mulcov

# Clean Up
clean:
	@rm -f output/*.txt
	@rm -f sinpar_sincov
	@rm -f sinpar_mulcov
	@rm -f mulpar_sincov
	@rm -f mulpar_mulcov
	@rm -f multi-lookup