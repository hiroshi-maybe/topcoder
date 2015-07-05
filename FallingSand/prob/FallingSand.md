# [FallingSand](http://community.topcoder.com/tc?module=ProblemDetail&rd=16464&pm=13768)
*Single Round Match 661 Round 1 - Division II, Level One*

## Statement
You have a rectangular board that is placed vertically.
The board is divided into a grid of unit square cells.
Some grid cells contain obstacles and some cells contain a grain of sand.
All other cells are currently empty.

You are given the description of the board as a String[] board.
The elements of *board* correspond to rows of the grid in the order from top to bottom.
(E.g., *board*[0] represents the topmost row of cells.)
Each character in each element of *board* represents one cell.
The character 'x' represents a cell with an obstacle, 'o' is a grain of sand, and '.' (period) is an empty cell.

You would like to implement a simulation of falling sand.
The rules are as follows:

The obstacles don't move.
Whenever there is an empty cell immediately below a grain of sand, the grain of sand moves into the empty cell.

Return the final configuration of the board after all grains of sand reach their final locations.

## Definitions
- *Class*: `FallingSand`
- *Method*: `simulate`
- *Parameters*: `String[]`
- *Returns*: `String[]`
- *Method signature*: `String[] simulate(String[] board)`

## Constraints
- *board* will contain between 1 and 50 elements, inclusive.
- Each element of *board* will have length between 1 and 50, inclusive.
- All elements of *board* will have the same length.
- Each character in each element of *board* will be one of 'x', 'o', and '.'.

## Examples
### Example 1
#### Input
<c>["ooooo",<br /> "..x..",<br /> "....x",<br /> ".....",<br /> "....o"]</c>
#### Output
<c>["..o..", "..x.o", "....x", ".....", "oo.oo" ]</c>
#### Reason
The return value is:

{"..o..", 
 "..x.o", 
 "....x", 
 ".....", 
 "oo.oo" }

### Example 2
#### Input
<c>["..o..", <br /> "..x.o", <br /> "....x", <br /> ".....", <br /> "oo.oo" ]</c>
#### Output
<c>["..o..", "..x.o", "....x", ".....", "oo.oo" ]</c>
### Example 3
#### Input
<c>["ooooxooo.ooxo.oxoxoooox.....x.oo"]</c>
#### Output
<c>["ooooxooo.ooxo.oxoxoooox.....x.oo" ]</c>
#### Reason
Nothing changes in this case, since all the sand is already at the bottom of the grid.

### Example 4
#### Input
<c>["o",<br /> ".",<br /> "o",<br /> ".",<br /> "o",<br /> ".",<br /> "."]</c>
#### Output
<c>[".", ".", ".", ".", "o", "o", "o" ]</c>
### Example 5
#### Input
<c>["oxxxxooo",<br /> "xooooxxx",<br /> "..xx.ooo",<br /> "oooox.o.",<br /> "..x....."]</c>
#### Output
<c>["oxxxxooo", "x.oo.xxx", "..xxo...", ".oo.x.o.", "ooxo.ooo" ]</c>
#### Reason
Note the final configuration of sand in the second column from the right.

{"oxxxxooo", 
 "x.oo.xxx", 
 "..xxo...", 
 ".oo.x.o.", 
 "ooxo.ooo"}

### Example 6
#### Input
<c>["..o..o..o..o..o..o..o..o..o..o..o",<br /> "o..o..o..o..o..o..o..o..o..o..o..",<br /> ".o..o..o..o..o..o..o..o..o..o..o.",<br /> "...xxx...xxx...xxxxxxxxx...xxx...",<br /> "...xxx...xxx...xxxxxxxxx...xxx...",<br /> "...xxx...xxx......xxx......xxx...",<br /> "...xxxxxxxxx......xxx......xxx...",<br /> "...xxxxxxxxx......xxx......xxx...",<br /> "...xxxxxxxxx......xxx......xxx...",<br /> "...xxx...xxx......xxx............",<br /> "...xxx...xxx...xxxxxxxxx...xxx...",<br /> "...xxx...xxx...xxxxxxxxx...xxx...",<br /> "..o..o..o..o..o..o..o..o..o..o..o",<br /> "o..o..o..o..o..o..o..o..o..o..o..",<br /> ".o..o..o..o..o..o..o..o..o..o..o."]</c>
#### Output
<c>[".................................",<br />".................................",<br />"...ooo...ooo...ooooooooo...ooo...",<br />"...xxx...xxx...xxxxxxxxx...xxx...",<br />"...xxx...xxx...xxxxxxxxx...xxx...",<br />"...xxxoooxxx......xxx......xxx...",<br />"...xxxxxxxxx......xxx......xxx...",<br />"...xxxxxxxxx......xxx......xxx...",<br />"...xxxxxxxxx......xxx......xxx...",<br />"...xxx...xxx......xxx............",<br />"...xxx...xxx...xxxxxxxxx...xxx...",<br />"...xxx...xxx...xxxxxxxxx...xxx...",<br />".................................",<br />"ooo.........ooo.........ooo...ooo",<br />"ooooooooooooooooooooooooooooooooo" ]</c>

