# [EightRooks](http://community.topcoder.com/tc?module=ProblemDetail&rd=16417&pm=13773)
*Single Round Match 657 Round 1 - Division II, Level One*

## Statement
Cat Snuke is playing a puzzle called Eight Rooks Puzzle.

In this puzzle, he must put exactly eight rooks onto an 8x8 chessboard. No two rooks must be in the same row, and no two rooks must be in the same column.

You are given a String[] *board*. The j-th character of the i-th element of *board* is either 'R' or '.'. If this is 'R', the cell in row i, column j contains a rook. Otherwise the cell doesn't contain a rook.

Determine whether Snuke solved the puzzle correctly. If he solved the puzzle correctly, return "Correct". Otherwise return "Incorrect".

## Definitions
- *Class*: `EightRooks`
- *Method*: `isCorrect`
- *Parameters*: `String[]`
- *Returns*: `String`
- *Method signature*: `String isCorrect(String[] board)`

## Constraints
- *board* will contain exactly 8 elements.
- Each element of *board* will contain exactly 8 characters.
- Each character in *board* will be either 'R' or '.'.

## Examples
### Example 1
#### Input
<c>["R.......",<br /> ".R......",<br /> "..R.....",<br /> "...R....",<br /> "....R...",<br /> ".....R..",<br /> "......R.",<br /> ".......R"]</c>
#### Output
<c>"Correct"</c>
### Example 2
#### Input
<c>["........",<br /> "....R...",<br /> "........",<br /> ".R......",<br /> "........",<br /> "........",<br /> "..R.....",<br /> "........"]</c>
#### Output
<c>"Incorrect"</c>
#### Reason
The number of rooks is not eight.

### Example 3
#### Input
<c>["......R.",<br /> "....R...",<br /> "...R....",<br /> ".R......",<br /> "R.......",<br /> ".....R..",<br /> "..R.....",<br /> ".......R"]</c>
#### Output
<c>"Correct"</c>
### Example 4
#### Input
<c>["......R.",<br /> "....R...",<br /> "...R....",<br /> ".R......",<br /> "R.......",<br /> ".......R",<br /> "..R.....",<br /> ".......R"]</c>
#### Output
<c>"Incorrect"</c>
#### Reason
The rightmost column contains two rooks.

### Example 5
#### Input
<c>["........",<br /> "........",<br /> "........",<br /> "........",<br /> "........",<br /> "........",<br /> "........",<br /> "........"]</c>
#### Output
<c>"Incorrect"</c>

