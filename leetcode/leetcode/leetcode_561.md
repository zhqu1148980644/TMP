---
title: Array Partition I
date: 2021-01-04
---
Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].

#### Solutions

1. ##### sort O(nlog(n))

- for sorted array: `n1, n2, n3, n4, n5, n6`, pairs will be `(n1, n2), (n3, n4), (n5, n6)`

```cpp
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i = 0; i < nums.size(); i += 2)
            res += nums[i];

        return res;
    }
};
```


2. ##### count sort O(n)

- The problem's note is `All the integers in the array will be in the range of [-10000, 10000].`

```cpp
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        vector<int> buckets(20001);
        for (auto n : nums)
            buckets[n + 10000]++;
        int w = 0;
        for (int i = -10000; i <= 10000; i++)
            while (buckets[i + 10000]-- > 0)
                nums[w++] = i;
        
        int res = 0;
        for (int i = 0; i < nums.size(); i += 2)
            res += nums[i];
        
        return res;
    }
};
```

- optimized version: check the official answer.