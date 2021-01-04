---
title: House Robber
date: 2021-01-04
---
#### You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

```
Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
```

#### Solutions

1. ##### dynamic programming O(n) O(n)/ O(1)

- Support we choose to rob `n[i]` at some point, what's the larget amount of money we can achieve.
- Obviuosly this question depends on where we robbed last time and the amount of money we achieved in the last step.
    - It can be enssured that it's not `n[i - 1]` cause robbing two cotiguous house is forbidden.
    - It can be `n[i - 2]`.
    - It can be `n[i - 3]`.
    - It can not be `n[i - 4]` or any location before this point, if the last robbing point is `n[i - 4]`, it's clear that rob `n[i - 2]` then rob `n[i]` can achieve a higher amount of money and this contradict with the truth that we are searching for the last robbing point.
- So it's a dynamic programming problem, The answer of `n[i]` depends only on `n[i - 2]` and `n[i - 3]`.

```cpp
#define max(x, y) ( x > y ? x : y)

int rob(int* nums, int numsSize){
    if (numsSize <= 1) return numsSize == 1 ? nums[0] : 0;
    int dp[numsSize];
    dp[0] = nums[0];
    dp[1] = nums[1];
    int max_num = max(dp[0], dp[1]);
    for (int i = 2; i < numsSize; i++) {
        int tmp = (i - 3 < 0) ? 0 : dp[i - 3];
        dp[i] = max(dp[i - 2], tmp) + nums[i];
        max_num = max(max_num, dp[i]);
    }
    return max_num;
}
```

As only three values need to be reordered, we can remove the redundant dp table.

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size() ? nums[0] : 0;
        vector<int> dp(nums.size());
        int ppp, pp, p, res; ppp = pp = p = res = 0;
        for (auto n : nums) {
            int cur = max(pp, ppp) + n;
            ppp = pp, pp = p;
            p = cur;
            res = max(cur, res);
        }
        return res;
    }
};
```

```python
# p mean previous, pp means previous of pevious ....
class Solution:
    def rob(self, nums: List[int]) -> int:
        ppp = pp = p = 0
        max_num = 0
        for num in nums:
            ppp, pp, p = pp, p, max(ppp, pp) + num
            max_num = max(max_num, p)

        return max_num
```

We can also use a recursive way(time consuming) similar to calculating fibbonacci sequence(top to bottom).

