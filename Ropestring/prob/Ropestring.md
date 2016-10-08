# [Ropestring](/tc?module=ProblemDetail&rd=16775&pm=14373)
*Single Round Match 696 Round 1 - Division II, Level One*

## Statement
Hero has a collection of ropes.
You are given the String *s* that contains an ASCII art depicting this collection of ropes.
Each character of *s* is either '-' (dash, ASCII 45) or '.' (period, ASCII 46).
Each dash is a rope segment, each period is an empty space.
Each contiguous segment of dashes represents one rope; the number of dashes is the length of the rope.
For example, *s* = "..-..----." means that Hero has two ropes: one of length 1 and one of length 4.

Hero has decided to rearrange his collection of ropes, using the following rules:
Each rope that has an even length must be placed to the left of all ropes that have odd lengths.
There must be at least one empty space between any two ropes.
If there are multiple arrangements that satisfy the previous two rules, Hero will choose the one that corresponds to the lexicographically smallest string. (This is explained below.)

Once Hero rearranges his ropes, we can encode their new placement into a new string that looks similar to *s*.
(The string will have the same length as *s* and it will contain the same collection of ropes, but possibly in different places.)

Given two strings of the same length, the lexicographically smaller one is the one that has a character with a smaller ASCII value on the first position on which they differ.
For example, the string X = "---.-" is lexicographically smaller than the string Y = "-.---" because X[0] = Y[0] and X[1] &lt Y[1].
(Note that a dash has a smaller ASCII value than a period.)

Construct the arrangement of ropes chosen by Hero and return the String that encodes it.

## Definitions
- *Class*: `Ropestring`
- *Method*: `makerope`
- *Parameters*: `String`
- *Returns*: `String`
- *Method signature*: `String makerope(String s)`

## Constraints
- *s* will contain between 1 and 50 characters, inclusive.
- Each character in *s* will be either '-' or '.'.

## Examples
### Example 1
#### Input
<c>"..-..-"</c>
#### Output
<c>"-.-..."</c>
### Example 2
#### Input
<c>"-.-"</c>
#### Output
<c>"-.-"</c>
### Example 3
#### Input
<c>"--..-.---..--"</c>
#### Output
<c>"--.--.---.-.."</c>
### Example 4
#### Input
<c>"--..-.---..--..-----.--."</c>
#### Output
<c>"--.--.--.-----.---.-...."</c>
### Example 5
#### Input
<c>"..."</c>
#### Output
<c>"..."</c>

