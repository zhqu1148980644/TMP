---
title: Partition Equal Subset Su
date: 2021-01-04
---
Given a non-empty array nums containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100


#### Solutions

1. ##### dynamic programming O(n * sum)

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((sum % 2) != 0) return false;

        vector<bool> dp(sum / 2 + 1);
        dp[0] = true;
        for (auto n : nums) {
            for (int s = sum / 2; s >= 0; s--) {
                if (dp[s] && s + n <= sum / 2)
                    dp[s + n] = true;
            }
        }

        return dp[sum / 2];
    }
};
```

or use bitset

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((sum % 2) != 0) return false;
        // Note that, the index 0 is the rightmost bit
        bitset<10001> dp {1};

        for (auto n : nums)
            dp |= dp << n;
        
        return dp[sum >> 1];
    }
};
```