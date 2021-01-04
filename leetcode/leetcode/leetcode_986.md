---
title: Interval List Intersections
date: 2021-01-04
---
Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.

Return the intersection of these two interval lists.

(Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.  The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.  For example, the intersection of [1, 3] and [2, 4] is [2, 3].)

 

Example 1:



Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 

Note:

0 <= A.length < 1000
0 <= B.length < 1000
0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9

#### Solutions

1. ##### megre and sort O((m + n)log(m + n))

```cpp
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        if (!A.size() || !B.size()) return {};
        A.insert(A.end(), B.begin(), B.end());
        sort(A.begin(), A.end());

        int prevst = A[0][0], preved = A[0][1];
        vector<vector<int>> res;
        for (int i = 1; i < A.size(); i++) {
            auto st = A[i][0], ed = A[i][1];
            if (st >= prevst && ed <= preved)
                res.push_back({st, ed});
            else {
                if (st <= preved)
                    res.push_back({st, preved});
                prevst = st;
                preved = ed;
            }
        }
        return res;
    }
};
```

2. ##### two pointers O(m + n)

```cpp
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        if (!A.size() || !B.size()) return {};

        int i = 0, j = 0;
        vector<vector<int>> res;
        while (i < A.size() && j < B.size()) {
            int lo = max(A[i][0], B[j][0]);
            int hi = min(A[i][1], B[j][1]);
            if (lo <= hi)
                res.push_back({lo, hi});
            if (A[i][1] <= B[j][1])
                i++;
            else
                j++;
        }
        return res;
    }
};
```