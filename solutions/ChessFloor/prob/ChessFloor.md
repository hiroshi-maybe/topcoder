# [ChessFloor](http://community.topcoder.com/tc?module=ProblemDetail&rd=16512&pm=13917)
*Single Round Match 663 Round 1 - Division II, Level One*

## Statement
Samantha is renovating a square room.
The floor of the room is an N times N grid of unit square tiles.
Each tile has some color.
You are given the current colors of all tiles in a String[] *floor* with N elements, each containing N characters.
Each character represents one tile.
Identical characters represent tiles of the same color.

Samantha wants to be able to play chess or checkers on the floor.
Hence, she wants to change the entire floor into a checkerboard pattern.
A checkerboard pattern has two properties:

there are exactly two distinct colors of tiles
no two tiles of the same color share a common side

For example, this is a checkerboard pattern:

afa
faf
afa

This is not a checkerboard pattern because there are more than two distinct colors:

aba
bcb
aba

This is not a checkerboard pattern because there are two tiles that share a side and have the same color:

aaa
bab
aba

Samantha wants to change her floor into a checkerboard pattern by changing the colors of as few tiles as possible.
Compute and return the number of tiles she needs to change.

## Definitions
- *Class*: `ChessFloor`
- *Method*: `minimumChanges`
- *Parameters*: `String[]`
- *Returns*: `int`
- *Method signature*: `int minimumChanges(String[] floor)`

## Constraints
- N will be between 2 and 20, inclusive.
- *floor* will contain exactly N elements.
- Each element of *floor* will consist of exactly N characters.
- Each character in *floor* will be a lowercase English letter ('a'-'z').

## Examples
### Example 1
#### Input
<c>["aba",<br /> "bbb",<br /> "aba"]</c>
#### Output
<c>1</c>
#### Reason
This is not a checkerboard pattern, but Samantha can change it into a checkerboard pattern easily.
All she needs to do is to change the color of the middle tile from 'b' to 'a'.
The smallest possible number of changes is therefore 1.

### Example 2
#### Input
<c>["wbwbwbwb",<br /> "bwbwbwbw",<br /> "wbwbwbwb",<br /> "bwbwbwbw",<br /> "wbwbwbwb",<br /> "bwbwbwbw",<br /> "wbwbwbwb",<br /> "bwbwbwbw"]</c>
#### Output
<c>0</c>
#### Reason
This floor already has a checkerboard pattern, so no changes are necessary.

### Example 3
#### Input
<c>["zz",<br /> "zz"]</c>
#### Output
<c>2</c>
#### Reason
A checkerboard pattern must contain tiles of two distinct colors.

### Example 4
#### Input
<c>["helloand",<br /> "welcomet",<br /> "osingler",<br /> "oundmatc",<br /> "hsixhund",<br /> "redandsi",<br /> "xtythree",<br /> "goodluck"]</c>
#### Output
<c>56</c>
### Example 5
#### Input
<c>["jecjxsengslsmeijrmcx",<br /> "tcfyhumjcvgkafhhffed",<br /> "icmgxrlalmhnwwdhqerc",<br /> "xzrhzbgjgabanfxgabed",<br /> "fpcooilmwqixfagfojjq",<br /> "xzrzztidmchxrvrsszii",<br /> "swnwnrchxujxsknuqdkg",<br /> "rnvzvcxrukeidojlakcy",<br /> "kbagitjdrxawtnykrivw",<br /> "towgkjctgelhpomvywyb",<br /> "ucgqrhqntqvncargnhhv",<br /> "mhvwsgvfqgfxktzobetn",<br /> "fabxcmzbbyblxxmjcaib",<br /> "wpiwnrdqdixharhjeqwt",<br /> "xfgulejzvfgvkkuyngdn",<br /> "kedsalkounuaudmyqggb",<br /> "gvleogefcsxfkyiraabn",<br /> "tssjsmhzozbcsqqbebqw",<br /> "ksbfjoirwlmnoyyqpbvm",<br /> "phzsdodppzfjjmzocnge"]</c>
#### Output
<c>376</c>

