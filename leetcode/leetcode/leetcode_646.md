---
title: Maximum Length of Pair Chain
date: 2021-01-04
---
You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]
Note:
The number of given pairs will be in the range [1, 1000].

#### Solutions

- This problem is the same as `problem 435/452` internally. ie: Find the maximum number of non-overlapping intervals

1. ##### greedy strategy sort by end

```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if (!pairs.size()) return 0;
        sort(pairs.begin(), pairs.end(), [](auto & p1, auto & p2) {
            return p1[1] < p2[1];
        });

        int count = 1, prevend = pairs[0][1];
        for (int i = 1; i < pairs.size(); i++)
            if (pairs[i][0] > prevend) {
                count++;
                prevend = pairs[i][1];
            }

        return count;
    }
};
```


or sort by start

```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if (!pairs.size()) return 0;
        sort(pairs.begin(), pairs.end());

        int count = 1, prevend = pairs[0][1];
        for (int i = 1; i < pairs.size(); i++)
            if (pairs[i][0] > prevend) {
                count++;
                prevend = pairs[i][1];
            }
            else if (pairs[i][1] < prevend)
                prevend = pairs[i][1];

        return count;
    }
};
```

2. ##### dynamic programming


3. ##### dynamic programming with binary search

- Similar to `problem 300 Longest increasing subsequence`

```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end());
        vector<vector<int>> dp;

        for (auto & v : pairs) {
            if (!dp.size() || v[0] > dp.back()[1]) {
                dp.push_back(v);
                continue;
            }
            // search the firster end greater then the current's start
            int lo = 0, hi = dp.size() - 1;
            while (lo < hi) {
                int mid = lo + ((hi - lo) / 2);
                // use upper bound.
                if (v[0] >= dp[mid][1])
                    lo = mid + 1;
                else
                    hi = mid;
            }
            // replace it if it's end is larger than the current one
            if (dp[lo][1] > v[1])
                dp[lo] = v;
        }

        return dp.size();
    }
};
```