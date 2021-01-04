---
title: Longest Harmonious Subsequence
date: 2021-01-04
---
We define a harmounious array as an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:

Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
 

Note: The length of the input array will not exceed 20,000.

#### Solutions

1. ##### hash map

- numbers in the final subsequence must be two consecutive numbers `(a, a+1)`

```cpp
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> m;
        for (auto n : nums) m[n]++;

        int res = 0;
        for (auto [n, c] : m)
            if (m.count(n - 1))
                res = max(res, c + m[n - 1]);

        return res;
    }
};
```

or update the result during the counting process

```cpp
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> m;
        int res = 0;
        for (auto n : nums) {
            m[n]++;
            if (m.count(n - 1))
                res = max(res, m[n] + m[n - 1]);
            if (m.count(n + 1))
                res = max(res, m[n] + m[n + 1]);
        }

        return res;
    }
};
```