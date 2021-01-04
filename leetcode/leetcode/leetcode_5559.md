---
title: Minimum Number of Removals to Make Mountain Array
date: 2021-01-04
---
You may recall that an array arr is a mountain array if and only if:

arr.length >= 3
There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.

 

Example 1:

Input: nums = [1,3,1]
Output: 0
Explanation: The array itself is a mountain array so we do not need to remove any elements.
Example 2:

Input: nums = [2,1,1,5,6,2,3,1]
Output: 3
Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].
Example 3:

Input: nums = [4,3,2,1,1,2,3,1]
Output: 4
Example 4:

Input: nums = [1,2,3,4,4,3,2,1]
Output: 1
 

Constraints:

3 <= nums.length <= 1000
1 <= nums[i] <= 109
It is guaranteed that you can make a mountain array out of nums.


#### Solutions

- Check for all possible peaks, the number of elements needs to be removed equals to total length deduce the sum length of two increasing/decreasing subsequences around the peak.
- Find the longest increasing/decreasing subsequences will be solved in `leetcode problem 300`

1. ##### dynamic programming O(n2)

```cpp
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size(), res = INT_MAX;

        vector<int> inc(nums.size()), dec(inc);
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] > nums[j])
                    inc[i] = max(inc[i], inc[j] + 1);
            }
        }
        
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] > nums[j])
                    dec[i] = max(dec[i], dec[j] + 1);
            }
            if (inc[i] && dec[i])
                res = min(res, n - inc[i] - dec[i] - 1);
        }
        
        return res;
        
    }
};

```

2. ##### binary search

- Check problem 300.