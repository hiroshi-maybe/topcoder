# [Hexspeak](http://community.topcoder.com/tc?module=ProblemDetail&rd=16511&pm=13880)
*Single Round Match 662 Round 1 - Division II, Level One*

## Statement
If you compile a Java program and open the .class file in a text editor, you will find that the first four bytes spell "CAFEBABE" in hexadecimal.
Using hexadecimal numbers to spell words is called Hexspeak.

Hexadecimal numbers are integers written in base 16.
The letters 'A' through 'F' represent the digits with values 10 through 15.
For example, the integer 202 written in hexadecimal is "CA".
This is because 202 = 12*16 + 10, and the digits 12 and 10 are written as 'C' and 'A', respectively.

In this problem we will use eight different letters: in addition to the letters 'A' through 'F' we will also interpret the digit 0 as the letter 'O' and the digit 1 as the letter 'I'.
Hence, any word that only consists of the letters ABCDEFIO can be interpreted as a hexadecimal number.
Such words are called valid hexspeak words.

Fox Ciel has a long *ciphertext* containing a positive integer.
Convert this number to hexadecimal.
If you get the representation of a valid hexspeak word, return that word.
Otherwise, return the string "Error!" (quotes for clarity).
In other words, you should return "Error!" if the hexadecimal representation of *ciphertext* contains some occurrence of a digit between 2 and 9, inclusive.

## Definitions
- *Class*: `Hexspeak`
- *Method*: `decode`
- *Parameters*: `long`
- *Returns*: `String`
- *Method signature*: `String decode(long ciphertext)`

## Notes
- The correct hexadecimal representation of *ciphertext* does not contain any leading zeros.
- The return value is case-sensitive.

## Constraints
- *ciphertext* will be between 1 and 1,000,000,000,000,000,000, inclusive.

## Examples
### Example 1
#### Input
<c>257</c>
#### Output
<c>"IOI"</c>
#### Reason
The number 257 in decimal is written as 101 in hexadecimal.
The digits 1 and 0 represent the characters 'I' and 'O', thus we should return "IOI".

### Example 2
#### Input
<c>258</c>
#### Output
<c>"Error!"</c>
#### Reason
The number 258 in decimal is written as 102 in hexadecimal.
The digit 2 does not represent a letter, so we return "Error!".

### Example 3
#### Input
<c>3405691582</c>
#### Output
<c>"CAFEBABE"</c>
### Example 4
#### Input
<c>2882400001</c>
#### Output
<c>"ABCDEFOI"</c>
### Example 5
#### Input
<c>999994830345994239</c>
#### Output
<c>"DEOBIFFFFFFFFFF"</c>
### Example 6
#### Input
<c>1000000000000000000</c>
#### Output
<c>"Error!"</c>

