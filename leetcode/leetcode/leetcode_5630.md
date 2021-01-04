---
title: Maximum Erasure Value
date: 2021-01-04
---
You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.

Return the maximum score you can get by erasing exactly one subarray.

An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

 

Example 1:

Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].
Example 2:

Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104


#### Solutions

1. ##### sliding window O(n)

```cpp
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int i = 0, j = 0, psum = 0, res = 0;
        vector<int> count(1e4 + 1);
        while (j < nums.size()) {
            psum += nums[j];
            if (++count[nums[j++]] > 1) {
                while (--count[nums[i]] != 1)
                    psum -= nums[i++];
                psum -= nums[i++];
            }
            res = max(res, psum);
        }
        return res;
    }
};
```