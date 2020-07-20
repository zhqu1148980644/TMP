#### There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

```
Example 1:

Input:
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

Output: "wertf"

Example 2:

Input:
[
  "z",
  "x"
]

Output: "zx"

Example 3:

Input:
[
  "z",
  "x",
  "z"
] 

Output: "" 

Explanation: The order is invalid, so return "".
```

#### Note:

-    You may assume all letters are in lowercase.
-    You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
-    If the order is invalid, return an empty string.
-    There may be multiple valid order of letters, return any one of them is fine.

#### Solutions

1. ##### topological ordering

- Similar to problem 210, we can thought of the order of characters as a dependency tree.
- The order of each pair of characters can be fetched by finding the first unequal character pair in two lexicographically sorted words.

```c++
class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<char> allchars(26, 0);
        vector<char> indeg(26, 0);
        vector<vector<char>> graph(26, vector<char>(26, 0));
        int dictsize = 0;
        for (auto & word : words)
            for (auto & c : word) {
                if (!allchars[c - 'a']) {
                    dictsize++;
                    allchars[c - 'a'] = 1;
                }
            }
        // build graph and record each node's number of indegree
        for (int i = 0; i < words.size(); i++) {
            if (i + 1 >= words.size()) break;
            int j, minlen = min(words[i].size(), words[i + 1].size());
            for (j = 0; j < minlen; j++) {
                char src = words[i][j] - 'a';
                char tgt = words[i + 1][j] - 'a';
                // Caution: these two `if` can not be merged into one expression
                if (src != tgt) {
                    if (!graph[src][tgt]) {
                        graph[src][tgt] = 1;
                        indeg[tgt]++;
                    }
                    break;
                }
            }
            // for case when ["abc", "ab"], fk this alien
            if (j == minlen && words[i].size() > words[i + 1].size())
                return false;
        }

        string path;
        queue<char> q;
        for (int i = 0; i < 26; i++)
            if (allchars[i] && indeg[i] == 0)
                    q.push(i);

        // iteratively remove nodes with zero indegrees
        while (!q.empty()) {
            char cur = q.front(); q.pop();
            path.push_back(cur + 'a');
            for (int out = 0; out < 26; out++)
                if (graph[cur][out] && --indeg[out] == 0)
                    q.push(out);
        }
        // Check whether the topological sorting sequence is complete.
        return path.size() == dictsize ? path : "";
    }
};
```