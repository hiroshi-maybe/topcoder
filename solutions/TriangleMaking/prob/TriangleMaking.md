# [TriangleMaking](/tc?module=ProblemDetail&rd=16776&pm=14371)
*Single Round Match 697 Round 1 - Division II, Level One*

## Statement
You have three sticks.
Their current lengths are *a*, *b*, and *c*.
You can shorten each of those sticks arbitrarily.
Your goal is to produce three sticks with the following properties:
The length of each stick is a positive integer.
The three sticks can be used to build a triangle. The triangle must be non-degenerate. (I.e., it must have a positive area.)
The perimeter of the triangle must be as large as possible.

You are given the ints *a*, *b*, and *c*.
Compute and return the largest possible perimeter of the triangle constructed from your three sticks.

## Definitions
- *Class*: `TriangleMaking`
- *Method*: `maxPerimeter`
- *Parameters*: `int, int, int`
- *Returns*: `int`
- *Method signature*: `int maxPerimeter(int a, int b, int c)`

## Notes
- The return value is always defined. In other words, for any *a*, *b*, and *c* there is at least one way to build a valid triangle.

## Constraints
- *a* will be between 1 and 100, inclusive.
- *b* will be between 1 and 100, inclusive.
- *c* will be between 1 and 100, inclusive.

## Examples
### Example 1
#### Input
<c>1,<br />2,<br />3</c>
#### Output
<c>5</c>
#### Reason
Shorten the last stick from 3 to 2. There is a triangle with sides (1,2,2). The perimeter of this triangle is 1+2+2 = 5.

### Example 2
#### Input
<c>2,<br />2,<br />2</c>
#### Output
<c>6</c>
#### Reason
Here the optimal solution is to use the three sticks you have without shortening any of them.

### Example 3
#### Input
<c>1,<br />100,<br />1</c>
#### Output
<c>3</c>
### Example 4
#### Input
<c>41,<br />64,<br />16</c>
#### Output
<c>113</c>

