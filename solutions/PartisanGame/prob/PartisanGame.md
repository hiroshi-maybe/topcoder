# [PartisanGame](/tc?module=ProblemDetail&rd=16822&pm=14426)
*Single Round Match 701 Sponsored By BAH Round 1 - Division I, Level One*

## Statement
Alice and Bob play a game with a pile of stones.
Initially, there are *n* stones in the pile.
The players take alternating turns, Alice goes first.

You are given two int[]s: *a* and *b*.
The elements of *a* are allowed moves for Alice, and the elements of *b* are allowed moves for Bob.

In each turn, the current player must remove some stones from the pile.
The number of removed stones must be equal to one of the player's allowed moves.
If a player cannot take a valid turn, they lose the game.

Assume that both Alice and Bob play the game optimally.
Return "Alice" if Alice wins, or "Bob" if Bob wins.
In other words, return "Alice" if and only if the first player has a winning strategy for the given *n*, *a*, and *b*.

## Definitions
- *Class*: `PartisanGame`
- *Method*: `getWinner`
- *Parameters*: `int, int[], int[]`
- *Returns*: `String`
- *Method signature*: `String getWinner(int n, int[] a, int[] b)`

## Constraints
- *n* will be between 0 and 1,000,000,000, inclusive.
- all elements of a will be distinct.
- all elements of b will be distinct.
- all elements of a will be between 1 and 5, inclusive.
- all elements of b will be between 1 and 5, inclusive.

## Examples
### Example 1
#### Input
<c>7,<br />[3, 4],<br />[4]</c>
#### Output
<c>"Alice"</c>
#### Reason
Alice should take 4 stones from the pile.
This will leave a pile of only 3 stones.
In that situation, Bob has no valid move.
(His only allowed move is 4, but it is not possible to remove 4 stones from a pile of only 3 stones.)
Thus, Bob loses the game.

### Example 2
#### Input
<c>10,<br />[1],<br />[4, 3, 2]</c>
#### Output
<c>"Bob"</c>
#### Reason
One winning strategy for Bob is to always take 4 stones.
If Bob follows this strategy, Alice will lose the game during her third turn.

### Example 3
#### Input
<c>104982,<br />[2, 3, 4, 5],<br />[2, 5]</c>
#### Output
<c>"Alice"</c>
### Example 4
#### Input
<c>999999999,<br />[4],<br />[5]</c>
#### Output
<c>"Bob"</c>
### Example 5
#### Input
<c>1000000000,<br />[1,2,3,4,5],<br />[1,2,3,4,5]</c>
#### Output
<c>"Alice"</c>

