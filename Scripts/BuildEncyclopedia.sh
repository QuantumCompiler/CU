# Variables
CSPBENCYDIR="CSPB Encyclopedia"
SCRIPTSDIR="Scripts"
ENCYCDIR="Encyclopedia"
LATEXDIR="LaTeX"

cd ..
cd "$CSPBENCYDIR"

if [ -d "$ENCYCDIR" ]; then
    rm -rf $ENCYCDIR
    echo && echo "Successfully deleted previous Encyclopedia directory." && echo
    mkdir $ENCYCDIR
    echo "Created a new Encyclopedia directory." && echo
else
    mkdir $ENCYCDIR
    echo && echo "Created a new Encyclopedia directory." && echo
fi

if [ -d "$LATEXDIR" ]; then
    cd "$LATEXDIR"
    ##### MASTER COURSE DIR
    COURSEDIR="Courses"
    cd "$COURSEDIR"
    ##### COURSES DIR
    DATASTRUCTDIR="CSPB 2270 - Data Structures"
    COMPSYSDIR="CSPB 2400 - Computer Systems"
    LINALGDIR="CSPB 2820 - Linear Algebra With Computer Science Applications"
    DISCRETEDIR="CSPB 2824 - Discrete Structures"
    DATASCIDIR="CSPB 3022 - Introduction To Data Science With Probability And Statistics"
    ALGODIR="CSPB 3104 - Algorithms"
    PPLDIR="CSPB 3155 - Principles Of Programming Languages"
    AIDIR="CSPB 3202 - Introduction To Artifical Intelligence"
    SOFTDEVDIR="CSPB 3308 - Software Development Methods And Tools"
    COGSCIDIR="CSPB 3702 - Cognitive Science"
    ##### 2270
    cd "$DATASTRUCTDIR"
    FINALPDFNAME="CSPB 2270 - Data Structures Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$DATASTRUCTDIR" ]; then
        rm -rf "$DATASTRUCTDIR"
    fi
    mkdir "$DATASTRUCTDIR"
    EXAM_NOTES_DIR="Exam Notes"
    EXAMS_DIR="Exams"
    INT_NOTES_DIR="Interview Notes"
    LEC_NOTES_DIR="Lecture Notes"
    READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    cp -a "$EXAM_NOTES_DIR" "$DATASTRUCTDIR/"
    cp -a "$EXAMS_DIR" "$DATASTRUCTDIR/"
    cp -a "$INT_NOTES_DIR" "$DATASTRUCTDIR/"
    cp -a "$INT_NOTES_DIR" "$DATASTRUCTDIR/"
    cp -a "$LEC_NOTES_DIR" "$DATASTRUCTDIR/"
    cp -a "$READ_MAT_DIR" "$DATASTRUCTDIR/"
    cp -a "$SYL_DIR" "$DATASTRUCTDIR/"
    cp -a "$TEXT_DIR" "$DATASTRUCTDIR/"
    cp "$FINALPDFNAME" "$DATASTRUCTDIR/"
    chmod +rwx "$DATASTRUCTDIR"
    echo "Data Structures course notes compiled successfully." && echo && cd ..
    ##### 2400
    cd "$COMPSYSDIR"
    FINALPDFNAME="CSPB 2400 - Computer Systems Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$COMPSYSDIR" ]; then
        rm -rf "$COMPSYSDIR"
    fi
    mkdir "$COMPSYSDIR"
    EXAM_NOTES_DIR="Exam Notes"
    EXAMS_DIR="Exams"
    LEC_NOTES_DIR="Lecture Notes"
    QUIZ_DIR="Quizzes"
    READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    cp -a "$EXAM_NOTES_DIR" "$COMPSYSDIR/"
    cp -a "$EXAMS_DIR" "$COMPSYSDIR/"
    cp -a "$LEC_NOTES_DIR" "$COMPSYSDIR/"
    cp -a "$QUIZ_DIR" "$COMPSYSDIR/"
    cp -a "$READ_MAT_DIR" "$COMPSYSDIR/"
    cp -a "$SYL_DIR" "$COMPSYSDIR/"
    cp -a "$TEXT_DIR" "$COMPSYSDIR/"
    cp "$FINALPDFNAME" "$COMPSYSDIR/"
    chmod +rwx "$COMPSYSDIR"
    echo "Computer Systems course notes compiled successfully." && echo && cd ..
    ##### 2820
    cd "$LINALGDIR"
    FINALPDFNAME="CSPB 2820 - Linear Algebra With Computer Science Applications Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$LINALGDIR" ]; then
        rm -rf "$LINALGDIR"
    fi
    mkdir "$LINALGDIR"
    ASS_DIR="Assignments"
    EXAM_NOTES_DIR="Exam Notes"
    LEC_NOTES_DIR="Lecture Notes"
    QUIZ_DIR="Quizzes"
    READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    cp -a "$ASS_DIR" "$LINALGDIR/"
    cp -a "$EXAM_NOTES_DIR" "$LINALGDIR/"
    cp -a "$LEC_NOTES_DIR" "$LINALGDIR/"
    cp -a "$QUIZ_DIR" "$LINALGDIR/"
    cp -a "$READ_MAT_DIR" "$LINALGDIR/"
    cp -a "$SYL_DIR" "$LINALGDIR/"
    cp -a "$TEXT_DIR" "$LINALGDIR/"
    cp "$FINALPDFNAME" "$LINALGDIR/"
    chmod +rwx "$LINALGDIR"
    echo "Linear Algebra course notes compiled successfully." && echo && cd ..
    ##### 2824
    cd "$DISCRETEDIR"
    FINALPDFNAME="CSPB 2824 - Discrete Structures Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$DISCRETEDIR" ]; then
        rm -rf "$DISCRETEDIR"
    fi
    mkdir "$DISCRETEDIR"
    ASS_DIR="Assignments"
    EXAMS_DIR="Exams"
    LEC_NOTES_DIR="Lecture Notes"
    QUIZ_DIR="Quizzes"
    READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    cp -a "$ASS_DIR" "$DISCRETEDIR/"
    cp -a "$EXAMS_DIR" "$DISCRETEDIR/"
    cp -a "$LEC_NOTES_DIR" "$DISCRETEDIR/"
    cp -a "$QUIZ_DIR" "$DISCRETEDIR/"
    cp -a "$READ_MAT_DIR" "$DISCRETEDIR/"
    cp -a "$SYL_DIR" "$DISCRETEDIR/"
    cp -a "$TEXT_DIR" "$DISCRETEDIR/"
    cp "$FINALPDFNAME" "$DISCRETEDIR/"
    chmod +rwx "$DISCRETEDIR"
    echo "Discrete Structures course notes compiled successfully." && echo && cd ..
    ##### 3022
    cd "$DATASCIDIR"
    FINALPDFNAME="CSPB 3022 - Introduction To Data Science With Probability And Statistics Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$DATASCIDIR" ]; then
        rm -rf "$DATASCIDIR"
    fi
    mkdir "$DATASCIDIR"
    EXAM_NOTES_DIR="Exam notes"
    EXAMS_DIR="Exams"
    LEC_NOTES_DIR="Lecture Notes"
    QUIZ_DIR="Quizzes"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    cp -a "$EXAM_NOTES_DIR" "$DATASCIDIR/"
    cp -a "$EXAMS_DIR" "$DATASCIDIR/"
    cp -a "$LEC_NOTES_DIR" "$DATASCIDIR/"
    cp -a "$QUIZ_DIR" "$DATASCIDIR/"
    cp -a "$SYL_DIR" "$DATASCIDIR/"
    cp -a "$TEXT_DIR" "$DATASCIDIR/"
    cp "$FINALPDFNAME" "$DATASCIDIR/"
    chmod +rwx "$DATASCIDIR"
    echo "Data Science course notes compiled successfully." && echo && cd ..
    ##### 3104
    cd "$ALGODIR"
    FINALPDFNAME="CSPB 3104 - Algorithms Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$ALGODIR" ]; then
        rm -rf "$ALGODIR"
    fi
    mkdir "$ALGODIR"
    EXAM_NOTES_DIR="Exam notes"
    EXAMS_DIR="Exams"
    QUIZ_DIR="Quizzes"
    READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    cp -a "$EXAM_NOTES_DIR" "$ALGODIR/"
    cp -a "$EXAMS_DIR" "$ALGODIR/"
    cp -a "$QUIZ_DIR" "$ALGODIR/"
    cp -a "$READ_MAT_DIR" "$ALGODIR/"
    cp -a "$SYL_DIR" "$ALGODIR/"
    cp -a "$TEXT_DIR" "$ALGODIR/"
    cp "$FINALPDFNAME" "$ALGODIR/"
    chmod +rwx "$ALGODIR"
    echo "Algorithms course notes compiled successfully." && echo && cd ..
    ##### 3155
    cd "$PPLDIR"
    FINALPDFNAME="CSPB 3155 - Principles Of Programming Languages Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    # pdflatex *.tex > /dev/null 2>&1
    # pdflatex *.tex > /dev/null 2>&1
    # pdflatex *.tex > /dev/null 2>&1
    # cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$PPLDIR" ]; then
        rm -rf "$PPLDIR"
    fi
    mkdir "$PPLDIR"
    # EXAM_NOTES_DIR="Exam notes"
    # EXAMS_DIR="Exams"
    # QUIZ_DIR="Quizzes"
    # READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    # cp -a "$EXAM_NOTES_DIR" "$PPLDIR/"
    # cp -a "$EXAMS_DIR" "$PPLDIR/"
    # cp -a "$QUIZ_DIR" "$PPLDIR/"
    # cp -a "$READ_MAT_DIR" "$PPLDIR/"
    cp -a "$SYL_DIR" "$PPLDIR/"
    cp -a "$TEXT_DIR" "$PPLDIR/"
    # cp "$FINALPDFNAME" "$PPLDIR/"
    chmod +rwx "$PPLDIR"
    echo "PPL course notes compiled successfully." && echo && cd ..
    ##### 3202
    cd "$AIDIR"
    FINALPDFNAME="CSPB 3202 - Introduction To Artifical Intelligence Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    # pdflatex *.tex > /dev/null 2>&1
    # pdflatex *.tex > /dev/null 2>&1
    # pdflatex *.tex > /dev/null 2>&1
    # cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$AIDIR" ]; then
        rm -rf "$AIDIR"
    fi
    mkdir "$AIDIR"
    # EXAM_NOTES_DIR="Exam notes"
    # EXAMS_DIR="Exams"
    # QUIZ_DIR="Quizzes"
    # READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    # cp -a "$EXAM_NOTES_DIR" "$AIDIR/"
    # cp -a "$EXAMS_DIR" "$AIDIR/"
    # cp -a "$QUIZ_DIR" "$AIDIR/"
    # cp -a "$READ_MAT_DIR" "$AIDIR/"
    cp -a "$SYL_DIR" "$AIDIR/"
    cp -a "$TEXT_DIR" "$AIDIR/"
    # cp "$FINALPDFNAME" "$AIDIR/"
    chmod +rwx "$AIDIR"
    echo "Artifical Intelligence course notes compiled successfully." && echo && cd ..
    ##### 3308
    cd "$SOFTDEVDIR"
    FINALPDFNAME="CSPB 3308 - Software Development Methods And Tools Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    # pdflatex *.tex > /dev/null 2>&1
    # pdflatex *.tex > /dev/null 2>&1
    # pdflatex *.tex > /dev/null 2>&1
    # cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$SOFTDEVDIR" ]; then
        rm -rf "$SOFTDEVDIR"
    fi
    mkdir "$SOFTDEVDIR"
    # EXAM_NOTES_DIR="Exam notes"
    # EXAMS_DIR="Exams"
    # QUIZ_DIR="Quizzes"
    # READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    TEXT_DIR="Textbook"
    # cp -a "$EXAM_NOTES_DIR" "$SOFTDEVDIR/"
    # cp -a "$EXAMS_DIR" "$SOFTDEVDIR/"
    # cp -a "$QUIZ_DIR" "$SOFTDEVDIR/"
    # cp -a "$READ_MAT_DIR" "$SOFTDEVDIR/"
    cp -a "$SYL_DIR" "$SOFTDEVDIR/"
    cp -a "$TEXT_DIR" "$SOFTDEVDIR/"
    # cp "$FINALPDFNAME" "$SOFTDEVDIR/"
    chmod +rwx "$SOFTDEVDIR"
    echo "Software Development course notes compiled successfully." && echo && cd ..
    ##### 3702
    cd "$COGSCIDIR"
    FINALPDFNAME="CSPB 3702 - Cognitive Science Course Notes.pdf"
    if [ -f "$FINALPDFNAME" ]; then
        rm "$FINALPDFNAME"
    fi
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    cp "main.pdf" "$FINALPDFNAME" && rm -rf "main.pdf"
    if [ -d "$COGSCIDIR" ]; then
        rm -rf "$COGSCIDIR"
    fi
    mkdir "$COGSCIDIR"
    ASS_DIR="Assignments"
    LEC_NOTES_DIR="Lecture Notes"
    QUIZ_DIR="Quizzes"
    READ_MAT_DIR="Reading Material"
    SYL_DIR="Syllabus"
    cp -a "$ASS_DIR" "$COGSCIDIR/"
    cp -a "$LEC_NOTES_DIR" "$COGSCIDIR/"
    cp -a "$QUIZ_DIR" "$COGSCIDIR/"
    cp -a "$READ_MAT_DIR" "$COGSCIDIR/"
    cp -a "$SYL_DIR" "$COGSCIDIR/"
    cp "$FINALPDFNAME" "$COGSCIDIR/"
    chmod +rwx "$COGSCIDIR"
    echo "Cognitive Science course notes compiled successfully." && echo && cd ..
    ###### Encyclopedia
    cd ..
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    pdflatex *.tex > /dev/null 2>&1
    echo "Compiled Encyclopedia successfully." && echo
    FINALPDFNAME="CSPB Encyclopedia.pdf"
    mkdir "../$ENCYCDIR/$COURSEDIR"
    mv "$COURSEDIR/$DATASTRUCTDIR/$DATASTRUCTDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$COMPSYSDIR/$COMPSYSDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$LINALGDIR/$LINALGDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$DISCRETEDIR/$DISCRETEDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$DATASCIDIR/$DATASCIDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$ALGODIR/$ALGODIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$PPLDIR/$PPLDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$AIDIR/$AIDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$SOFTDEVDIR/$SOFTDEVDIR" "../$ENCYCDIR/$COURSEDIR/"
    mv "$COURSEDIR/$COGSCIDIR/$COGSCIDIR" "../$ENCYCDIR/$COURSEDIR/"
    cp "main.pdf" "../$ENCYCDIR/$FINALPDFNAME"
    cd ../../$SCRIPTSDIR && ./LatexClean.sh
else
    echo "Error, $LATEXDIR not found."
fi