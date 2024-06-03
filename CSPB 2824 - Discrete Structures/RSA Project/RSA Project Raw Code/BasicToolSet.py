# Convert_Text - Converts a string to an array of integers that correspond to the ascii code for a given value
# Input:
#   _string - String that is to be converted to an array of ascii integers
# Algorithm:
#   * Create an empty array where the ascii digits are supposed to be appended to
#   * Iterate over the string and append the corresponding ascii value to integer_list
#       * Append the ascii code to integer_list
#   * Return the array
# Output:
#   integer_list - Array of integer values pertaining to the ascii of a letter or character
def Convert_Text(_string):
    integer_list = []
    for i in _string:
        integer_list.append(ord(i))
    return integer_list

# Convert_Num - Converts an array of numbers representing ascii numbers for a given character
# Input:
#   _list - Array of integers that represent ascii codes for a given character
# Algorithm:
#   * Create an empty string where characters are to be appended to the string
#   * Iterate over the array and append the characters to the string
#       * Append the character in _list to _string
#   * Return the string
# Output:
#   _string - String that represents the converted array to string
def Convert_Num(_list):
    _string = ''
    for i in _list:
        _string += chr(i)
    return _string

# Convert_Binary_String - Converts a decimal number to binary
# Input:
#   _int - Integer value that is to represent a number in decimal that is to be converted to binary
# Algorithm:
#   * Create an empty string that will represent the binary number
#   * While _int is greater than 0
#       * Calculate the binary digit by taking the modulo of _int and 2
#       * Update the string value with this digit
#       * Update _int by calculating the floor of _int divided by 2
#   * Reverse the order of the string
#   * Return the string
# Output:
#   _string - String value that is equal to the binary number of the original integer _int
def Convert_Binary_String(_int):
    _string = ''
    while(_int > 0):
        bindig = _int % 2
        _string += str(bindig)
        _int = _int // 2
    _string = _string[::-1]
    return _string