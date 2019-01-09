## Solutions

Complexity (Loop count or count of recursive calls) for demo case 2

Memoized recursion (sort) | Memoized recursion | Brute force      | Recursion (no memoization)
--------------------------|--------------------|------------------|---------------------
19503 (36 ms)             | 41847 (53 ms)      | 1048576 (429 ms) | More than 10^8 (N/A)

## Memoized recursion (sort)

MutaliskEasy.cpp

```bash
$ make sys 
88 cases checked, 0 failures, 0 errors
   Total time taken: 787 ms
   Average time taken: 8 ms
   Slowest running case: 31 ms (case 73)
```

Complexity
```bash
$ make demo
Case 0 ... lc = 628
9ms Passed
Case 1 ... lc = 4359
16ms Passed
Case 2 ... lc = 19503
36ms Passed
Case 3 ... lc = 1
6ms Passed
Case 4 ... lc = 6728
21ms Passed
Case 5 ... lc = 763
7ms Passed
```	    

## Memoized recursion

MutaliskEasy-nosort.cpp

```bash
$ make sys 
88 cases checked, 0 failures, 0 errors
   Total time taken: 1046 ms
   Average time taken: 11 ms
   Slowest running case: 66 ms (case 58)
```

Complexity
```bash
$ make demo
Case 0 ... lc = 320
8ms Passed
Case 1 ... lc = 3292
8ms Passed
Case 2 ... lc = 41847
53ms Passed
Case 3 ... lc = 1
7ms Passed
Case 4 ... lc = 9027
18ms Passed
Case 5 ... lc = 307
7ms Passed
```

## Brute force

MutaliskEasy-bruteforce.cpp

```bash
$ make sys 
88 cases checked, 0 failures, 0 errors
   Total time taken: 37905 ms	
   Average time taken: 430 ms
   Slowest running case: 561 ms (case 4)
```

Complexity
```bash
$ make demo
Case 0 ... lc = 1048576
415ms Passed
Case 1 ... lc = 1048576
469ms Passed
Case 2 ... lc = 1048576
429ms Passed
Case 3 ... lc = 1048576
433ms Passed
Case 4 ... lc = 1048576
428ms Passed
Case 5 ... lc = 1048576
425ms Passed
```