# [Initials](/tc?module=ProblemDetail&rd=16802&pm=14389)
*Single Round Match 698 Sponsored by Google Round 1 - Division II, Level One*

## Statement
When dealing with long names and phrases, we sometimes use the initial letters of words to form its acronym.
For example, we use "JFK" instead of "John Fitzgerald Kennedy", "lgtm" instead of "looks good to me", and so on.

You are given a String *name*.
This String contains a phrase: one or more words separated by single spaces.
Please compute and return the acronym of this phrase.
(As above, the acronym should consist of the first letter of each word, in order.)

## Definitions
- *Class*: `Initials`
- *Method*: `getInitials`
- *Parameters*: `String`
- *Returns*: `String`
- *Method signature*: `String getInitials(String name)`

## Constraints
- *name* will contain between 1 and 50 characters, inclusive.
- Each character in *s* will be a space or a lowercase English letter ('a' - 'z').
- The first and last character in *s* will not be a space.
- No two continuous spaces can appear in *s*.

## Examples
### Example 1
#### Input
<c>"john fitzgerald kennedy"</c>
#### Output
<c>"jfk"</c>
#### Reason
There are three words: "john", "fitzgerald" and "kennedy".
Their first letters are 'j', 'f' and 'k'.
The correct return value is their concatenation: the string "jfk".
Note that all letters in our problem are in lowercase.

### Example 2
#### Input
<c>"single"</c>
#### Output
<c>"s"</c>
#### Reason
There is only one word: "single". Its acronym has a single letter.

### Example 3
#### Input
<c>"looks good to me"</c>
#### Output
<c>"lgtm"</c>
### Example 4
#### Input
<c>"single round match"</c>
#### Output
<c>"srm"</c>
### Example 5
#### Input
<c>"a aa aaa aa a bbb bb b bb bbb"</c>
#### Output
<c>"aaaaabbbbb"</c>

