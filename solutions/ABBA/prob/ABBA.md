# [ABBA](http://community.topcoder.com/tc?module=ProblemDetail&rd=16512&pm=13918)
*Single Round Match 663 Round 1 - Division II, Level Two*

## Statement
One day, Jamie noticed that many English words only use the letters A and B.
Examples of such words include "AB" (short for abdominal), "BAA" (the noise a sheep makes), "AA" (a type of lava), and "ABBA" (a Swedish pop sensation).

Inspired by this observation, Jamie created a simple game.
You are given two Strings: *initial* and *target*.
The goal of the game is to find a sequence of valid moves that will change *initial* into *target*.
There are two types of valid moves:

Add the letter A to the end of the string.
Reverse the string and then add the letter B to the end of the string.

Return "Possible" (quotes for clarity) if there is a sequence of valid moves that will change *initial* into *target*.
Otherwise, return "Impossible".

## Definitions
- *Class*: `ABBA`
- *Method*: `canObtain`
- *Parameters*: `String, String`
- *Returns*: `String`
- *Method signature*: `String canObtain(String initial, String target)`

## Constraints
- The length of *initial* will be between 1 and 999, inclusive.
- The length of *target* will be between 2 and 1000, inclusive.
- *target* will be longer than *initial*.
- Each character in *initial* and each character in *target* will be either 'A' or 'B'.

## Examples
### Example 1
#### Input
<c>"B",<br />"ABBA"</c>
#### Output
<c>"Possible"</c>
#### Reason
Jamie can perform the following moves:
Initially, the string is "B".
Jamie adds an 'A' to the end of the string. Now the string is "BA".
Jamie reverses the string and then adds a 'B' to the end of the string. Now the string is "ABB".
Jamie adds an 'A' to the end of the string. Now the string is "ABBA".
Since there is a sequence of moves which starts with "B" and creates the string "ABBA", the answer is "Possible".

### Example 2
#### Input
<c>"AB",<br />"ABB"</c>
#### Output
<c>"Impossible"</c>
#### Reason
The only strings of length 3 Jamie can create are "ABA" and "BAB".

### Example 3
#### Input
<c>"BBAB",<br />"ABABABABB"</c>
#### Output
<c>"Impossible"</c>
### Example 4
#### Input
<c>"BBBBABABBBBBBA",<br />"BBBBABABBABBBBBBABABBBBBBBBABAABBBAA"</c>
#### Output
<c>"Possible"</c>
### Example 5
#### Input
<c>"A",<br />"BB"</c>
#### Output
<c>"Impossible"</c>

