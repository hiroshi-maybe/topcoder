# [BearDartsDiv2](http://community.topcoder.com/tc?module=ProblemDetail&rd=16551&pm=13479)
*Single Round Match 671 Round 1 - Division II, Level Two*

## Statement
Limak is an old brown bear who likes to play darts.

Limak just picked up an empty scorecard.
He then threw a sequence of darts into a dartboard and for each dart he recorded the point value of the area it hit.
You are given a int[] *w* containing the contents of Limak's scorecard: a sequence of point values.

Today there is a special jackpot.
In order to win the jackpot, the player must present a scorecard with exactly four scores: (a, b, c, d).
Additionally, these scores must be such that a*b*c = d.
Note that order matters: the scores a, b, c, d must have been obtained in this particular order.

Limak wants to erase all but four scores from his scorecard in such a way that he will win the jackpot.
Compute and return the number of different ways in which he can do that.

## Definitions
- *Class*: `BearDartsDiv2`
- *Method*: `count`
- *Parameters*: `int[]`
- *Returns*: `long`
- *Method signature*: `long count(int[] w)`

## Notes
- Pay attention to the unusual time limit.

## Constraints
- *w* will contain between 4 and 500 elements, inclusive.
- Each element in *w* will be between 1 and 10^6, inclusive.

## Examples
### Example 1
#### Input
<c>[10,2,2,7,40,160]</c>
#### Output
<c>2</c>
#### Reason
Limak must erase two of the six scores on his scorecard.
There are two ways to do that and win the jackpot:
Erase the elements on 0-based indices 3 and 5. You are left with (a,b,c,d) = (10,2,2,40), and 10*2*2 = 40.
Erase the elements on 0-based indices 0 and 3. You are left with (a,b,c,d) = (2,2,40,160), and 2*2*40 = 160.

### Example 2
#### Input
<c>[128,64,32,16,8,4,2,1]</c>
#### Output
<c>0</c>
#### Reason
Regardless of which four scores Limak erases, the remaining four will always have a > b > c > d and therefore it cannot be the case that a*b*c = d.

### Example 3
#### Input
<c>[2,3,4,5,6,8,12,16,20,24,40,24,20,16,12,8,6,5,4,3,2]</c>
#### Output
<c>3</c>
### Example 4
#### Input
<c>[100,100,100,1000000,1000000,1000000,1000000,1000000]</c>
#### Output
<c>5</c>
### Example 5
#### Input
<c>[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,<br />1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]</c>
#### Output
<c>2573031125</c>

