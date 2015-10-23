# [Cdgame](http://community.topcoder.com/tc?module=ProblemDetail&rd=16550&pm=14062)
*Single Round Match 670 Round 1 - Division II, Level One*

## Statement
Two players are playing a cooperative game.

At the beginning of the game each player has some cards.
There is a positive integer written on each card.

The game is played as follows:

Each player chooses one of their cards.
At the same time, each player gives the chosen card to the other player.
Each player computes the sum of the numbers on the cards they now have.
The final outcome of the game is the product of the two sums the players computed in the previous step.

You are given the int[]s *a* and *b*.
The elements of *a* are the numbers on the first player's cards at the beginning of the game.
The elements of *b* are the numbers on the second player's cards.

Compute and return the number of different outcomes the game may have.

## Definitions
- *Class*: `Cdgame`
- *Method*: `rescount`
- *Parameters*: `int[], int[]`
- *Returns*: `int`
- *Method signature*: `int rescount(int[] a, int[] b)`

## Constraints
- *A* and *B* will contain between 1 and 50 elements, inclusive.
- *A* and *B* will contain the same number of elements.
- Each element in *A* and *B* will be between 1 and 100, inclusive.

## Examples
### Example 1
#### Input
<c>[1,2],<br />[3,4]</c>
#### Output
<c>2</c>
#### Reason
This game can be played in four possible ways.
One of them looks as follows:
The first player chooses the card with the number 1. At the same time, the second player chooses the card with the number 3.
Each player gives the chosen card to the other player. After the exchange the first player has the cards with numbers 2 and 3, and the second player has the cards with numbers 1 and 4.
The first player computes that his sum is 2+3 = 5. The second player computes that her sum is 1+4 = 5.
The final outcome is the value 5*5 = 25.
The other three ways correspond to the following outcomes: (2+4)*(1+3) = 6*4 = 24, (1+3)*(2+4) = 4*6 = 24, and (1+4)*(2+3) = 5*5 = 25.
Hence, only two different outcomes are possible: 24 and 25.
Thus, the correct return value is 2.

### Example 2
#### Input
<c>[1,2,4],<br />[8,16,32]</c>
#### Output
<c>9</c>
#### Reason
With three cards in each player's hand there are 9 ways to play the game.
In this case each of those ways leads to a different outcome.

### Example 3
#### Input
<c>[1,1,1],<br />[1,1,1]</c>
#### Output
<c>1</c>
#### Reason
Again, there are 9 ways to play the game, but obviously in this case the outcome will always be the same.

### Example 4
#### Input
<c>[1,2,3],<br />[5,5,5]</c>
#### Output
<c>3</c>
### Example 5
#### Input
<c>[3,3,4,1],<br />[2,2,2,100]</c>
#### Output
<c>4</c>
### Example 6
#### Input
<c>[31,34,55,56,57],<br />[1,2,3,4,5]</c>
#### Output
<c>15</c>

