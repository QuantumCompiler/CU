grep "clue_text" *.html
grep "clue_text" *.html | wc
grep "clue_text" *.html | wc -l
touch clues.txt
grep "clue_text" *.html > clues.txt
head -2 clues.txt
touch categories.txt
grep "category" *.html > categories.txt
wc -l categories.txt
touch "clues_J.txt"
touch "clues_DJ.txt"
touch "clues_FJ.txt"
grep "clue_J" *.html > clues_J.txt
grep "clue_DJ" *.html > clues_DJ.txt
grep "clue_FJ" *.html > clues_FJ.txt
wc -l *.txt
sort clues_DJ.txt
grep "clue_text" *.html | sort > clues.txt
grep "clue_J" *.html | sort > clues_J.txt
grep "clue_DJ" *.html | sort > clues_DJ.txt