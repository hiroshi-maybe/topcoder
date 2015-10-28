# [CombiningSlimes](http://community.topcoder.com/tc?module=ProblemDetail&rd=16549&pm=13947)
*Single Round Match 669 Round 1 - Division II, Level Two*

## Statement
The idols Ami and Mami like playing games.
Today they bought a new game.
At the beginning of the game a group of slimes appears on the screen.
In each turn of the game the player can select any two of the slimes and merge them together.
The game ends when there is only one slime left.

Each slime has a positive integer size.
Whenever the player merges two slimes, the size of the merged slime is x+y, where x and y are the sizes of the two merged slimes.
Additionally, the player is awarded x*y mascots for performing this merge.

Ami and Mami have just started a new game.
You are given a int[] *a* containing the initial sizes of all slimes.
Ami and Mami really like mascots.
Find and return the maximum total number of mascots they can obtain during the game.

## Definitions
- *Class*: `CombiningSlimes`
- *Method*: `maxMascots`
- *Parameters*: `int[]`
- *Returns*: `int`
- *Method signature*: `int maxMascots(int[] a)`

## Constraints
- *a* will contain between 2 and 100 elements, inclusive.
- Each element of *a* will be between 1 and 100, inclusive.

## Examples
### Example 1
#### Input
<c>[3,4]</c>
#### Output
<c>12</c>
#### Reason
There are two slimes, their sizes are 3 and 4.
There is only one possible move: we merge them into a single slime of size 7.
Doing so gives us 3*4 = 12 mascots.

### Example 2
#### Input
<c>[2,2,2]</c>
#### Output
<c>12</c>
#### Reason
In the first turn we will merge any two slimes.
The size of the new slime will be 2+2 = 4, and we will gain 2*2 = 4 mascots.
In the second turn we will merge the two remaining slimes.
The size of the final slime will be 4+2 = 6.
The second merge will give us 4*2 = 8 mascots.
Hence, the total number of mascots we will obtain is 4 + 8 = 12.

### Example 3
#### Input
<c>[1,2,3]</c>
#### Output
<c>11</c>
#### Reason
One optimal solution looks as follows:
First, merge slimes of sizes 1 and 3.
This produces a slime of size 4, and we get 3 mascots.
Then, merge slimes of sizes 4 and 2.
This produces a slime of size 6, and we get 8 mascots.

### Example 4
#### Input
<c>[3,1,2]</c>
#### Output
<c>11</c>
#### Reason
The set of slimes is the same as in Example 2, therefore the correct answer is also the same.
As we can merge any two slimes, their order in *a* does not matter.

### Example 5
#### Input
<c>[7,6,5,3,4,6]</c>
#### Output
<c>395</c>

