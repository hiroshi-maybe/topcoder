# [XMarksTheSpot](/tc?module=ProblemDetail&rd=16821&pm=14416)
*Single Round Match 700 Sponsored by Booz Allen Ham Round 1 - Division II, Level Two*

## Statement
You are playing a treasure hunt game.
The game is played on a rectangular board that is divided into a grid of unit squares.
You are given the layout of the board in the String[] *board*.
Each character in *board* represents one square of the board.
The meanings of the characters in *board*:

'O' (capital oh): This square contains a landmark.
'.': This square is empty.
'?': You do not know the contents of this square. It may contain a landmark and it may be empty.

A treasure is buried under one of the squares.
You know something about its location:

The row in which the treasure is buried is between T and B, inclusive, where T is the topmost row that contains a landmark and B is the bottommost row that contains a landmark.
The column in which the treasure is buried is between L and R, inclusive, where L is the leftmost column that contains a landmark and R is the rightmost column that contains a landmark.

Thus, you can narrow your search space to a sub-rectangle of the original grid.

Suppose k is the number of grid squares which are unknown to you.
In other words, let k be the number of '?' characters in *board*.
There are 2^k different boards that correspond to the information you have.
For each of those boards, compute the number of squares that may contain the treasure.
Find and return the sum of those 2^k numbers.

## Definitions
- *Class*: `XMarksTheSpot`
- *Method*: `countArea`
- *Parameters*: `String[]`
- *Returns*: `int`
- *Method signature*: `int countArea(String[] board)`

## Constraints
- *board* will have between 1 and 50 elements, inclusive.
- Each element of *board* will be the same length.
- Each element of *board* will have between 1 and 50 characters, inclusive.
- Each character of each element of *board* will be "O", ".", or "?".
- The number of "?" characters among all elements of *board* is at most 19.
- There will be at least one "O" character among all elements of *board*.

## Examples
### Example 1
#### Input
<c>[<br />"?.",<br />".O"<br />]</c>
#### Output
<c>5</c>
#### Reason
If the top left corner is empty, we only have 1 possible location of the treasure: the bottom right corner.
If the top left corner is a landmark, the treasure can be anywhere in the grid: 4 possible locations.
The return value is therefore 1 + 4 = 5.

### Example 2
#### Input
<c>[<br />"???",<br />"?O?",<br />"???"<br />]</c>
#### Output
<c>1952</c>
### Example 3
#### Input
<c>[<br />"...?.",<br />"?....",<br />".O...",<br />"..?..",<br />"....?"<br />]</c>
#### Output
<c>221</c>
### Example 4
#### Input
<c>["OOOOOOOOOOOOOOOOOOOOO"]</c>
#### Output
<c>21</c>
### Example 5
#### Input
<c>["?????????OO??????????"]</c>
#### Output
<c>9963008</c>
### Example 6
#### Input
<c>[<br />"OOO",<br />"O?O",<br />"OOO",<br />"..."<br />]</c>
#### Output
<c>18</c>

