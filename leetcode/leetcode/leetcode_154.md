---
title: Find Minimum in Rotated Sorted Array II
date: 2021-01-04
---
#### Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

The array may contain duplicates.

```
Example 1:

Input: [1,3,5]
Output: 1
Example 2:

Input: [2,2,2,0,1]
Output: 0
```

#### Note:

This is a follow up problem to Find Minimum in Rotated Sorted Array.
Would allow duplicates affect the run-time complexity? How and why?


#### Solutions

1. ##### binary search

- reference: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/discuss/48883/C%2B%2B-binary-%2B-linear-search
- There is no way to choose the right moving direction in O(1).
- For example: `01111` can be rotated to `10111` and `11101`.
- In these two cases, both `left` `mid` `right` equals to `1`, thus a linear search is nesserary.

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1, len = nums.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (nums[mid] < nums[hi])
                hi = mid;
            else if (nums[mid] > nums[hi])
                lo = mid + 1;
            else
                hi--;
        }
        return nums[lo];
    }
};
```