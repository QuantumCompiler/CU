# Variables
CSPBENCYDIR="CSPB Encyclopedia"
ENCYCDIR="Encyclopedia"
CSPB2270NOTEDIR="CSPB 2270 - Data Structures/Notes/Class Notes"
CSPB2400NOTEDIR="CSPB 2400 - Computer Systems/Notes/Class Notes"
CSPB2820NOTEDIR="CSPB 2820 - Linear Algebra With Computer Science Applications/Notes/Class Notes"
CSPB2824NOTEDIR="CSPB 2824 - Discrete Structures/Notes/Class Notes"
CSPB3022NOTEDIR="CSPB 3022 - Introduction To Data Science With Probability And Statistics/Notes/Class Notes"
CSPB3104NOTEDIR="CSPB 3104 - Algorithms/Notes/Class Notes"
CSPB3155NOTEDIR="CSPB 3155 - Principles Of Programming Languages/Notes/Class Notes"
CSPB3202NOTEDIR="CSPB 3202 - Introduction To Artificial Intelligence/Notes/Class Notes"
SCRIPTSDIR="Scripts"
ENCYCDIR="Encyclopedia"
LATEXDIR="LaTeX"

cd ..
cd "$CSPBENCYDIR"

# Encyclopedia Set Up

if [ -d "$ENCYCDIR" ]; then
    rm -rf $ENCYCDIR
    echo && echo "Successfully deleted previous Encyclopedia directory." && echo
    mkdir $ENCYCDIR
    echo "Created a new Encyclopedia directory." && echo
else
    mkdir $ENCYCDIR
    echo && echo "Created a new Encyclopedia directory." && echo
fi

cd ..

# 2270 Compiling

# cd "$CSPB2270NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC2270DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2270 - Data Structures"

# mkdir "$ENCYC2270DIR"

# cp main.pdf "$ENCYC2270DIR/CSPB 2270 - Data Structures Class Notes.pdf"

# cp -r "Exam Notes" "$ENCYC2270DIR"

# cp -r "Exams" "$ENCYC2270DIR"

# cp -r "Interview Notes" "$ENCYC2270DIR"

# cp -r "Lecture Notes" "$ENCYC2270DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 2270 Compiled Successfully"

# 2400 Compiling

# cd "$CSPB2400NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC2400DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2400 - Computer Systems"

# mkdir "$ENCYC2400DIR"

# cp main.pdf "$ENCYC2400DIR/CSPB 2400 - Computer Systems Class Notes.pdf"

# cp -r "Exam Notes" "$ENCYC2400DIR"

# cp -r "Exams" "$ENCYC2400DIR"

# cp -r "Lecture Notes" "$ENCYC2400DIR"

# cp -r "Quizzes" "$ENCYC2400DIR"

# cp -r "Textbook" "$ENCYC2400DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 2400 Compiled Successfully"

# 2820 Compiling

# cd "$CSPB2820NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC2820DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2820 - Linear Algebra With Computer Science Applications"

# mkdir "$ENCYC2820DIR"

# cp main.pdf "$ENCYC2820DIR/CSPB 2820 - Linear Algebra With Computer Science Applications Class Notes.pdf"

# cp -r "Assignments" "$ENCYC2820DIR"

# cp -r "Exam Notes" "$ENCYC2820DIR"

# cp -r "Lecture Notes" "$ENCYC2820DIR"

# cp -r "Quizzes" "$ENCYC2820DIR"

# cp -r "Textbook" "$ENCYC2820DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 2820 Compiled Successfully"

# 2824 Compiling

# cd "$CSPB2824NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC2824DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2824 - Discrete Structures"

# mkdir "$ENCYC2824DIR"

# cp main.pdf "$ENCYC2824DIR/CSPB 2824 - Discrete Structures Class Notes.pdf"

# cp -r "Assignments" "$ENCYC2824DIR"

# cp -r "Exams" "$ENCYC2824DIR"

# cp -r "Lecture Notes" "$ENCYC2824DIR"

# cp -r "Quizzes" "$ENCYC2824DIR"

# cp -r "Textbook" "$ENCYC2824DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 2824 Compiled Successfully"

# 3022 Compiling

# cd "$CSPB3022NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC3022DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3022 - Introduction To Data Science With Probability And Statistics"

# mkdir "$ENCYC3022DIR"

# cp main.pdf "$ENCYC3022DIR/CSPB 3022 - Introduction To Data Science With Probability And Statistics Class Notes.pdf"

# cp -r "Exam Notes" "$ENCYC3022DIR"

# cp -r "Exams" "$ENCYC3022DIR"

# cp -r "Lecture Notes" "$ENCYC3022DIR"

# cp -r "Quizzes" "$ENCYC3022DIR"

# cp -r "Textbook" "$ENCYC3022DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 3022 Compiled Successfully"

# 3104 Compiling

# cd "$CSPB3104NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC3104DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3104 - Algorithms"

# mkdir "$ENCYC3104DIR"

# cp main.pdf "$ENCYC3104DIR/CSPB 3104 - Algorithms Class Notes.pdf"

# cp -r "Exam Notes" "$ENCYC3104DIR"

# cp -r "Exams" "$ENCYC3104DIR"

# cp -r "Lecture Notes" "$ENCYC3104DIR"

# cp -r "Quizzes" "$ENCYC3104DIR"

# cp -r "Textbook" "$ENCYC3104DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 3104 Compiled Successfully"

# 3155 Compiling

# cd "$CSPB3155NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC3155DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3155 - Principles Of Programming Languages"

# mkdir "$ENCYC3155DIR"

# cp main.pdf "$ENCYC3155DIR/CSPB 3155 - Principles Of Programming Languages Class Notes.pdf"

# cp -r "Exam Notes" "$ENCYC3155DIR"

# cp -r "Exams" "$ENCYC3155DIR"

# cp -r "Lecture Notes" "$ENCYC3155DIR"

# cp -r "Quizzes" "$ENCYC3155DIR"

# cp -r "Textbook" "$ENCYC3155DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 3155 Compiled Successfully"

# 3202 Compiling

# cd "$CSPB3202NOTEDIR"

# pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1

# ENCYC3202DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3202 - Introduction To Artificial Intelligence"

# mkdir "$ENCYC3202DIR"

# cp main.pdf "$ENCYC3202DIR/CSPB 3202 - Introduction To Artificial Intelligence Class Notes.pdf"

# cp -r "Assignments" "$ENCYC3202DIR"

# cp -r "Exam Notes" "$ENCYC3202DIR"

# cp -r "Exams" "$ENCYC3202DIR"

# cp -r "Lecture Notes" "$ENCYC3202DIR"

# cp -r "Quizzes" "$ENCYC3202DIR"

# cp -r "Textbook" "$ENCYC3202DIR"

# git restore main.pdf

# cd ../../../

# echo "CSPB 3202 Compiled Successfully"