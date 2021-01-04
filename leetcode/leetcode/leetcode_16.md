---
title: 3Sum Closest
date: 2021-01-04
---
### Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

### Example:

```
Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```


### Solutions

1. #### The same method in problem `15-3Sum` O(nlog(n) + n2)

```cpp
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int i = 0;
        int closest = nums[0] + nums[1] + nums[2];
        while (i < nums.size() - 1) {
            int a = nums[i];
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                int b = nums[j], c = nums[k], sum = a + b + c;
                if (sum < target) while (j < k && nums[j] == b) j++;
                else if (sum > target) while (j < k && nums[k] == c) k--;
                else return target;
                // Changes compared to 15.
                if (abs(sum - target) < abs(closest - target))
                    closest = sum;
            }
            while (nums[i] == a && i < nums.size() - 1) i++;
        }
        return closest;
    }
};
```
