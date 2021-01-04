---
title: Ways to Split Array Into Three Subarrays
date: 2021-01-04
---
A split of an integer array is good if:

The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [1,1,1]
Output: 1
Explanation: The only good way to split nums is [1] [1] [1].
Example 2:

Input: nums = [1,2,2,2,5,0]
Output: 3
Explanation: There are three good ways of splitting nums:
[1] [2] [2,2,5,0]
[1] [2,2] [2,5,0]
[1,2] [2,2] [5,0]
Example 3:

Input: nums = [3,2,1]
Output: 0
Explanation: There is no good way to split nums.
 

Constraints:

3 <= nums.length <= 105
0 <= nums[i] <= 104


#### Solutions

1. ##### two pointers with binary search

- Iterate over the partition points between `left` and `mid`, `mid` and right.
- Then second partition point has a lower bound constrained by `mid >= left` and a upper bound constrained by `mid <= right`.
  - The lower bound and the upper bound can be found in `O(log(n))` time by using binary search because of the monotonicity of addition.

```cpp
class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        vector<double> psum(n + 1);
        for (int i = 0; i < n; i++) {
            psum[i + 1] += psum[i] + nums[i];
        }
        
        size_t res = 0;
        for (int i = 1; i < n; i++) {
            double lsum = psum[i];
            if (psum[n] - lsum < 2 * lsum) continue;
            auto lo = lower_bound(psum.begin() + i + 1, psum.end(), lsum + lsum);
            auto hi = upper_bound(psum.begin() + i + 1, psum.end(), lsum + (psum[n] - lsum) / 2);
            // special case when all numbers are zero
            if (psum[n] == 0)
                res += n - i - 1;
            // make sure each part is non-empty
            else if (hi > lo && hi != psum.end())
                res += hi - lo;
            res %= 1000000007;            
        }
        
        return res;
    }
};

```