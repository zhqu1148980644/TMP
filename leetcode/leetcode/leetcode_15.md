---
title: 3Su
date: 2021-01-04
---
### Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

### Note:

The solution set must not contain duplicate triplets.

### Example:

```
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```


### Solutions

1. #### sort and two pointer O(log(n) + n2)

- Use sort to remove duplicate
- Use two pointer way to seach target

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    if (!nums.size() || nums[0] > 0 || nums[nums.size() - 1] < 0)
        return res;
    int i = 0, a;
    while (i < nums.size() - 2) {
        if ((a = nums[i]) > 0) return res;
        int j = i + 1, k = nums.size() - 1;
        while (j < k) {
            int b = nums[j], c = nums[k], sum = a + b + c;
            if (sum <= 0) while (j < k && nums[j] == b) j++;
            if (sum >= 0) while (j < k && nums[k] == c) k--;
            if (sum == 0) res.push_back(vector<int>{a, b, c});
        }
        while (nums[i] == a && i < nums.size() - 1) i++;
    }
    return res;
    }
};
```