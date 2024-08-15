#/bin/sh

# You must edit and remane this file file for your use
# It is included to make sure your text is correct for 
# grading your output
#
# Usage to run the script:
#  <script_name> <filename>

# How many lines in the data file?
echo ""
echo -n "How many lines in the data file?    "
wc -l $1

# How many lines start with Capital Letter?
echo ""
echo -n "How many lines start with Capital Letter?    "
grep -e "^[A-Z]" $1| wc -l

###
### Insert your solution to each problem
###

# How many lines end with a number?
echo ""
echo -n "How many lines end with a Number?    "
echo 0
## grep ...

# How many lines do not start with a vowel?
echo ""
echo -n "How many lines do not start with a vowel?   "
echo 0
## grep ...

# How many 12 letter (alphabet only) lines?
echo ""
echo -n "How many 12 letter (alphabet only) lines?    "
echo 0
## grep ...

# How many phone numbers are in the dataset (format: _ _ _-_ _ _-_ _ _ _)?
echo ""
echo -n "How many phone numbers are in the dataset (format: _ _ _-_ _ _-_ _ _ _)?    "
echo 0
## grep ...

# How many phone numbers have area code the same as University of Colorado Boulder, "303"?
echo ""
echo -n "How many 303 phone numbers?   "
echo 0
## grep ...

# How many begin with a vowel and end with a number?
echo ""
echo -n "How many begin with a vowel and end with a number?    "
echo 0
## grep ...

# How many email addresses are from geocities? (Eg: end with'geocities.com')?
echo ""
echo -n "How many email addresses are from geocities? (Eg: end with\'geocities.com\')?    "
echo 0
## grep ...

# How many email addresses are in ‘first.last’ name format and involve someone who’s 
# first name starts with a letter in the first half of the alphabet?
echo ""
echo "How many email addresses are in ‘first.last’ name format and involve someone "
echo -n "who’s first name starts with a letter in the first half of the alphabet?      "
echo 0
## grep ...

echo ""

# Running regexAnswers.sh script file should output 10 lines which is the result of wc –l for each regex command. 
# If unsure of any one of the answers, use echo "0" so that the rest of your answers align in the output.

