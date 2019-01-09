# [InfiniteString](http://community.topcoder.com/tc?module=ProblemDetail&rd=16461&pm=13783)
*Single Round Match 658 Round 1 - Division II, Level One*

## Statement
Given a string s, let f(s) denote the infinite string obtained by concatenating infinitely many copies of s.
For example, if s = "abc" then f(s) = "abcabcabcabc...".

Note that the string f(s) still has a beginning.
Hence, f("abc") and f("bca") are two different infinite strings: the first one starts with an 'a' while the other starts with a 'b'.

Sometimes, two different finite strings can produce the same infinite string.
For example, f("abc") is the same as f("abcabc").

You are given Strings *s* and *t*.
Check whether f(*s*) equals f(*t*).
If the two infinite strings are equal, return "Equal".
Otherwise, return "Not equal".

## Definitions
- *Class*: `InfiniteString`
- *Method*: `equal`
- *Parameters*: `String, String`
- *Returns*: `String`
- *Method signature*: `String equal(String s, String t)`

## Constraints
- *s* will contain between 1 and 50 elements, inclusive.
- *t* will contain between 1 and 50 elements, inclusive.
- Each character in *s* will be a lowercase English letter ('a'-'z').
- Each character in *t* will be a lowercase English letter ('a'-'z').

## Examples
### Example 1
#### Input
<c>"ab",<br />"abab"</c>
#### Output
<c>"Equal"</c>
#### Reason
Both string will generate "ababababab...".

### Example 2
#### Input
<c>"abc",<br />"bca"</c>
#### Output
<c>"Not equal"</c>
### Example 3
#### Input
<c>"abab",<br />"aba"</c>
#### Output
<c>"Not equal"</c>
#### Reason
The first one will generate "abababab...", but the second one will generate "abaaba...".

### Example 4
#### Input
<c>"aaaaa",<br />"aaaaaa"</c>
#### Output
<c>"Equal"</c>
### Example 5
#### Input
<c>"ababab",<br />"abab"</c>
#### Output
<c>"Equal"</c>
### Example 6
#### Input
<c>"a",<br />"z"</c>
#### Output
<c>"Not equal"</c>

