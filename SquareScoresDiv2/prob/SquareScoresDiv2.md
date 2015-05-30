# [SquareScoresDiv2](http://community.topcoder.com/tc?module=ProblemDetail&rd=16318&pm=13700)
*Single Round Match 654 Round 1 - Division II, Level One*

## Statement
A substring of a string is a contiguous sequence of characters from the string.
For example, each of the strings "ab", "bcd", and "e" is a substring of "abcde". 
On the other hand, "cba", "ace", and "f" are not substrings of "abcde".

The score of a string S is the number of ways in which we can select a non-empty substring of S such that all characters in the substring are the same.
If two substrings consist of the same letters but occur at different places in S, they are still considered different.
For example, the score of "aaaba" is 8: there are four occurrences of the substring "a", two occurrences of "aa", one occurrence of "aaa", and one of "b".

On her birthday, Maki got a String *s* from her friend Niko as a present.
Calculate and return its score.

## Definitions
- *Class*: `SquareScoresDiv2`
- *Method*: `getscore`
- *Parameters*: `String`
- *Returns*: `int`
- *Method signature*: `int getscore(String s)`

## Constraints
- The length of *s* will be between 1 and 100, inclusive.
- Each character in s will be a lowercase letter ('a'-'z').

## Examples
### Example 1
#### Input
<c>"aaaba"</c>
#### Output
<c>8</c>
#### Reason
The example explained above.

### Example 2
#### Input
<c>"zzzxxzz"</c>
#### Output
<c>12</c>
### Example 3
#### Input
<c>"abcdefghijklmnopqrstuvwxyz"</c>
#### Output
<c>26</c>
### Example 4
#### Input
<c>"p"</c>
#### Output
<c>1</c>
### Example 5
#### Input
<c>"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"</c>
#### Output
<c>5050</c>
#### Reason
All substrings satisfy the condition.


