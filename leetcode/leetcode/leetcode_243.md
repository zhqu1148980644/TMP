---
title: Shortest Word Distance
date: 2021-01-04
---
#### Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

```
Example:
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Input: word1 = “coding”, word2 = “practice”
Output: 3

Input: word1 = "makes", word2 = "coding"
Output: 1
```

#### Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int mins = INT_MAX;
        int i1 = -1, i2 = -1;
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1)
                i1 = i;
            else if (words[i] == word2)
                i2 = i;
            if (i1 != -1 && i2 != -1)
                mins = min(mins, abs(i1 - i2));
        }
        return mins;
    }
};
```