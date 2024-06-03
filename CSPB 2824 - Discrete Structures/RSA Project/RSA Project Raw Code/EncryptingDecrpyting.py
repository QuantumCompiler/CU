import BasicToolSet as BTS
import FirstToolSet as FTS
import SecondToolSet as STS

# Encode - Encodes a string of text from a public key e and number n
# Input:
#   n - Integer value that is calculated with Find_Public_Key_e
#   e - Integer value that is calculated with Find_Public_Key_e
#   message - Message that is fed into the algorithm to by encoded
# Algorithm:
#   * Create an empty array called cipher_text
#   * Iterate over the characters in the message
#       * Calculate the integer value of char from Convert_Text
#       * Encode charNum with the use of FME and the value of e and n with charNum
#       * Append this value to cipher_text
#   * Return cipher_text
# Output:
#   This function returns an array of integers that represent encoded values from message
def Encode(n,e,message):
    cipher_text = []
    for char in message:
        charNum = BTS.Convert_Text(char)[0]
        encoded = FTS.FME(charNum,e,n)
        cipher_text.append(encoded)
    return cipher_text

# Decode - Decodes a message from an array of integers with private key d, n, and cipher_text
# Input:
#   n - Integer value that is calculated with Find_Public_Key_e
#   d - Integer value that is calculated with Find_Private_Key_d
#   cipher_text - Array of integers that represents an encoded message
# Algorithm:
#   * Create an empty container for the message that is to be returned
#   * Create an empty array to store the converted integers to strings in
#   * Iterate over the cipher_text array
#       * Calculate the ascii code for the given string with FME
#       * Append this ascii code to empty
#   * Decode the ascii values with Convert_Num and assign the result to message
#   * Return message
# Output:
#   This function returns the decoded message from cipher_text with private key d and n
def Decode(n,d,cipher_text):
    message = ''
    empty = []
    for num in cipher_text:
        numVal = FTS.FME(num,d,n)
        empty.append(numVal)
    message = BTS.Convert_Num(empty)
    return message