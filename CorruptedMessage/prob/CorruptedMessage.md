# [CorruptedMessage](http://community.topcoder.com/tc?module=ProblemDetail&rd=16416&pm=13748)
*Single Round Match 656 Round 1 - Division II, Level One*

## Statement
Your friend just sent you a message.
The message consisted of one or more copies of the same lowercase letter.
For example, "aaaaa" and "xxxxxxxxx" are valid messages.
Unfortunately, on its way to you the message became corrupted: exactly *k* letters of the original message were changed to some other letters.
The message you received is *s*.

Given the String *s* and the int *k*, reconstruct the original message.
More precisely, return a String that could have been the original message.
It is guaranteed that at least one such String will always exist.
If there are multiple possible answers, you may return any of them.

## Definitions
- *Class*: `CorruptedMessage`
- *Method*: `reconstructMessage`
- *Parameters*: `String, int`
- *Returns*: `String`
- *Method signature*: `String reconstructMessage(String s, int k)`

## Constraints
- The number of characters in *s* will be between 1 and 50, inclusive.
- Each character in *s* will be a lowercase letter ('a'-'z').
- *k* will be between 0 and the length of *s*, inclusive.
- At least one possible original message will be consistent with *s* and *k*.

## Examples
### Example 1
#### Input
<c>"hello",<br />3</c>
#### Output
<c>"lllll"</c>
#### Reason
The three corrupted characters have 0-based indices 0, 1, and 4.

### Example 2
#### Input
<c>"abc",<br />3</c>
#### Output
<c>"ddd"</c>
#### Reason
The original message can't be "aaa", "bbb", or "ccc", since we need to change exactly 3 characters.

Some other possible answers include "qqq", "xxx", or "ppp".

### Example 3
#### Input
<c>"wwwwwwwwwwwwwwwwww",<br />0</c>
#### Output
<c>"wwwwwwwwwwwwwwwwww"</c>
#### Reason
No characters were corrupted.

### Example 4
#### Input
<c>"ababba",<br />3</c>
#### Output
<c>"aaaaaa"</c>
#### Reason
"bbbbbb" will also be accepted.

### Example 5
#### Input
<c>"zoztxtoxytyt",<br />10</c>
#### Output
<c>"oooooooooooo"</c>
### Example 6
#### Input
<c>"jlmnmiunaxzywed",<br />13</c>
#### Output
<c>"mmmmmmmmmmmmmmm"</c>

