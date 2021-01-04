---
title: Shortest Word Distance II
date: 2021-01-04
---
#### Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list. Your method will be called repeatedly many times with different parameters. 

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

1. ##### hash map

- reference: official answer
- We use a hash map to record the indexes of each word in words vector.
- As the indexes are ordered, for a certain pair of indexes of two given words:
    - if `index1 < index2` moving the index2 forward will not gain a shorter distance, so we need to move `index1` forward.
    - The scanning ends when one of two pointers reaches the end.

```cpp
class WordDistance {
private:
    unordered_map<string, vector<int>> records;
public:
    WordDistance(vector<string>& words) {
        for (int i = 0; i < words.size(); i++)
            records[words[i]].push_back(i);
    }

    int shortest(string word1, string word2) {
        vector<int> & v1 = records[word1];
        vector<int> & v2 = records[word2];
        int i = 0, j = 0, mindiff = INT_MAX;
        while (i < v1.size() && j < v2.size()) {
            mindiff = min(mindiff, abs(v1[i] - v2[j]));
            if (v1[i] < v2[j])
                i++;
            else
                j++;
        }
        return mindiff;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(words);
 * int param_1 = obj->shortest(word1,word2);
 */
```