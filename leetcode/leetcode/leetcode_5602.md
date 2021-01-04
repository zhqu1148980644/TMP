---
title: Minimum Operations to Reduce X to Zero
date: 2021-01-04
---
You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost or the rightmost element from the array nums and subtract its value from x. Note that this modifies the array for future operations.

Return the minimum number of operations to reduce x to exactly 0 if it's possible, otherwise, return -1.

 

Example 1:

Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
Example 2:

Input: nums = [5,6,7,8,9], x = 4
Output: -1
Example 3:

Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104
1 <= x <= 109

#### Solutions

1. ##### prefix sum with hashmap

- As the ordering of numbers at both ends does not matter. The problem equals to find the shortest `head + tail` with sum equal to the target `x`.
- Denotes the sum of the whole array as `S`, the problem equals to find the longest contiguous subarray with sum equals to `S - x`.


```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        if (x == 0) return 0;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int exp = sum - x;
        if (exp < 0) return -1;
        unordered_map<int, int> m;
        m[0] = -1;
        
        int res = INT_MAX; sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            // record the first appearance of a certain prefix sum
            if (!m.count(sum))
                m[sum] = i;
            // record the longest subarray
            if (m.count(sum - exp))
                res = min(res, (int)nums.size() - (i - m[sum - exp]));
        }
        
        return res == INT_MAX ? -1 : res;
    }
};
```