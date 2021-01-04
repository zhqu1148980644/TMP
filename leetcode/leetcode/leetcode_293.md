---
title: Flip Game
date: 2021-01-04
---
You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to compute all possible states of the string after one valid move.

Example:

Input: s = "++++"
Output: 
[
  "--++",
  "+--+",
  "++--"
]


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> res; int end = (int)s.size() - 1;
        for (int i = 0; i < end; i++)
            if (s[i] == '+' && s[i + 1] == '+') {
                string tmp(s);
                tmp[i] = '-'; tmp[i + 1] = '-';
                res.push_back(move(tmp));
            }

        return res;
    }
};
```