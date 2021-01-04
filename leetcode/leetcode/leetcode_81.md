---
title: Search in Rotated Sorted Array II
date: 2021-01-04
---
#### Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).

You are given a target value to search. If found in the array return true, otherwise return false.

```
Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
```

#### Follow up:

-    This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
-    Would this affect the run-time complexity? How and why?


#### Solutions

1. ##### Solutions

- See `problem 33`
- The time complexity is O(n) in worst case.
    - 1111111123400001111. When mid is `nums[mid] == num[hi] == 1`, it's unable to know if mid within the let part or the right part.


or

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (!nums.size()) return false;
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (nums[mid] == target)
                return true;
            if (nums[mid] > nums[hi - 1]) {
                if (target >= nums[mid] || target <= nums[hi - 1])
                    lo = mid + 1;
                else
                    hi = mid;
            }
            else if (nums[mid] < nums[hi - 1]) {
                if (target >= nums[mid] && target <= nums[hi - 1])
                    lo = mid + 1;
                else
                    hi = mid;
            }
            else
                hi--;
        }
        return false;
    }
};
```

Or

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (!nums.size()) return false;
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (nums[mid] == target)
                return true;
            if (nums[mid] > nums[hi]) {
                if (target >= nums[mid] || target <= nums[hi])
                    lo = mid + 1;
                else
                    hi = mid;
            } else if (nums[mid] < nums[hi]) {
                if (target >= nums[mid] && target <= nums[hi])
                    lo = mid + 1;
                else
                    hi = mid;
            } else
                // here comes the difference
                // shrink right bound if middle equals to right bound
                hi--;
        }
        return false;
    }
};
```