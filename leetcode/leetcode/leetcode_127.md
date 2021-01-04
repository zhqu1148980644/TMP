---
title: Word Ladder
date: 2021-01-04
---
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list.
Note:

Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

#### Solutions

1. ##### bfs

- build graph connects all string pairs can be converted into each other in one change, then use bfs search for the minimum traversal steps.

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        auto it = find(wordList.begin(), wordList.end(), endWord);
        if (it == wordList.end()) return 0;
        int target = it - wordList.begin();

        wordList.push_back(beginWord);
        int n = wordList.size(), wlen = beginWord.size();
        // build graph
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int diff = 0;
                for (int k = 0; k < wlen; k++)
                    if (wordList[i][k] != wordList[j][k] && ++diff > 1)
                        break;
                if (diff == 1) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        queue<int> q; q.push(n - 1);
        vector<bool> visited(n);
        visited[n - 1] = true;
        // bfs search
        int step = 1;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                int cur = q.front(); q.pop();
                for (auto out : g[cur]) {
                    if (visited[out]) continue;
                    if (out == target) return step + 1;
                    visited[out] = true;
                    q.push(out);
                }
            }
            step++;
        }

        return 0; 
    }
};
```

or find neighbors in lazy mode(from the official answer).

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string_view> words(wordList.begin(), wordList.end());
        if (!words.count(endWord)) return 0;

        unordered_set<string_view> visited;
        visited.insert(beginWord);
        queue<string_view> q;
        q.push(beginWord);
        
        int step = 1;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto cur = string(q.front()); q.pop();
                // check all possible neighbors, wlen * 26
                for (auto & c : cur) {
                    char back = c;
                    for (char nc = 'a'; nc <= 'z'; nc++) {
                        if (nc == back) continue;
                        c = nc;
                        if (words.count(cur) && !visited.count(cur)) {
                            if (cur == endWord) return step + 1;
                            auto news = *words.find(cur);
                            visited.insert(news);
                            q.push(news);
                        }
                    }
                    c = back;
                }
            }
            step++;
        }

        return 0;
    }
};
```

2. ##### Bidirectional bfs

- Whenever the searching space of one ends intersect with the other ends', return the sum steps(level) in two directions as the result.
- Directly uses hashset as queue and both two bfs searching directions share a common visited hashset(actually this hashset can be ommited by removing words from word dict).

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        using Set = unordered_set<string_view>;
        Set words(wordList.begin(), wordList.end());
        if (!words.count(endWord)) return 0;
        words.erase(beginWord); words.erase(endWord);

        Set q1 = {beginWord}, q2 = {endWord}, nextlevel;

        int res = 2;
        while (q1.size() && q2.size()) {
            for (auto & sv : q1) {
                auto cur = string(sv);
                for (auto & c : cur) {
                    char back = c;
                    for (char nc = 'a'; nc <= 'z'; nc++) {
                        if (nc == back) continue; c = nc;
                        if (q2.count(cur))  return res;
                        if (words.count(cur)) {
                            auto newsv = *words.find(cur);
                            // remove from word dict, equals to insert into a visited hashset.
                            words.erase(newsv);
                            nextlevel.insert(newsv);
                        }
                    }
                    c = back;
                }
            }
            res++;
            q1.clear(); swap(q1, nextlevel);
            if (q2.size() < q1.size())
                swap(q1, q2);
        }

        return 0;
    }
};
```