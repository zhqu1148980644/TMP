---
title: Flower Planting With No Adjacent
date: 2021-01-04
---
You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.

paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.

Also, there is no garden that has more than 3 paths coming into or leaving it.

Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.

Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.  It is guaranteed an answer exists.

 

Example 1:

Input: N = 3, paths = [[1,2],[2,3],[3,1]]
Output: [1,2,3]
Example 2:

Input: N = 4, paths = [[1,2],[3,4]]
Output: [1,2,1,2]
Example 3:

Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
Output: [1,2,3,4]
 

Note:

1 <= N <= 10000
0 <= paths.size <= 20000
No garden has 4 or more paths coming into or leaving it.
It is guaranteed an answer exists.

#### Solutions

1. ##### greedy

- The coloring process must(node more than 3 neighbors) can be done by iteratively coloring adjacent nodes without violating the requirements.

```cpp
class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        unordered_map<int, vector<int>> g;
        for (auto & e : paths) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> colors(N);
        for (int cur = 1; cur <= N; cur++) {
            vector<bool> used = {true, false, false, false, false};
            for (auto out : g[cur])
                used[colors[out - 1]] = true;
            for (int c = 1; c <= 4; c++)
                if (!used[c]) {
                    colors[cur - 1] = c;
                    break;
                }
        }

        return colors;
    }
};
```