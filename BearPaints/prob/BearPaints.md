# [BearPaints](http://community.topcoder.com/tc?module=ProblemDetail&rd=16551&pm=13488)
*Single Round Match 671 Round 1 - Division II, Level One*

## Statement
Limak is a little polar bear.
Today he found two things in the snow: a bucket of blue paint and a white rectangular grid with *W* times *H* square cells.

Limak is going to paint some (possibly even all) cells blue.
He wants to do it in such a way that the blue cells will form a completely filled blue rectangle.
He has enough paint for *M* cells.
What is the largest possible area of a blue rectangle he can paint?

## Definitions
- *Class*: `BearPaints`
- *Method*: `maxArea`
- *Parameters*: `int, int, long`
- *Returns*: `long`
- *Method signature*: `long maxArea(int W, int H, long M)`

## Constraints
- *W* and *H* will be between 1 and 10^6, inclusive.
- *M* will be between 1 and 10^12, inclusive.

## Examples
### Example 1
#### Input
<c>3,<br />5,<br />14</c>
#### Output
<c>12</c>
#### Reason
Limak has a grid that is *W* = 3 cells wide and *H* = 5 cells tall.
He doesn't have enough paint to color all 15 cells.
He also cannot color just 14 or 13 cells in a way that would produce a blue rectangle.
The best he can do is to color four consecutive rows blue.
This will produce a blue rectangle.
Its area is 12 squares.

### Example 2
#### Input
<c>4,<br />4,<br />10</c>
#### Output
<c>9</c>
#### Reason
Here the best solution is to paint a rectangle of size 3 times 3 blue.
(A square is a valid rectangle.)

### Example 3
#### Input
<c>1000000,<br />12345,<br />1000000000000</c>
#### Output
<c>12345000000</c>
#### Reason
Limak has more than enough paint to make whole grid blue.

### Example 4
#### Input
<c>1000000,<br />1000000,<br />720000000007</c>
#### Output
<c>720000000000</c>
#### Reason
Limak's grid is a square with side 10^6.
Limak can paint a rectangle of size 800,000 times 900,000.

### Example 5
#### Input
<c>1000000,<br />1000000,<br />999999999999</c>
#### Output
<c>999999000000</c>

