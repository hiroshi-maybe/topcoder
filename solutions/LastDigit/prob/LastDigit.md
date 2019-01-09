# [LastDigit](/tc?module=ProblemDetail&rd=16803&pm=14397)
*Single Round Match 699 Sponsored by Cisco Round 1 - Division II, Level Two*

## Statement
Limak chose a positive integer X and wrote it on a blackboard.
After that, every day he erased the last digit of the current number.
He stopped when he erased all digits.

After the process was over, Limak computed the sum of all numbers that appeared on the blackboard, including the original number X.

For example, if the original number was 509, the numbers that appeared on the blackboard were the numbers 509, 50, and 5.
Their sum is 564.

You are given a long *S*.
Limak wants you to find a number X such that the above process produces the sum *S*.
It can be shown that for any positive *S* there is at most one valid X.
If there is a valid X, find and return it.
Otherwise, return -1.

## Definitions
- *Class*: `LastDigit`
- *Method*: `findX`
- *Parameters*: `long`
- *Returns*: `long`
- *Method signature*: `long findX(long S)`

## Constraints
- *S* will be between 1 and 10^18, inclusive.

## Examples
### Example 1
#### Input
<c>564</c>
#### Output
<c>509</c>
#### Reason
This is the example from the problem statement. The value X = 509 produces the sum 564, as shown above.

### Example 2
#### Input
<c>565</c>
#### Output
<c>-1</c>
#### Reason
There is no X for which the sum would be 565.

### Example 3
#### Input
<c>3000</c>
#### Output
<c>2701</c>
#### Reason
You can check that 2701 + 270 + 27 + 2 = 3000.

### Example 4
#### Input
<c>137174210616796</c>
#### Output
<c>123456789555123</c>
### Example 5
#### Input
<c>837592744927492746</c>
#### Output
<c>-1</c>
### Example 6
#### Input
<c>999999999999999999</c>
#### Output
<c>900000000000000000</c>

