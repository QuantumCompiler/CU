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
CSPB3308NOTEDIR="CSPB 3308 - Software Development Methods And Tools/Notes/Class Notes"
CSPB3702NOTEDIR="CSPB 3702 - Cognitive Science/Notes/Class Notes"
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

cd "$CSPB2270NOTEDIR"

ENCYC2270DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2270 - Data Structures"

mkdir "$ENCYC2270DIR"

cp main.pdf "$ENCYC2270DIR/CSPB 2270 - Data Structures Class Notes.pdf"

cp -r "Exam Notes" "$ENCYC2270DIR"

cp -r "Exams" "$ENCYC2270DIR"

cp -r "Interview Notes" "$ENCYC2270DIR"

cp -r "Lecture Notes" "$ENCYC2270DIR"

cd ../../

ENCYC2270DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 2270 - Data Structures"

cp -r "Syllabus" "$ENCYC2270DIR"

cp -r "Textbook" "$ENCYC2270DIR"

cd ..

echo "CSPB 2270 Compiled Successfully"

# 2400 Compiling

cd "$CSPB2400NOTEDIR"

ENCYC2400DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2400 - Computer Systems"

mkdir "$ENCYC2400DIR"

cp main.pdf "$ENCYC2400DIR/CSPB 2400 - Computer Systems Class Notes.pdf"

cp -r "Exam Notes" "$ENCYC2400DIR"

cp -r "Exams" "$ENCYC2400DIR"

cp -r "Lecture Notes" "$ENCYC2400DIR"

cp -r "Quizzes" "$ENCYC2400DIR"

cp -r "Textbook" "$ENCYC2400DIR"

cd ../../

ENCYC2400DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 2400 - Computer Systems"

cp -r "Syllabus" "$ENCYC2400DIR"

cd ..

echo "CSPB 2400 Compiled Successfully"

# 2820 Compiling

cd "$CSPB2820NOTEDIR"

ENCYC2820DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2820 - Linear Algebra With Computer Science Applications"

mkdir "$ENCYC2820DIR"

cp main.pdf "$ENCYC2820DIR/CSPB 2820 - Linear Algebra With Computer Science Applications Class Notes.pdf"

cp -r "Assignments" "$ENCYC2820DIR"

cp -r "Exam Notes" "$ENCYC2820DIR"

cp -r "Lecture Notes" "$ENCYC2820DIR"

cp -r "Quizzes" "$ENCYC2820DIR"

cp -r "Textbook" "$ENCYC2820DIR"

cd ../../

ENCYC2820DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 2820 - Linear Algebra With Computer Science Applications"

cp -r "Syllabus" "$ENCYC2820DIR"

cd ..

echo "CSPB 2820 Compiled Successfully"

# 2824 Compiling

cd "$CSPB2824NOTEDIR"

ENCYC2824DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 2824 - Discrete Structures"

mkdir "$ENCYC2824DIR"

cp main.pdf "$ENCYC2824DIR/CSPB 2824 - Discrete Structures Class Notes.pdf"

cp -r "Assignments" "$ENCYC2824DIR"

cp -r "Exams" "$ENCYC2824DIR"

cp -r "Lecture Notes" "$ENCYC2824DIR"

cp -r "Quizzes" "$ENCYC2824DIR"

cp -r "Textbook" "$ENCYC2824DIR"

cd ../../

ENCYC2824DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 2824 - Discrete Structures"

cp -r "Syllabus" "$ENCYC2824DIR"

cd ..

echo "CSPB 2824 Compiled Successfully"

# 3022 Compiling

cd "$CSPB3022NOTEDIR"

ENCYC3022DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3022 - Introduction To Data Science With Probability And Statistics"

mkdir "$ENCYC3022DIR"

cp main.pdf "$ENCYC3022DIR/CSPB 3022 - Introduction To Data Science With Probability And Statistics Class Notes.pdf"

cp -r "Exam Notes" "$ENCYC3022DIR"

cp -r "Exams" "$ENCYC3022DIR"

cp -r "Lecture Notes" "$ENCYC3022DIR"

cp -r "Quizzes" "$ENCYC3022DIR"

cp -r "Textbook" "$ENCYC3022DIR"

cd ../../

ENCYC3022DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 3022 - Introduction To Data Science With Probability And Statistics"

cp -r "Syllabus" "$ENCYC3022DIR"

cd ..

echo "CSPB 3022 Compiled Successfully"

# 3104 Compiling

cd "$CSPB3104NOTEDIR"

ENCYC3104DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3104 - Algorithms"

mkdir "$ENCYC3104DIR"

cp main.pdf "$ENCYC3104DIR/CSPB 3104 - Algorithms Class Notes.pdf"

cp -r "Exam Notes" "$ENCYC3104DIR"

cp -r "Exams" "$ENCYC3104DIR"

cp -r "Lecture Notes" "$ENCYC3104DIR"

cp -r "Quizzes" "$ENCYC3104DIR"

cp -r "Textbook" "$ENCYC3104DIR"

cd ../../

ENCYC3104DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 3104 - Algorithms"

cp -r "Syllabus" "$ENCYC3104DIR"

cd ..

