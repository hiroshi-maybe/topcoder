# [MutaliskEasy](http://community.topcoder.com/tc?module=ProblemDetail&rd=16461&pm=13782)
*Single Round Match 658 Round 1 - Division II, Level Two*

## Statement
Fox Ciel is writing an AI for the game Starcraft and she needs your help.

In Starcraft, one of the available units is a mutalisk.
Mutalisks are very useful for harassing Terran bases.
Fox Ciel has one mutalisk.
The enemy base contains one or more Space Construction Vehicles (SCVs).
Each SCV has some amount of hit points.

When the mutalisk attacks, it can target up to three different SCVs.
The first targeted SCV will lose 9 hit points.
The second targeted SCV (if any) will lose 3 hit points.
The third targeted SCV (if any) will lose 1 hit point.
If the hit points of a SCV drop to 0 or lower, the SCV is destroyed.
Note that you may not target the same SCV twice in the same attack.

You are given a int[] *HP* containing the current hit points of your enemy's SCVs.
Return the smallest number of attacks in which you can destroy all these SCVs.

## Definitions
- *Class*: `MutaliskEasy`
- *Method*: `minimalAttacks`
- *Parameters*: `int[]`
- *Returns*: `int`
- *Method signature*: `int minimalAttacks(int[] x)`

## Constraints
- *x* will contain between 1 and 3 elements, inclusive.
- Each element in *x* will be between 1 and 60, inclusive.

## Examples
### Example 1
#### Input
<c>[12,10,4]</c>
#### Output
<c>2</c>
#### Reason
You can destroy all SCVs in two attacks as follows:
Target the SCVs in the order 0, 2, 1. Their hit points after the attack will be {12-9, 10-1, 4-3} = {3, 9, 1}.
Target the SCVs in the order 1, 0, 2. Their hit points will drop exactly to {0, 0, 0}.

### Example 2
#### Input
<c>[54,18,6]</c>
#### Output
<c>6</c>
#### Reason
You should attack 6 times, always in the order 0, 1, 2.

### Example 3
#### Input
<c>[55,60,53]</c>
#### Output
<c>13</c>
### Example 4
#### Input
<c>[1,1,1]</c>
#### Output
<c>1</c>
### Example 5
#### Input
<c>[60, 40]</c>
#### Output
<c>9</c>
### Example 6
#### Input
<c>[60]</c>
#### Output
<c>7</c>

