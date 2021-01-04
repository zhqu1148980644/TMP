---
title: Jump Game VI
date: 2021-01-04
---
You are given a 0-indexed integer array nums and an integer k.

You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.

You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.

Return the maximum score you can get.

 

Example 1:

Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
Example 2:

Input: nums = [10,-5,-2,4,0,3], k = 3
Output: 17
Explanation: You can choose your jumps forming the subsequence [10,4,3] (underlined above). The sum is 17.
Example 3:

Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
Output: 0
 

Constraints:

 1 <= nums.length, k <= 105
-104 <= nums[i] <= 104


#### Solutions

1. ##### dynamic programming O(n2)

- Gets TLE.

```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, INT_MIN / 2);
        dp[0] = 0;
        for (int j = 1; j < n; j++) {
            for (int i = max(0, j - k); i < j; i++)
                dp[j] = max(dp[j], dp[i] + nums[i]);
        }

        return dp[n - 1] + nums[n - 1];
    }
};
```

2. ##### mono queue

- reference: https://leetcode-cn.com/problems/jump-game-vi/solution/tiao-yue-you-xi-vi-by-zerotrac2-r1kq/
- The idea is that when `dp[i] <= dp[j] with i < j`, `dp[j]` is always preferred as the previous state(previous jump point).
- To preferencially store the nearest state, we maintain a monotonically decreasing queue.

```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        deque<pair<int, int>> mq = {{nums[0], 0}};
        
        int n = 0, score = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            while (mq.size() && mq.front().second < i - k)
                mq.pop_front();
            score = mq.front().first + nums[i];
            if (score >= mq.front().first)
                mq.clear();
            else {
                while (mq.back().first <= score)
                    mq.pop_back();
            }
            mq.emplace_back(score, i);
        }
        return score;
    }
};
```