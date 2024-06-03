HOST=cs2400-applied.cs.colorado.edu:15213
ID=$(shell cat ./identikey)

default:
	@echo "If you do not already have a bomb, run 'make bomb.tar' to retrieve one'"
	@echo "The automated testing wll use the following make rules"
	@echo "  Grade first 3 phases     --- make grade-first"
	@echo "  Grade remaining phases   --- make grade-rest"
	@echo "  Grade extra credit phase --- make grade-extra"
	@echo "For most of your work, you'll use GDB within the bomb directory"

bomb.tar:
	@echo "Retrieving bomb...If this fails, visit http://${HOST} and download manually"
	@echo "---"
	curl "http://${HOST}/?username=${ID}&usermail=${ID}@colorado.edu&" > bomb.tar
	tar xvf ./bomb.tar	
	git add "`ls -td bomb[0-9]* | head -1`"

#
# Determine most recently modified bomb folder. This is what will be auto-graded by default.
#
BOMB = $(shell ls -td bomb[0-9]* | head -1)

check-for-solution.txt:
	@echo We will use the solution.txt file at ${BOMB}/solution.txt
	test -f ${BOMB}/solution.txt

grade-first: ${BOMB}/solution.txt
	@echo Grading first part of ${BOMB} using ${BOMB}/solution.txt
	awk NF < ${BOMB}/solution.txt | head -3 | GRADE_BOMB=1 ${BOMB}/bomb /dev/stdin | tee /dev/stderr | grep 'Halfway there!'

grade-rest: ${BOMB}/solution.txt
	@echo Grading rest of ${BOMB} using ${BOMB}/solution.txt
	cat ${BOMB}/solution.txt | GRADE_BOMB=1 ${BOMB}/bomb /dev/stdin | tee /dev/stderr | grep "Congratulations! You've defused the bomb!"

grade-extra: ${BOMB}/solution.txt
	@echo Grading extra credit of ${BOMB} using ${BOMB}/solution.txt
	cat ${BOMB}/solution.txt | GRADE_BOMB=1 ${BOMB}/bomb /dev/stdin | tee /dev/stderr | grep "Wow! You've defused the secret stage!"
