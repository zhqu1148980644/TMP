---
title: Find All Numbers Disappeared in an Array
date: 2021-01-04
---
#### Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

```
Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]
```

#### Solutions


1. ##### in-place hashmap

- Use in-place hashmap, set appeared numbers with negative flag.

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (auto num : nums) {
            num = num < 0 ? -num : num;
            if (nums[num - 1] > 0)
                nums[num - 1] *= -1;
        }
        vector<int> res;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] > 0)
                res.push_back(i + 1);
            else
                nums[i] *= -1;
        return res;
    }
};
```

2. ##### Pigeonhole principle 

- Similar to problem 41/442.

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
        }
        vector<int> res;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != i + 1)
                res.push_back(i + 1);
        return res;
    }
};
```