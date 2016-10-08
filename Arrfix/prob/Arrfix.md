# [Arrfix](/tc?module=ProblemDetail&rd=16775&pm=14361)
*Single Round Match 696 Round 1 - Division II, Level Two*

## Statement
Hero has two arrays, *A* and *B*, each containing the same number of integers.
He wants to change *A* into an array that will resemble *B* as closely as possible.
More precisely, the difference between two arrays of equal length is the number of indices where the two arrays differ.
Hero wants to minimize the distance between the modified array *A* and the original array *B*.

Hero can only modify *A* by using stickers.
He has a collection of stickers.
Each sticker contains a single integer.
Each sticker can be used to cover a single element of *A*.
Hero must use each sticker exactly once, and he cannot use multiple stickers on the same element of *A*.

You are given the original arrays in the int[]s *A* and *B*, and the collection of stickers in the int[] *F*.
Return the smallest possible difference between *A* and *B* after all stickers from *F* have been used to replace some elements of *A*.

## Definitions
- *Class*: `Arrfix`
- *Method*: `mindiff`
- *Parameters*: `int[], int[], int[]`
- *Returns*: `int`
- *Method signature*: `int mindiff(int[] A, int[] B, int[] F)`

## Constraints
- *A* will contain between 1 and 50 elements, inclusive.
- *A* and *B* will contain the same number of elements.
- Size of *F* won't be larger than size of *A*.
- Each element in *A*, *B* and *F* will be between 1 and 1000, inclusive.

## Examples
### Example 1
#### Input
<c>[1,1,1],<br />[2,2,2],<br />[2]</c>
#### Output
<c>2</c>
### Example 2
#### Input
<c>[1,1,1],<br />[2,2,1],<br />[2,2]</c>
#### Output
<c>0</c>
### Example 3
#### Input
<c>[1,2,3],<br />[3,2,1],<br />[]</c>
#### Output
<c>2</c>
#### Reason
Hero has no stickers. The given arrays *A* and *B* differ on two positions: on 0-based indices 0 and 2.

### Example 4
#### Input
<c>[2,2,2],<br />[2,2,2],<br />[1,2,3]</c>
#### Output
<c>2</c>
#### Reason
Note that Hero must use all the stickers. Originally the two arrays are the same, but applying all the stickers creates two differences, regardless of the order in which you use them.

### Example 5
#### Input
<c>[1,3,3,3],<br />[2,3,3,3],<br />[2,2]</c>
#### Output
<c>1</c>

