HOST=cs2400-applied.cs.colorado.edu:15513
ID=$(shell cat ./identikey)

target.tar:
	@echo "Retrieving your attacklab...If this fails, visit http://${HOST} and download manually"
	@echo "---"
	curl "http://${HOST}/?username=${ID}&usermail=${ID}@colorado.edu&" > target.tar
	tar xvf ./target.tar

#
# Determine most recently modified bomb folder. This is what will be auto-graded by default.
#
TARGET = $(shell ls -td target[0-9]* | head -1)

#
# grade individual phases of the ctarget/rtarget
#

grade-ctarget.l1.txt: ${TARGET}/ctarget.l1.txt
	@echo Grading first phases of ${TARGET}/ using ${TARGET}/ctarget.l1.txt
	${TARGET}/hex2raw < ${TARGET}/ctarget.l1.txt | ${TARGET}/ctarget | tee /dev/stderr | grep PASS

grade-ctarget.l2.txt: ${TARGET}/ctarget.l2.txt
	@echo Grading second phases of ${TARGET}/ using ${TARGET}/ctarget.l2.txt
	${TARGET}/hex2raw < ${TARGET}/ctarget.l2.txt | ${TARGET}/ctarget | tee /dev/stderr | grep PASS

grade-ctarget.l3.txt: ${TARGET}/ctarget.l3.txt
	@echo Grading third phases of ${TARGET}/ using ${TARGET}/ctarget.l3.txt
	${TARGET}/hex2raw < ${TARGET}/ctarget.l3.txt | ${TARGET}/ctarget | tee /dev/stderr | grep PASS

grade-rtarget.l2.txt: ${TARGET}/rtarget.l2.txt
	@echo Grading second phases of ${TARGET}/ using ${TARGET}/rtarget.l2.txt
	${TARGET}/hex2raw < ${TARGET}/rtarget.l2.txt | ${TARGET}/rtarget | tee /dev/stderr | grep PASS 

grade-rtarget.l3.txt: ${TARGET}/rtarget.l3.txt
	@echo Grading third phases of ${TARGET}/ using ${TARGET}/rtarget.l3.txt
	${TARGET}/hex2raw < ${TARGET}/rtarget.l3.txt | ${TARGET}/rtarget | tee /dev/stderr | grep PASS
