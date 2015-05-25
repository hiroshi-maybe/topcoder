# [ProblemSetsEasy](http://community.topcoder.com/tc?module=ProblemDetail&rd=16417&pm=13772)
*Single Round Match 657 Round 1 - Division II, Level Two*

## Statement
Cat Snuke came up with some problems. He wants to construct as many problem sets as possible using those problems.

Each problem set must contain exactly three problems: one for the Easy slot, one for the Medium slot, and one for the Hard slot. Each problem can only be assigned to a single slot in a single problem set. He came up with *E* + *EM* + *M* + *MH* + *H* problems in total. The distribution of the problems is as follows:

*E* problems can only be used in the Easy slot.
*EM* problems can be used either in the Easy slot or the Medium slot.
*M* problems can only be used in the Medium slot.
*MH* problems can be used either in the Medium slot or the Hard slot.
*H* problems can only be used in the Hard slot.

Return the maximal number of problem sets he can construct.

## Definitions
- *Class*: `ProblemSetsEasy`
- *Method*: `maxSets`
- *Parameters*: `int, int, int, int, int`
- *Returns*: `int`
- *Method signature*: `int maxSets(int E, int EM, int M, int MH, int H)`

## Constraints
- E, EM, M, MH, H must be between 0 and 100000, inclusive.

## Examples
### Example 1
#### Input
<c>2,<br />2,<br />1,<br />2,<br />2</c>
#### Output
<c>3</c>
#### Reason
One of *EM* problems should be used for the Easy slot, and the other should be used for the Medium slot.
One of *MH* problems should be used for the Medium slot, and the other should be used for the Hard slot.

### Example 2
#### Input
<c>100,<br />100,<br />100,<br />0,<br />0</c>
#### Output
<c>0</c>
#### Reason
Unfortunately, no problem can be used for the Hard slot.

### Example 3
#### Input
<c>657,<br />657,<br />657,<br />657,<br />657</c>
#### Output
<c>1095</c>
### Example 4
#### Input
<c>1,<br />2,<br />3,<br />4,<br />5</c>
#### Output
<c>3</c>
### Example 5
#### Input
<c>100000,<br />100000,<br />100000,<br />100000,<br />100000</c>
#### Output
<c>166666</c>

