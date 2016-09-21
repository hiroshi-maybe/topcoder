# [SubtreeSum](/tc?module=ProblemDetail&rd=16802&pm=14392)
*Single Round Match 698 Sponsored by Google Round 1 - Division II, Level Three*

## Statement
You are given an undirected tree.
The tree has n vertices, numbered 0 through n-1.
For each valid i, there is an edge between the vertices *p*[i] and (i+1).
Each vertex i has a nonnegative integer weight *x*[i].

All nonempty connected subgraphs of our tree are called its subtrees.
The value of a subtree is the bitwise OR of the weights of its vertices.
For example, a subtree that contains vertices with weights 1, 4, and 6 has the value (1 OR 4 OR 6) = 7.

You are given the description of the tree: the int[]s *p* and *x*.
Compute and return the sum of values of all subtrees, modulo 10^9 + 7.

## Definitions
- *Class*: `SubtreeSum`
- *Method*: `getSum`
- *Parameters*: `int[], int[]`
- *Returns*: `int`
- *Method signature*: `int getSum(int[] p, int[] x)`

## Constraints
- n will be between 2 and 50, inclusive.
- *p* will contain exactly n-1 elements.
- For each i, 0 <= *p*[i] <= i.
- *x* will contain exactly n elements.
- Each element in *x* will be between 0 and 1,000,000,000, inclusive.

## Examples
### Example 1
#### Input
<c>[0],<br />[1,2]</c>
#### Output
<c>6</c>
#### Reason
This is a tree with two vertices and a single edge 0-1.
This tree has three subtrees:
A subtree that only contains the vertex 0.
A subtree that only contains the vertex 1.
A subtree that contains both vertices.
The values of these three subtrees are 1, 2, and 3.
Hence, the correct return value is 1+2+3 = 6.

### Example 2
#### Input
<c>[0,1],<br />[1,2,4]</c>
#### Output
<c>23</c>
#### Reason
This tree has six subtrees.
Their values are 1, 2, 4, 3, 6, and 7, respectively.
The sum of these values is 23.

### Example 3
#### Input
<c>[0,0,0,0,0,0,0,0,0,0],<br />[1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000]</c>
#### Output
<c>33999993</c>
#### Reason
This tree has 1034 subtrees.
Each of those subtrees has value 1,000,000.
Hence, the sum of values of all subtrees is 1,034,000,000.
We should return 1,034,000,000 modulo (10^9 + 7) = 33,999,993.

### Example 4
#### Input
<c>[0,0,1,0,2,2,3,0,0,2,1],<br />[4,5,6,7,0,8,9,5,1,2,3,6]</c>
#### Output
<c>6378</c>

