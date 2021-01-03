#### You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

```
Example 1:

Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
             because they are adjacent houses.

Example 2:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
```

#### Solutions

1. ##### dynamic programming


```cpp
class Solution {
public:     
    int rob(vector<int> & nums, int start, int len) {
        if (len == 1) return nums[start];
        int dp[len];
        dp[0] = nums[start];
        dp[1] = nums[start + 1];
        for (int i = 2; i < len; i++) {
            int tmp = i - 3 >= 0 ? dp[i - 3] : 0;
            dp[i] = max(dp[i - 2], tmp) + nums[start + i];
        }

        return max(dp[len - 1], dp[len - 2]);
    }

    int rob(vector<int>& nums) {
        if (!nums.size())
            return 0;
        else if (nums.size() == 1)
            return nums[0];
        else
            return max(
                rob(nums, 0, nums.size() - 1), 
                rob(nums, 1, nums.size() - 1)
            );
    }
};
```