---
title: Word Ladder II
date: 2021-01-04
---
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: []

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

#### Solutions

1. ##### bidirectional bfs

- Check `problem 127` first. bfs routines are basically the same.
- Compared to `problem 127`, appened words in each level can not be immediately added into the `visited` hash set to leave chance for other nodes in the current level to be connected with their `next` words.

```cpp
class Solution {
public:
    using Set = unordered_set<string_view>;
    using Graph = unordered_map<string_view, vector<string_view>>;
    vector<string_view> path;
    vector<vector<string>> res;
    // search in backtrack graph and build the path
    void dfs(Graph & g, const string_view & cur, int mindis) {
        if (path.size() == mindis) {
            // not need to check if the current string is target, it must be
            vector<string> fullpath(mindis);
            for (int i = mindis - 1; i >= 0; i--)
                fullpath[mindis - i - 1] = string(path[i]);
            res.push_back(move(fullpath));
        }
        else {
            for (auto & prev : g[cur]) {
                path.push_back(prev);
                dfs(g, prev, mindis);
                path.pop_back();
            }
        }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        Set words(wordList.begin(), wordList.end());
        if (!words.count(endWord)) return {};
        // both queue share a common visited set
        Set visited = {beginWord, endWord}, nextlevel;
        // two queues for two directions
        Set qst = {beginWord}, qed = {endWord};
        // backtracking graph with reverse link(ed -> st2 -> st1)
        Graph g;
        
        int stepst = 1, steped = 1, mindis = -1;
        while (qst.size() && qed.size()) {
            // expanding from the queue with the minimum size
            bool checkst = qst.size() <= qed.size();
            auto & q1 = checkst ? qst : qed;
            auto & q2 = checkst ? qed : qst;
            int & step = checkst ? stepst : steped;
            
            bool intersect = false;
            for (auto & src : q1) {
                auto cur = string(src);
                for (auto & c : cur) {
                    char back = c;
                    for (char nc = 'a'; nc <= 'z'; nc++) {
                        if (nc == back) continue; c = nc;
                        if (!words.count(cur)) continue;
                        bool curintersec = q2.count(cur);
                        if (curintersec) intersect = true;
                        // ensure strings do not connect back(loop)
                        // intersect with elements in another ends is not a loop.
                        if (curintersec || !visited.count(cur)) {
                            // get a nontemporary source
                            auto tgt = *words.find(cur);
                            // build bactrack graph
                            if (checkst)
                                g[tgt].push_back(src);
                            else
                                g[src].push_back(tgt);
                            // can not directly add into visited
                            // other wise some strings may not have changes to build graph
                            nextlevel.insert(tgt);
                        }
                    }
                    c = back;
                }
            }
            if (intersect) {
                mindis = stepst + steped; break;
            }
            // not it's time to update visited.
            visited.insert(nextlevel.begin(), nextlevel.end());
            q1.clear(); swap(q1, nextlevel);
            step++;
        }
        if (mindis == -1) return {};
        path.push_back(endWord);
        dfs(g, endWord, mindis);

        return res;
    }
};
```