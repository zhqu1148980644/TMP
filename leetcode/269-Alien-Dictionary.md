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
        vector<char> seen(26), indeg(26);
        vector<vector<char>> graph(26, vector<char>(26));
        int dictsize = 0;
        for (auto & w : words)
            for (auto c : w)
                if (!seen[c - 'a']) {
                    dictsize++;
                    seen[c - 'a'] = 1;
                }
        // build graph and record each node's number of indegre
        int n = words.size();
        for (int i = 0; i < n - 1; i++) {
            int j, minlen = min(words[i].size(), words[i + 1].size());
            for (j = 0; j < minlen; j++) {
                char src = words[i][j] - 'a';
                char tgt = words[i + 1][j] - 'a';
                if (src != tgt) {
                    if (graph[tgt][src]) return "";
                    if (!graph[src][tgt]) {
                        graph[src][tgt] = 1;
                        indeg[tgt]++;
                    }
                    break;
                }
            }
            // for case when ["abc", "ab"], fk this alie
            if (j == minlen && words[i].size() > j) return "";
        }

        string path;
        queue<char> q;
        for (int c = 0; c < 26; c++)
            if (seen[c] && indeg[c] == 0)
                q.push(c);
        // iteratively remove nodes with zero indegrees
        while (q.size()) {
            char cur = q.front(); q.pop();
            path += cur + 'a';
            for (int out = 0; out < 26; out++) {
                if (graph[cur][out] && --indeg[out] == 0)
                    q.push(out);
            }
        }
        // Check whether the topological sorting sequence is complete.
        return path.size() == dictsize ? path : "";
    }
};
```