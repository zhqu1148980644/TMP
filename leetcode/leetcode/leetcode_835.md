---
title: Image Overlap
date: 2021-01-04
---
Two images A and B are given, represented as binary, square matrices of the same size.  (A binary matrix has only 0s and 1s as values.)

We translate one image however we choose (sliding it left, right, up, or down any number of units), and place it on top of the other image.  After, the overlap of this translation is the number of positions that have a 1 in both images.

(Note also that a translation does not include any kind of rotation.)

What is the largest possible overlap?

Example 1:

Input: A = [[1,1,0],
            [0,1,0],
            [0,1,0]]
       B = [[0,0,0],
            [0,1,1],
            [0,0,1]]
Output: 3
Explanation: We slide A to right by 1 unit and down by 1 unit.
Notes: 

1 <= A.length = A[0].length = B.length = B[0].length <= 30
0 <= A[i][j], B[i][j] <= 1

#### Solutions

1. ##### brute force O(n4)

- Check all combinations of overlapping, use hash map to record the delta with the maximum count.

```cpp
class Solution {
public:
    struct hash {
        size_t operator()(const pair<int, int> & p) const {
            return p.first * 100 + p.second;
        }
    };
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        if (!A.size() || !B.size()) return 0;
        unordered_set<pair<int, int>, hash> points;
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < A[0].size(); j++)
                if (A[i][j]) points.insert({i, j});
        
        unordered_map<pair<int, int>, int, hash> delta;
        for (int i = 0; i < B.size(); i++)
            for (int j = 0; j < B[0].size(); j++) {
                if (!B[i][j]) continue;
                for (auto & p : points)
                    delta[{p.first - i, p.second - j}]++;
            }
        int res = 0;
        for (auto & [p, cnt] : delta)
            res = max(res, cnt);
        
        return res;
    }
};
```