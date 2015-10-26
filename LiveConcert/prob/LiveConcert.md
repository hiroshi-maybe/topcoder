# [LiveConcert](http://community.topcoder.com/tc?module=ProblemDetail&rd=16549&pm=13948)
*Single Round Match 669 Round 1 - Division II, Level One*

## Statement
Today, a large live concert is going to take place.
Some interprets (called "idols") are going to perform at the concert.
Different idols have different names.

There are M distinct songs that can be included in the concert.
The songs are numbered 0 through M-1.
Song i can only be performed by the idol *s*[i].
Including this song in the concert will increase the happiness of the audience by *h*[i].

We have to choose the set list for this concert.
Our goal is to make the audience as happy as possible.
However, the concert time is limited and therefore each idol can only perform at most one song.

You are given the int[] *h* and the String[] *s* with M elements each.
Find the set of songs that should be played at the concert.
The set of songs must have the following properties:

Each idol will perform at most one song.
After hearing the songs, the happiness of the audience will increase by the largest amount possible.
Return the largest possible amount of happiness the audience can gain.

## Definitions
- *Class*: `LiveConcert`
- *Method*: `maxHappiness`
- *Parameters*: `int[], String[]`
- *Returns*: `int`
- *Method signature*: `int maxHappiness(int[] h, String[] s)`

## Notes
- The value M is not given explicitly. You can determine M as the length of *h*.

## Constraints
- M will be between 1 and 100, inclusive.
- *h* and *s* will contain exactly M elements each.
- All numbers in *h* will be between 1 and 100, inclusive.
- All strings in *s* will have between 1 and 10 characters, inclusive.
- For each valid i, each character in *s*[i] will be a lowercase letter ('a'-'z').

## Examples
### Example 1
#### Input
<c>[10,5,6,7,1,2],<br />["ciel","bessie","john","bessie","bessie","john"]</c>
#### Output
<c>23</c>
#### Reason
The optimal concert will contain three songs:
"ciel" will sing the song number 0, which will give the audience 10 happiness
"bessie" will sing the song number 3, which will give the audience 7 happiness
"john" will sing the song number 2, which will give the audience 6 happiness
The total amount of happiness will be 10+7+6 = 23.

### Example 2
#### Input
<c>[3,3,4,3,3],<br />["a","a","a","a","a"]</c>
#### Output
<c>4</c>
#### Reason
There is a single idol, thus the concert will consist of a single song.
The optimal choice is the song that gives 4 happiness.

### Example 3
#### Input
<c>[1,2,3,4,5,6,7,8,9,10,100],<br />["a","b","c","d","e","e","d","c","b","a","abcde"]</c>
#### Output
<c>140</c>
### Example 4
#### Input
<c>[100],<br />["oyusop"]</c>
#### Output
<c>100</c>
### Example 5
#### Input
<c>[100,100,100,100,100,100,100,100,100,100,100,100,100],<br />["haruka","chihaya","yayoi","iori","yukiho","makoto","ami","mami","azusa","miki","hibiki","takane","ritsuko"]</c>
#### Output
<c>1300</c>

