---
title: Satisfiability of Equality Equations
date: 2021-01-04
---
Given an array equations of strings that represent relationships between variables, each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.

 

Example 1:

Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.
Example 2:

Input: ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
Example 3:

Input: ["a==b","b==c","a==c"]
Output: true
Example 4:

Input: ["a==b","b!=c","c==a"]
Output: false
Example 5:

Input: ["c==c","b==d","x!=z"]
Output: true
 

Note:

1 <= equations.length <= 500
equations[i].length == 4
equations[i][0] and equations[i][3] are lowercase letters
equations[i][1] is either '=' or '!'
equations[i][2] is '='

#### Solutions

1. ##### UnionFind

- Iterating over all equations the first time to connect equal chracters, then iterate over again and check if two characters with unequal mark are within the same community.

```cpp
struct UnionFind {
    vector<int> nodes;
    UnionFind(int size) : nodes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        return nodes[node] == node ? node : (nodes[node] = find(nodes[node]));
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf(126);

        for (auto & s : equations)
            if (s[1] == '=')
                uf.merge(s[0], s[3]);

        for (auto & s : equations)
            if (s[1] == '!' && uf.find(s[0]) == uf.find(s[3]))
                return false;

        return true;
    }
};
```

2. ##### graph