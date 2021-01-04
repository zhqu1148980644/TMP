---
title: Two Sum
date: 2021-01-04
---
### Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

### Example

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```


### Solutions

1. #### Brute force O(n2)

```python
class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        for i, n in enumerate(nums):
            for j, can in enumerate(nums[i + 1:]):
                if n + can == target:
                    return i, i + j + 1
```

2. #### Hashmap O(n) S(n)

Time: O(n)
Space: O(n)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (m.count(target - nums[i]))
                return {m[target - nums[i]], i};
            else
                m[nums[i]] = i;
        }
        return {0, 0};
    }
};
```
