# [BichromeBoard](http://community.topcoder.com/tc?module=ProblemDetail&rd=16415&pm=13719)
*Single Round Match 655 Round 1 - Division II, Level One*

## Statement
We have a rectangular board divided into a grid of unit squares.
We are going to color each square either white or black.

You are given the String[] *board*.
Each character in *board* represents one unit square.
If *board*[i][j] is 'B', the corresponding square must be black.
If *board*[i][j] is 'W', the corresponding square must be white.
Finally, if *board*[i][j] is '?', you get to choose the color for this square: either white or black.

Two squares are adjacent if they share a common side.
We want to color the board in such a way that no two adjacent squares share the same color.
Return "Possible" (quotes for clarity) if it can be done, or "Impossible" otherwise.

## Definitions
- *Class*: `BichromeBoard`
- *Method*: `ableToDraw`
- *Parameters*: `String[]`
- *Returns*: `String`
- *Method signature*: `String ableToDraw(String[] board)`

## Constraints
- *board* will contain between 1 and 50 elements, inclusive.
- Each element in *board* will contain between 1 and 50 characters, inclusive.
- Each element in *board* will contain the same number of characters.
- Each character in *board* will be one of 'W', 'B', '?'.

## Examples
### Example 1
#### Input
<c>["W?W",<br /> "??B",<br /> "???"]</c>
#### Output
<c>"Possible"</c>
#### Reason
The solution is:
WBW
BWB
WBW

### Example 2
#### Input
<c>["W??W"]</c>
#### Output
<c>"Impossible"</c>
#### Reason
The four possible colorings of this board are WWWW, WWBW, WBWW, and WBBW.

In each of them there is at least one pair of adjacent squares that share the same color.

Thus, there is no way to get a pattern with the desired property.

### Example 3
#### Input
<c>["??"]</c>
#### Output
<c>"Possible"</c>
#### Reason
There are 2 ways:
WB and BW

### Example 4
#### Input
<c>["W???",<br /> "??B?",<br /> "W???",<br /> "???W"]</c>
#### Output
<c>"Possible"</c>
### Example 5
#### Input
<c>["W???",<br /> "??B?",<br /> "W???",<br /> "?B?W"]</c>
#### Output
<c>"Impossible"</c>
### Example 6
#### Input
<c>["B"]</c>
#### Output
<c>"Possible"</c>

