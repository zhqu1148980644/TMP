---
title: Minimum Subsequence in Non Increasing Order
date: 2021-01-04
---
Given the array nums, obtain a subsequence of the array whose sum of elements is strictly greater than the sum of the non included elements in such subsequence. 

If there are multiple solutions, return the subsequence with minimum size and if there still exist multiple solutions, return the subsequence with the maximum total sum of all its elements. A subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. 

Note that the solution with the given constraints is guaranteed to be unique. Also return the answer sorted in non-increasing order.

 

```
Example 1:

Input: nums = [4,3,10,9,8]
Output: [10,9] 
Explanation: The subsequences [10,9] and [10,8] are minimal such that the sum of their elements is strictly greater than the sum of elements not included, however, the subsequence [10,9] has the maximum total sum of its elements. 
Example 2:

Input: nums = [4,4,7,6,7]
Output: [7,7,6] 
Explanation: The subsequence [7,7] has the sum of its elements equal to 14 which is not strictly greater than the sum of elements not included (14 = 4 + 4 + 6). Therefore, the subsequence [7,6,7] is the minimal satisfying the conditions. Note the subsequence has to returned in non-decreasing order.  
Example 3:

Input: nums = [6]
Output: [6]
```
 

Constraints:

1 <= nums.length <= 500
1 <= nums[i] <= 100


#### Solutions

1. ##### sort

- By adding items from the largest to smallest, the first matching subsequence is the best choice.

```cpp
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<>());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        vector<int> res;
        int cursum = 0;
        for (auto n : nums) {
            cursum += n;
            sum -= n;
            res.push_back(n);
            if (cursum > sum)
                return res;
        }

        return res;
    }
};
```

or

```cpp
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        vector<int> buckets(101), res;
        int sum = 0, cursum = 0;
        for (auto n : nums) {
            buckets[n]++; sum += n;
        }

        for (int n = 100; n > 0; n--)
            for (int i = 0; i < buckets[n]; i++) {
                cursum += n; sum -= n;
                res.push_back(n);
                if (cursum > sum)
                    return res;
            }

        return {};
    }
};
```