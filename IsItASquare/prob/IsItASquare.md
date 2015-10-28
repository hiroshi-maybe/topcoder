# [IsItASquare](http://community.topcoder.com/tc?module=ProblemDetail&rd=16548&pm=14004)
*Single Round Match 668 Round 1 - Division II, Level Two*

## Statement
It's a bird! It's a plane! No, it's a square in a plane! Wait, is it really a square?

There are four distinct points in the plane.
You are given their coordinates in the int[]s *x* and *y*:
for each i between 0 and 3, inclusive, there is a point at (*x*[i], *y*[i]).

Return "It's a square" (quotes for clarity) if the four points are the vertices of a square.
Otherwise, return "Not a square".

## Definitions
- *Class*: `IsItASquare`
- *Method*: `isSquare`
- *Parameters*: `int[], int[]`
- *Returns*: `String`
- *Method signature*: `String isSquare(int[] x, int[] y)`

## Constraints
- *x* will contain 4 elements.
- *y* will contain 4 elements.
- Each element of *x* will be between 0 and 10,000, inclusive.
- Each element of *y* will be between 0 and 10,000, inclusive.
- The four points described by *x* and *y* will be distinct.

## Examples
### Example 1
#### Input
<c>[0, 0, 2, 2],<br />[0, 2, 0, 2]</c>
#### Output
<c>"It's a square"</c>
### Example 2
#### Input
<c>[0, 1, 5, 6],<br />[1, 6, 0, 5]</c>
#### Output
<c>"It's a square"</c>
#### Reason
Note that the sides of the square do not have to be parallel to the coordinate axes.
Also note that the order in which the points are given does not have to be the same as the order in which you would encounter them when following the boundary of the square.

### Example 3
#### Input
<c>[0, 0, 7, 7],<br />[0, 3, 0, 3]</c>
#### Output
<c>"Not a square"</c>
### Example 4
#### Input
<c>[0, 5000, 5000, 10000],<br />[5000, 0, 10000, 5000]</c>
#### Output
<c>"It's a square"</c>
### Example 5
#### Input
<c>[1, 2, 3, 4],<br />[4, 3, 2, 1]</c>
#### Output
<c>"Not a square"</c>
### Example 6
#### Input
<c>[0, 5, 3, 8],<br />[0, 0, 4, 4]</c>
#### Output
<c>"Not a square"</c>

