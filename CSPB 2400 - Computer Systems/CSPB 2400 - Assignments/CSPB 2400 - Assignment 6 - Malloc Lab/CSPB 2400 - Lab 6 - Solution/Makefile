#
# Students' Makefile for the Malloc Lab
#
TEAM = xyzzy
VERSION = 1

CC = cc
CFLAGS = -Wall -Ofast -march=native -funroll-loops -flto

OBJS = mdriver.o mm.o memlib.o fsecs.o fcyc.o clock.o ftimer.o

mdriver: $(OBJS)
	$(CC) $(CFLAGS) -o mdriver $(OBJS)

tests: mdriver
	./mdriver -a -f traces/binary-bal.rep
	./mdriver -a -f traces/binary2-bal.rep
	./mdriver -a -f traces/binary-bal.rep
	./mdriver -a -f traces/binary2-bal.rep
	./mdriver -a -f traces/cccp-bal.rep
	./mdriver -a -f traces/coalescing-bal.rep
	./mdriver -a -f traces/cp-decl-bal.rep
	./mdriver -a -f traces/random-bal.rep
	./mdriver -a -f traces/random2-bal.rep
	./mdriver -a -f traces/realloc-bal.rep
	./mdriver -a -f traces/realloc2-bal.rep

grade:	mdriver
	python3 ./grade-malloc.py

mdriver.o: mdriver.c fsecs.h fcyc.h clock.h memlib.h config.h mm.h
memlib.o: memlib.c memlib.h
mm.o: mm.c mm.h memlib.h
fsecs.o: fsecs.c fsecs.h config.h
fcyc.o: fcyc.c fcyc.h
ftimer.o: ftimer.c ftimer.h config.h
clock.o: clock.c clock.h

clean:
	rm -f *~ *.o mdriver


