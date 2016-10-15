# [XYZCoder](/tc?module=ProblemDetail&rd=16821&pm=14401)
*Single Round Match 700 Sponsored by Booz Allen Ham Round 1 - Division II, Level Three*

## Statement
You are going to take part in a popular online programming contest.
During the contest the contestants will be split across *room* rooms, with exactly *size* contestants in each room.
(Hence, there will be exactly *room***size* contestants.)
The rooms will be numbered from 1 to *room*.

The contest is such that there will be no ties.
After the contest, each contestant will have a distinct rank between 1 and *room***size*, inclusive.
(The contestant with rank 1 is the winner.)

A room winner is the contestant with the best (i.e., smallest) rank in their room.

You are interested in the ranks of all room winners.
Once the contest finishes, you will write down a sequence of *room* positive integers.
For each i, the i-th element of this sequence will be the rank of the winner of room i.

You are given the ints *room* and *size*.
Let L be the number of different sequences you can possibly obtain.
Compute and return the value (L modulo 1,000,000,007).

## Definitions
- *Class*: `XYZCoder`
- *Method*: `countWays`
- *Parameters*: `int, int`
- *Returns*: `int`
- *Method signature*: `int countWays(int room, int size)`

## Constraints
- *room* will be between 1 and 100, inclusive.
- *size* will be between 1 and 100, inclusive.

## Examples
### Example 1
#### Input
<c>2,<br />1</c>
#### Output
<c>2</c>
#### Reason
There are 2 rooms, each with 1 contestant.
If contestant in room 1 wins the contest, you will write down the list {1,2}.
Otherwise, you will write down the list {2,1}.
Note that these are considered to be two distinct sequences.

### Example 2
#### Input
<c>1,<br />2</c>
#### Output
<c>1</c>
#### Reason
There is 1 room with 2 contestants.
Regardless of which of them wins, the winner of the only room will have rank 1, so you will write down the list {1}.

### Example 3
#### Input
<c>2,<br />2</c>
#### Output
<c>4</c>
#### Reason
Now we have 2 rooms, each with 2 contestants.
In this case you will write down one of the following four lists: {1,2}, {2,1}, {1,3}, or {3,1}.
Note the following:
You will never write down the list {2,3}, because the winner of the entire contest (rank 1) has to be the winner of one of the rooms.
You will never write down the list {1,4}, because the contestant with rank 4 cannot be a room winner in this setting.

### Example 4
#### Input
<c>4,<br />5</c>
#### Output
<c>6840</c>
### Example 5
#### Input
<c>100,<br />100</c>
#### Output
<c>718243627</c>

