# Variables
CSPBENCYDIR="CSPB Encyclopedia"
SCRIPTSDIR="Scripts"
ENCYCDIR="Encyclopedia"
LATEXDIR="LaTeX"

cd ..
cd "$CSPBENCYDIR"

if [ -d "$ENCYCDIR" ]; then
    rm -rf $ENCYCDIR
    echo && echo "Successfully deleted previous Encyclopedia directory."
    mkdir $ENCYCDIR
    echo "Created a new Encyclopedia directory." && echo
else
    mkdir $ENCYCDIR
    echo && echo "Created a new Encyclopedia directory." && echo
fi

if [ -d "$LATEXDIR" ]; then
    cd $LATEXDIR
    pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1 && pdflatex *.tex > /dev/null 2>&1
    echo "Compiled main TeX file successfully." && echo && cd ..
    COURSEDIR="Courses"
    MAINPDF="main.pdf"
    FINALPDF="CSPB Encyclopedia.pdf"
    cp -r "$LATEXDIR/$COURSEDIR" "$ENCYCDIR/$COURSEDIR"
    echo "Copied Courses directory successfully."
    cp "$LATEXDIR/$MAINPDF" "$ENCYCDIR/$FINALPDF"
    echo "Copied $MAINPDF and renamed it to $FINALPDF successfully." && cd .. && cd "$SCRIPTSDIR"
    ./LatexClean.sh
else
    echo "Error, $LATEXDIR not found."
fi