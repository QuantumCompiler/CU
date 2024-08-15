#/bin/sh

# You must edit and remane this file file for your use
# It is included to make sure your text is correct for 
# grading your output
#
# Usage to run the script:
#  <script_name> <filename>

# How many lines in the data file?
echo ""
count_lines=$(wc -l $1)
echo -n "How many lines in the data file?    $count_lines"

# How many lines start with Capital Letter?
echo ""
count_lines_cap=$(grep -e "^[A-Z]" $1| wc -l)
echo -n "How many lines start with Capital Letter?    $count_lines_cap"

###
### Insert your solution to each problem
###

# How many lines end with a number?
echo ""
count_num=$(grep -E '.*[0-9]$' "$1" | wc -l)
echo -n "How many lines end with a Number?    $count_num"

# How many lines do not start with a vowel?
echo ""
count_not_vow=$(grep -E '^[^aeiouAEIOU]' "$1" | wc -l)
echo -n "How many lines do not start with a vowel?   $count_not_vow"

# How many 12 letter (alphabet only) lines?
echo ""
count_let=$(grep -E '^[a-zA-Z]{12}$' "$1" | wc -l)
echo -n "How many 12 letter (alphabet only) lines?    $count_let"

# How many phone numbers are in the dataset (format: _ _ _-_ _ _-_ _ _ _)?
echo ""
count_phone_num=$(grep -E '^[0-9]{3}-[0-9]{3}-[0-9]{4}$' "$1" | wc -l)
count_phone_num_alt=$(grep -E '^\([0-9]{3}\)[0-9]{3}-[0-9]{4}$|^[0-9]{3}-[0-9]{3}-[0-9]{4}$' "$1" | wc -l)
count_phone_num_alt_alt=$(grep -E '^[0-9]{3}-[0-9]{4}$|^\([0-9]{3}\)[0-9]{3}-[0-9]{4}$|^[0-9]{3}-[0-9]{3}-[0-9]{4}$' "$1" | wc -l)
echo -n "How many phone numbers are in the dataset (format: _ _ _-_ _ _-_ _ _ _)?    $count_phone_num"
echo -n "   when allowing for '(xxx)xxx-xxxx'    :  $count_phone_num_alt"
echo -n "   when only checking for 'xxx-xxxx'    :  $count_phone_num_alt_alt"

# How many phone numbers have area code the same as University of Colorado Boulder, "303"?
echo ""
count_303_num=$(grep -E '^303-[0-9]{3}-[0-9]{4}$|^\(303\)[0-9]{3}-[0-9]{4}$' "$1" | wc -l)
count_303_num_alt=$(grep -E '^303-[0-9]{3}-[0-9]{4}$' "$1" | wc -l)
echo -n "How many 303 phone numbers?   $count_303_num"
echo -n "   when only allowing for '303-xxx-xxxx'    :   $count_303_num_alt"

# How many begin with a vowel and end with a number?
echo ""
count_vow_num=$(grep -E '^[aeiouAEIOU].*[0-9]$' "$1" | wc -l)
echo -n "How many begin with a vowel and end with a number?    $count_vow_num"

# How many email addresses are from geocities? (Eg: end with'geocities.com')?
echo ""
count_email=$(grep -E 'geocities\.com$' "$1" | wc -l)
echo -n "How many email addresses are from geocities? (Eg: end with\'geocities.com\')?    $count_email"

# How many email addresses are in ‘first.last’ name format and involve someone who’s 
# first name starts with a letter in the first half of the alphabet?
echo ""
count_email_names=$(grep -E '^[A-Ma-m][A-Za-z]+\.[A-Za-z]+@.*' "$1" | wc -l)
echo "How many email addresses are in ‘first.last’ name format and involve someone "
echo -n "who’s first name starts with a letter in the first half of the alphabet?      $count_email_names"

echo ""

# Running regexAnswers.sh script file should output 10 lines which is the result of wc –l for each regex command. 
# If unsure of any one of the answers, use echo "0" so that the rest of your answers align in the output.

