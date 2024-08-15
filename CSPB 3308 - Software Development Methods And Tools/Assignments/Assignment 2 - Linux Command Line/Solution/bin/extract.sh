if [ -f $1 ]; then
    grep "clue_text" $1
    grep "clue_text" $1 | wc
    grep "clue_text" $1 | wc -l
    touch clues.txt
    grep "clue_text" $1 > clues.txt
    head -2 clues.txt
    touch categories.txt
    grep "category" $1 > categories.txt
    wc -l categories.txt
    touch "clues_J.txt"
    touch "clues_DJ.txt"
    touch "clues_FJ.txt"
    grep "clue_J" $1 > clues_J.txt
    grep "clue_DJ" $1 > clues_DJ.txt
    grep "clue_FJ" $1 > clues_FJ.txt
    wc -l *.txt
    sort clues_DJ.txt
    grep "clue_text" $1 | sort > clues.txt
    grep "clue_J" $1 | sort > clues_J.txt
    grep "clue_DJ" $1 | sort > clues_DJ.txt
else
    echo "Invalid or Missing filename"
    echo -n "Usage: "
    echo "$0 <filename>"
    echo ""
fi