echo "CSPB 3104 Compiled Successfully"

# 3155 Compiling

cd "$CSPB3155NOTEDIR"

ENCYC3155DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3155 - Principles Of Programming Languages"

mkdir "$ENCYC3155DIR"

cp main.pdf "$ENCYC3155DIR/CSPB 3155 - Principles Of Programming Languages Class Notes.pdf"

cp -r "Exam Notes" "$ENCYC3155DIR"

cp -r "Exams" "$ENCYC3155DIR"

mkdir "../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3155 - Principles Of Programming Languages/Lecture Notes"

mkdir "../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3155 - Principles Of Programming Languages/Lecture Notes/Notes"

cp -r "Lecture Notes/Notes" "$ENCYC3155DIR/Lecture Notes"

cp -r "Quizzes" "$ENCYC3155DIR"

cp -r "Textbook" "$ENCYC3155DIR"

cd ../../

ENCYC3155DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 3155 - Principles Of Programming Languages"

cp -r "Syllabus" "$ENCYC3155DIR"

cd ..

echo "CSPB 3155 Compiled Successfully"

# 3202 Compiling

cd "$CSPB3202NOTEDIR"

ENCYC3202DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3202 - Introduction To Artificial Intelligence"

mkdir "$ENCYC3202DIR"

cp main.pdf "$ENCYC3202DIR/CSPB 3202 - Introduction To Artificial Intelligence Class Notes.pdf"

cp -r "Assignments" "$ENCYC3202DIR"

cp -r "Exam Notes" "$ENCYC3202DIR"

cp -r "Exams" "$ENCYC3202DIR"

mkdir "../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3202 - Introduction To Artificial Intelligence/Lecture Notes"

mkdir "../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3202 - Introduction To Artificial Intelligence/Lecture Notes/Notes"

cp -r "Lecture Notes/Notes" "$ENCYC3202DIR/Lecture Notes"

cp -r "Quizzes" "$ENCYC3202DIR"

cp -r "Textbook" "$ENCYC3202DIR"

cd ../../

ENCYC3202DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 3202 - Introduction To Artificial Intelligence"

cp -r "Syllabus" "$ENCYC3202DIR"

cd ..

echo "CSPB 3202 Compiled Successfully"

# CSPB 3308 Compiling

cd "$CSPB3308NOTEDIR"

ENCYC3308DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3308 - Software Development Methods And Tools"

mkdir "$ENCYC3308DIR"

cp main.pdf "$ENCYC3308DIR/CSPB 3308 - Software Development Methods And Tools Class Notes.pdf"

cp -r "Exam Notes" "$ENCYC3308DIR"

cp -r "Exams" "$ENCYC3308DIR"

cp -r "Lecture Notes" "$ENCYC3308DIR"

cp -r "Quizzes" "$ENCYC3308DIR"

cp -r "Textbook" "$ENCYC3308DIR"

cd ../../

ENCYC3308DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 3308 - Software Development Methods And Tools"

cp -r "Syllabus" "$ENCYC3308DIR"

cd ..

echo "CSPB 3308 Compiled Successfully"

# CSPB 3702 Compiling

cd "$CSPB3702NOTEDIR"

ENCYC3702DIR="../../../$CSPBENCYDIR/$ENCYCDIR/CSPB 3702 - Cognitive Science"

mkdir "$ENCYC3702DIR"

cp main.pdf "$ENCYC3702DIR/CSPB 3702 - Cognitive Science Class Notes.pdf"

cp -r "Assignments" "$ENCYC3702DIR"

cp -r "Lecture Notes" "$ENCYC3702DIR"

cp -r "Quizzes" "$ENCYC3702DIR"

cd ../../

ENCYC3702DIR="../$CSPBENCYDIR/$ENCYCDIR/CSPB 3702 - Cognitive Science"

cp -r "Syllabus" "$ENCYC3702DIR"

cp -r "Textbook" "$ENCYC3702DIR"

cd ..

echo "CSPB 3702 Compiled Successfully"

# Main Encyclopedia Compilation

cd "$CSPBENCYDIR/$ENCYCDIR"

mkdir "Courses"

mv "CSPB 2270 - Data Structures" "Courses"

mv "CSPB 2400 - Computer Systems" "Courses"

mv "CSPB 2820 - Linear Algebra With Computer Science Applications" "Courses"

mv "CSPB 2824 - Discrete Structures" "Courses"

mv "CSPB 3022 - Introduction To Data Science With Probability And Statistics" "Courses"

mv "CSPB 3104 - Algorithms" "Courses"

mv "CSPB 3155 - Principles Of Programming Languages" "Courses"

mv "CSPB 3202 - Introduction To Artificial Intelligence" "Courses"

mv "CSPB 3308 - Software Development Methods And Tools" "Courses"

mv "CSPB 3702 - Cognitive Science" "Courses"

cp -r "Courses" "../LaTeX"

cd "../LaTeX"

pdflatex "main.tex" && pdflatex "main.tex" && pdflatex "main.tex" 

cd ../../

cd "Scripts"

echo && ./LatexClean.sh

cd ..

echo && echo "Encyclopedia Compiled Successfully"