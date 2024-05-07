##
##

CXX	=g++
##
## Use our standard compiler flags for the course...
## You can try changing these flags to improve performance.
##
## -march=native: Compiler generates code optimized for the specific architecture of the machine
## -0fast: Enables all optimizations from -03, makes aggressive optimizations
## -funroll-loops: Unrolls loops to reduce the overhead of the loop condition and increases the speed of the loop
## -maxv2: Processes more data per clock cycle
## -fopenmp: Enables parallel programming, i.e. allows for multi threading, designating multiple cores for the process
CXXFLAGS= -g -march=native -Ofast -funroll-loops -mavx2 -fno-omit-frame-pointer -Wall -fopenmp

goals: filter judge
	@echo "Done"

filter: FilterMain.cpp Filter.cpp cs1300bmp.cc cs1300bmp.h Filter.h rdtsc.h
	$(CXX) $(CXXFLAGS) -o filter FilterMain.cpp Filter.cpp cs1300bmp.cc

##
## Parameters for the test run
##
FILTERS = gauss.filter vline.filter hline.filter emboss.filter
IMAGES = boats.bmp blocks-small.bmp
TRIALS = 1 2 3 4

#
# Run the Judge script to compute a score
#
judge: filter
	@echo Running run for performance / scoring information
	./Judge -p ./filter -i blocks-small.bmp
	@echo Now checking if the output is correct. Any errors indicate bugs in your code.
	@cmp filtered-avg-blocks-small.bmp tests/filtered-avg-blocks-small.bmp
	@cmp filtered-emboss-blocks-small.bmp tests/filtered-emboss-blocks-small.bmp
	@cmp filtered-gauss-blocks-small.bmp tests/filtered-gauss-blocks-small.bmp
	@cmp filtered-hline-blocks-small.bmp tests/filtered-hline-blocks-small.bmp

#
# Run the Judge tests on both images and then compare the output to the reference output.
#
# Note you shouldn't use this to compute a score -- it's just for testing
#
test:	filter
	./Judge -p ./filter -i boats.bmp
	./Judge -p ./filter -i blocks-small.bmp
	cmp filtered-avg-blocks-small.bmp tests/filtered-avg-blocks-small.bmp
	cmp filtered-avg-boats.bmp tests/filtered-avg-boats.bmp
	cmp filtered-emboss-blocks-small.bmp tests/filtered-emboss-blocks-small.bmp
	cmp filtered-emboss-boats.bmp tests/filtered-emboss-boats.bmp
	cmp filtered-gauss-blocks-small.bmp tests/filtered-gauss-blocks-small.bmp
	cmp filtered-gauss-boats.bmp tests/filtered-gauss-boats.bmp
	cmp filtered-hline-blocks-small.bmp tests/filtered-hline-blocks-small.bmp
	@echo All tests passed

clean:
	-rm -f *.o
	-rm -f filter
	-rm -f filtered-*.bmp
