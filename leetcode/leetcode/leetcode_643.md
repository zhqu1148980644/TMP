---
title: Maximum Average Subarray I
date: 2021-01-04
---
Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

Example 1:

Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
 

Note:

1 <= k <= n <= 30,000.
Elements of the given array will be in the range [-10,000, 10,000].
 

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double sum = accumulate(nums.begin(), nums.begin() + k, 0);
        double res = sum / k;
        for (int i = k; i < nums.size(); i++) {
            sum += nums[i] - nums[i - k];
            if (sum / k > res)
                res = sum / k;
        }

        return res;
    }
};
```