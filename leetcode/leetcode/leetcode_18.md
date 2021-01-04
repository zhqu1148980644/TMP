---
title: 4Su
date: 2021-01-04
---
Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]


#### Solutions

1. ##### two pointers O(n3)

- Except the outer most for-loop, the logic is the same as in `problem 15 3 sum`

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < n; i++) {
            int a = nums[i];
            for (int j = i + 1; j < n; j++) {
                int b = nums[j], k = j + 1, l = n - 1;
                while (k < l) {
                    int c = nums[k], d = nums[l];
                    int sum = a + b + c + d;
                    if (sum <= target) while (k < l && nums[k] == c) k++;
                    if (sum >= target) while (k < l && nums[l] == d) l--;
                    if (sum == target)
                        res.push_back({a, b, c, d});
                    
                }
                while (j + 1 < n && nums[j + 1] == b) j++;
            }
            while (i + 1 < n && nums[i + 1] == a) i++;
        }

        return res;
    }
};
```