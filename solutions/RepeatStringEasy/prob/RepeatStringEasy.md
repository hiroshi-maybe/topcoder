# [RepeatStringEasy](/tc?module=ProblemDetail&rd=16802&pm=14390)
*Single Round Match 698 Sponsored by Google Round 1 - Division II, Level Two*

## Statement
A string S is called a square if there is some string T such that S = T + T.
For example, the strings "", aabaab" and "xxxx" are squares, but "a", "aabb" and "aabbaa" are not.

You are given a String *s*.
Find the longest square string that can be obtained from *s* by erasing some (possibly none, possibly all) of its characters.
In other words, we are looking for the longest square that occurs in *s* as a subsequence.
Return the length of that square.

Note that the answer is well-defined, as the square "" (the empty string) will always occur in *s* as a subsequence.

## Definitions
- *Class*: `RepeatStringEasy`
- *Method*: `maximalLength`
- *Parameters*: `String`
- *Returns*: `int`
- *Method signature*: `int maximalLength(String s)`

## Constraints
- *s* will contain between 1 and 50 characters, inclusive.
- Each character in *s* will be a lowercase English letter ('a'-'z').

## Examples
### Example 1
#### Input
<c>"frankfurt"</c>
#### Output
<c>4</c>
#### Reason
The longest square that occurs in "frankfurt" is "frfr". Its length is 4.

### Example 2
#### Input
<c>"single"</c>
#### Output
<c>0</c>
#### Reason
The letters in the string "single" are all distinct. Hence, the only square that occurs in this string is "". The length of this square is zero.

### Example 3
#### Input
<c>"singing"</c>
#### Output
<c>6</c>
### Example 4
#### Input
<c>"aababbababbabbbbabbabb"</c>
#### Output
<c>18</c>
### Example 5
#### Input
<c>"x"</c>
#### Output
<c>0</c>

