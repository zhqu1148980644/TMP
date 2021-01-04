---
title: Shortest Distance to Target Color
date: 2021-01-04
---

You are given an array colors, in which there are three colors: 1, 2 and 3.

You are also given some queries. Each query consists of two integers i and c, return the shortest distance between the given index i and the target color c. If there is no solution return -1.

 

Example 1:

Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
Output: [3,0,3]
Explanation: 
The nearest 3 from index 1 is at index 4 (3 steps away).
The nearest 2 from index 2 is at index 2 itself (0 steps away).
The nearest 1 from index 6 is at index 3 (3 steps away).
Example 2:

Input: colors = [1,2], queries = [[0,3]]
Output: [-1]
Explanation: There is no 3 in the array.
 

Constraints:

1 <= colors.length <= 5*10^4
1 <= colors[i] <= 3
1 <= queries.length <= 5*10^4
queries[i].length == 2
0 <= queries[i][0] < colors.length
1 <= queries[i][1] <= 3

#### Solutions

1. ##### hash map O(2n)

```cpp
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        unordered_map<int, vector<pair<int, int>>> qs;
        for (int i = 0; i < queries.size(); i++) {
            auto & q = queries[i];
            qs[q[0]].emplace_back(q[1], i);
        }
        vector<int> res(queries.size());
        // search for the left nearest
        vector<int> pos(4, -1);
        for (int i = 0; i < colors.size(); i++) {
            auto c = colors[i]; pos[c] = i;
            if (!qs.count(i)) continue;
            for (auto [target, qi] : qs[i])
                res[qi] = pos[target] == -1 ? INT_MAX : i - pos[target];
        }
        // search for the right nearest
        pos = vector<int>(4, -1);
        for (int i = colors.size() - 1; i >= 0; i--) {
            auto c = colors[i]; pos[c] = i;
            if (!qs.count(i)) continue;
            for (auto [target, qi] : qs[i]) {
                res[qi] = min(res[qi], pos[target] == -1 ? INT_MAX : pos[target] - i);
                if (res[qi] == INT_MAX)
                    res[qi] = -1;
            }
        }

        return res;
    }
};
```

2. ##### binary  O(n + len(q)log(n))

```cpp
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<vector<int>> m(4);
        for (int i = 0; i < colors.size(); i++)
            m[colors[i]].push_back(i);
        
        vector<int> res(queries.size(), -1);
        int w = 0;
        for (auto & q : queries) {
            auto & index = m[q[1]];
            if(colors[q[0]] == q[1])
                res[w++] = 0;
            else {
                auto find = lower_bound(index.begin(), index.end(), q[0]);
                int left = find == index.begin() ? -100000 : *prev(find);
                int right = find == index.end() ? 100000 : *find;
                res[w] = min(q[0] - left, right - q[0]);
                if (res[w] > colors.size()) res[w] = -1;
                w++;
            }
        }

        return res;
    }
};
```