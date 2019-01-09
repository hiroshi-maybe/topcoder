# [TaroFillingAStringDiv1](http://community.topcoder.com/tc?module=ProblemDetail&rd=16314&pm=13669)
*Single Round Match 650 Round 1 - Division I, Level One*

## Statement
Cat Taro likes strings.
He is currently constructing a string S of length *N*.
Each character of S will be either 'A' or 'B'.
Taro has already chosen some of the characters.
You are given these choices as a int[] *position* and a String *value*.
For each valid i, the character at the 1-based index *position*[i] in S is the character *value*[i].

To Taro, the ugliness of a string is the number of pairs of equal consecutive characters.
For example, the ugliness of "ABABAABBB" is 3: there is one pair "AA" and two (overlapping) pairs "BB".

Taro now wants to finish S by filling in the remaining characters.
His goal is to create a string with the smallest possible ugliness.
Let X be the number of possible strings Taro may produce.
Return the value (X modulo 1,000,000,007).

## Definitions
- *Class*: `TaroFillingAStringDiv1`
- *Method*: `getNumber`
- *Parameters*: `int, int[], String`
- *Returns*: `int`
- *Method signature*: `int getNumber(int N, int[] position, String value)`

## Constraints
- *N* will be between 1 and 1,000,000,000, inclusive.
- *position* will contian between 1 and 50 elements, inclusive.
- *value* and *position* will contain the same number of elements.
- Each element of *position* will be between 1 and *N*, inclusive.
- All elements of *position* will be distinct.
- *value* will consist only of characters 'A' and 'B'.

## Examples
### Example 1
#### Input
<c>3,<br />[1, 3],<br />"AB"</c>
#### Output
<c>2</c>
#### Reason
Currently, Taro's string looks as follows: A_B.
He can either produce the string AAB or the string ABB.
Both have the same ugliness.

### Example 2
#### Input
<c>4,<br />[2, 1, 3, 4],<br />"ABBA"</c>
#### Output
<c>1</c>
#### Reason
All characters of S have already been chosen.

### Example 3
#### Input
<c>25,<br />[23, 4, 8, 1, 24, 9, 16, 17, 6, 2, 25, 15, 14, 7, 13],<br />"ABBBBABABBAAABA"</c>
#### Output
<c>1</c>
### Example 4
#### Input
<c>305,<br />[183, 115, 250, 1, 188, 193, 163, 221, 144, 191, 92, 192, 58, 215, 157, 187, 227, 177, 206, 15, 272, 232, 49, 11, 178, 59, 189, 246],<br />"ABAABBABBAABABBBBAAAABBABBBA"</c>
#### Output
<c>43068480</c>

