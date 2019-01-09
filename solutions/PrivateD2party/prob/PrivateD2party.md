# [PrivateD2party](http://community.topcoder.com/tc?module=ProblemDetail&rd=16463&pm=13824)
*Single Round Match 660 Round 1 - Division II, Level Two*

## Statement
Hero is inviting his friends to the party.

He has n friends, numbered 0 through n-1.
For each of his friends there is at most one other person the friend dislikes.
You are given this information as a int[] *a* with n elements.
For each i, *a*[i] is either the number of the person disliked by friend i, we have *a*[i]=i if friend i likes everybody else.

Hero is inviting his friends one at a time.
Whenever he invites friend i, they will accept if and only if the friend *a*[i] didn't accept an earlier invitation.
(That includes two cases: either Hero didn't invite friend *a*[i] yet, or he did but the friend rejected the invitation.)

Hero noticed that the order in which he invites his friends matters: different orders may produce different numbers of accepted invitations.

Find an order that will produce the most accepted invitations, and return their number.

## Definitions
- *Class*: `PrivateD2party`
- *Method*: `getsz`
- *Parameters*: `int[]`
- *Returns*: `int`
- *Method signature*: `int getsz(int[] a)`

## Constraints
- *a* will contain exactly n elements.
- n will be between 1 and 50, inclusive.
- Each element of *a* will be between 0 and n - 1, inclusive.

## Examples
### Example 1
#### Input
<c>[0,1]</c>
#### Output
<c>2</c>
#### Reason
Each of the friends likes the other. Regardless of the order in which Hero asks them, they will both accept the invitation.

### Example 2
#### Input
<c>[1,0]</c>
#### Output
<c>1</c>
#### Reason
Friend 0 dislikes friend 1 and vice versa. The first friend Hero asks will accept the invitation but then the other friend will certainly reject it.

### Example 3
#### Input
<c>[1,0,3,2]</c>
#### Output
<c>2</c>
### Example 4
#### Input
<c>[5,2,2,4,5,0]</c>
#### Output
<c>5</c>
#### Reason
Here is what would happen if Hero invited the friends in the order (0,1,2,3,4,5):
Friend 5 didn't accept yet, so friend 0 would accept.
Friend 2 didn't accept yet, so friend 1 would accept.
Friend 2 likes everybody and therefore they would accept.
Friend 4 didn't accept yet, so friend 3 would accept.
Friend 5 didn't accept yet, so friend 4 would accept.
Friend 0 did already accept, therefore friend 5 would reject.
It turns out that this solution happens to be optimal: there is no order such that all six friends would accept the invitations.

### Example 5
#### Input
<c>[3,2,1,0,5,4]</c>
#### Output
<c>3</c>

