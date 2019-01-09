# [DivisibleSetDiv2](/tc?module=ProblemDetail&rd=16776&pm=14369)
*Single Round Match 697 Round 1 - Division II, Level Two*

## Statement
You are given a int[] *b* containing a sequence of n positive integers: *b*[0], ..., *b*[n-1].
We are now looking for another sequence a[0], ..., a[n-1].
This sequence should have the following properties:
Each a[i] should be a number of the form 2^x[i] where x[i] is some positive integer. In other words, each a[i] is one of the numbers 2, 4, 8, 16, ...
For each i, the value a[i]^*b*[i] (that is, a[i] to the power *b*[i]) should be divisible by P, where P is the product of all a[i].

Determine whether there is at least one sequence with the desired properties.
Return "Possible" (quotes for clarity) if such a sequence exists and "Impossible" otherwise.

## Definitions
- *Class*: `DivisibleSetDiv2`
- *Method*: `isPossible`
- *Parameters*: `int[]`
- *Returns*: `String`
- *Method signature*: `String isPossible(int[] b)`

## Constraints
- *b* will contain between 1 and 50 elements, inclusive.
- Each element in *b* will be between 1 and 10, inclusive.

## Examples
### Example 1
#### Input
<c>[3,2]</c>
#### Output
<c>"Possible"</c>
#### Reason
One valid sequence is the sequence {2, 2}.
That is, a[0] = a[1] = 2.
Clearly, each a[i] is a power of two not smaller than 2.
The product of all a[i] is 2*2 = 4.
Both a[0]^*b*[0] = 2^3 = 8 and a[1]^*b*[1] = 2^2 = 4 are divisible by 4.

### Example 2
#### Input
<c>[3,3,3]</c>
#### Output
<c>"Possible"</c>
#### Reason
Here, one valid sequence is {2, 2, 2}.

### Example 3
#### Input
<c>[1,10]</c>
#### Output
<c>"Impossible"</c>
#### Reason
Suppose that a[0] = x and a[1] = y.
The value a[0]^*b*[0] = x^1 should be divisible by x*y.
This is only possible for y = 1.
However, 1 is not a positive power of two, so we cannot have a[1] = 1.

### Example 4
#### Input
<c>[2, 3, 10]</c>
#### Output
<c>"Possible"</c>
#### Reason
One valid sequence is {8, 4, 2}.

### Example 5
#### Input
<c>[7,10,4,6,3]</c>
#### Output
<c>"Possible"</c>
### Example 6
#### Input
<c>[9,9,9,9,9,9,9,9,9]</c>
#### Output
<c>"Possible"</c>
### Example 7
#### Input
<c>[3,4,5,6,7]</c>
#### Output
<c>"Impossible"</c>

