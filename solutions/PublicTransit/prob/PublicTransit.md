# [PublicTransit](http://community.topcoder.com/tc?module=ProblemDetail&rd=16462&pm=13793)
*Single Round Match 659 Round 1 - Division II, Level Two*

## Statement
Note that this problem has a time limit of 5 seconds.

The city of Gridlock is a grid of cells with *R* rows and *C* columns. Each cell has up to four neighbours: the cells directly above, below, to the left, and to the right. A citizen of Gridlock can travel from a cell to any of its neighbours in one minute.

The citizens of Gridlock are upset that it takes too long to get around, so they have decided to build a teleporter. The teleporter will consist of two identical booths, each located in some cell. If a citizen enters either booth, he or she may choose to teleport to the other booth instantly. It is allowed to build both booths in the same cell.

We define the distance between two cells as the minimum number of minutes needed to get from one cell to another. Let D be the maximum distance between any two cells. Place the teleporter in such a way that D is minimized, and return this minimum value.

## Definitions
- *Class*: `PublicTransit`
- *Method*: `minimumLongestDistance`
- *Parameters*: `int, int`
- *Returns*: `int`
- *Method signature*: `int minimumLongestDistance(int R, int C)`

## Constraints
- *R* is between 1 and 10, inclusive.
- *C* is between 1 and 10, inclusive.

## Examples
### Example 1
#### Input
<c>4,<br />1</c>
#### Output
<c>1</c>
#### Reason
The optimal solution is to connect cell (1, 1) to cell (4, 1). (All cell coordinates are 1-based.)

### Example 2
#### Input
<c>2,<br />2</c>
#### Output
<c>1</c>
### Example 3
#### Input
<c>5,<br />3</c>
#### Output
<c>4</c>
### Example 4
#### Input
<c>8,<br />2</c>
#### Output
<c>4</c>

