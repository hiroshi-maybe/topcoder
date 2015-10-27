# [Drbalance](http://community.topcoder.com/tc?module=ProblemDetail&rd=16550&pm=14060)
*Single Round Match 670 Round 1 - Division II, Level Two*

## Statement
A plus/minus string is a string in which each character is either a '+' or a '-'.

The balance of a plus/minus string is computed as the number of '+' characters minus the number of '-' characters.

For example, the balance of the string "++-+" is 3-1 = 2, and the balance of the string "---" is 0-3 = -3.

The prefix of a string S is any string that can be obtained by removing some (possibly none, possibly all) characters from the end of S.
For example, the prefixes of the string "++-+" are the strings "++-+", "++-", "++", "+", and "".

Given a plus/minus string, its negativity is the number of its prefixes that have a negative balance.
For example, the negativity of the string "++-+" is 0, as none of its prefixes have a negative balance.
The negativity of the string "---" is 3.
Its three prefixes with a negative balance are "-", "--", and "---".

You are given a String *s* that is a plus/minus string.
You are also given an int *k*.
Your goal is to change *s* into a string with negativity at most *k*.
In other words, you want to change *s* into a string that has at most *k* prefixes that have a negative balance.

In order to change *s* you are going to perform a sequence of zero or more steps.
In each step you can change a single '-' character in *s* into a '+' or vice versa.
Compute and return the smallest number of steps needed.

## Definitions
- *Class*: `Drbalance`
- *Method*: `lesscng`
- *Parameters*: `String, int`
- *Returns*: `int`
- *Method signature*: `int lesscng(String s, int k)`

## Constraints
- *s* will contain between 1 and 50 characters, inclusive.
- *k* will be between 0 and the length of *s*, inclusive.
- Each character in *s* will be either '+' or '-'.

## Examples
### Example 1
#### Input
<c>"---",<br />1</c>
#### Output
<c>1</c>
#### Reason
One step is sufficient.
If we change character 0 of *s* into a '+', we will obtain the string "+--".
This string has only one prefix with a negative balance - namely, the entire string "+--".
As *k*=1, we have reached our goal.

### Example 2
#### Input
<c>"+-+-",<br />0</c>
#### Output
<c>0</c>
### Example 3
#### Input
<c>"-+-+---",<br />2</c>
#### Output
<c>1</c>
### Example 4
#### Input
<c>"-------++",<br />3</c>
#### Output
<c>3</c>
### Example 5
#### Input
<c>"-+--+--+--++++----+",<br />3</c>
#### Output
<c>2</c>

