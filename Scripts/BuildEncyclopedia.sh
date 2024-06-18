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