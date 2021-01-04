---
title: Degree of an Array
date: 2021-01-04
---
Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.

#### Solutions

1. ##### sliding window

```cpp
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        if (!nums.size()) return 0;
        unordered_map<int, int> m;
        int maxc = INT_MIN;
        for (auto n : nums)
            maxc = max(maxc, ++m[n]);
        if (maxc == 1) return 1;    

        vector<int> vals;
        for (auto [n , c] : m)
            if (c == maxc) vals.push_back(n);

        unordered_map<int, int> count;
        int i = 0, j = 0, res = INT_MAX;
        while (j < nums.size())
            if (++count[nums[j++]] == maxc) {
                while (--count[nums[i++]] != maxc - 1);
                res = min(res, j - i + 1);
            }

        return res;   
    }
};
```

- The truth is that we only cares about the first/last indexes of numbers with the maximum frequency.

```cpp
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        if (!nums.size()) return 0; 

        unordered_map<int, int> m, start, end;
        int maxc = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];
            maxc = max(maxc, ++m[n]);
            if (!start.count(n))
                start[n] = i;
            end[n] = i;
        }
        int res = INT_MAX;
        for (auto [n, c] : m)
            if (c == maxc)
                res = min(res, end[n] - start[n] + 1);

        return res;
    }
};
``