---
title: Delete and Earn
date: 2021-01-04
---
Given an array nums of integers, you can perform operations on the array.

In each operation, you pick any nums[i] and delete it to earn nums[i] points. After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.

You start with 0 points. Return the maximum number of points you can earn by applying such operations.

Example 1:

Input: nums = [3, 4, 2]
Output: 6
Explanation: 
Delete 4 to earn 4 points, consequently 3 is also deleted.
Then, delete 2 to earn 2 points. 6 total points are earned.
 

Example 2:

Input: nums = [2, 2, 3, 3, 3, 4]
Output: 9
Explanation: 
Delete 3 to earn 3 points, deleting both 2's and the 4.
Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
9 total points are earned.
 

Note:

The length of nums is at most 20000.
Each element nums[i] is an integer in the range [1, 10000].

#### Solutions

1. ##### dynamic programming

- Similar to `problem 198 House Robber`


```cpp
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.size() < 2) return nums.size() ? nums[0] : 0;
        auto [minv, maxv] = minmax_element(nums.begin(), nums.end());

        vector<int> sums(*maxv - *minv + 1);
        for (auto n : nums)
            sums[n - *minv] += n;
        
        int ppp, pp, p, res; ppp = pp = p = res = 0;
        for (auto n : sums) {
            int cur = max(ppp, pp) + n;
            ppp = pp; pp = p; p = cur;
            res = max(res, cur);
        }

        return res;
    }
};
```
or.
This version is slower than the previous version because naive sorting cause `O(nlog(n))` complexity while bucket sort takes `O(n)`.

```cpp
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (!nums.size()) return 0;
        unordered_map<int, int> m;
        for (auto n : nums) m[n]++;

        sort(nums.begin(), nums.end());
        int k = unique(nums.begin(), nums.end()) - nums.begin();
        int use, nouse, res;
        nouse = 0; use = res = nums[0] * m[nums[0]];
        for (int i = 1; i < k; i++) {
            int tmp = use;
            if (nums[i] == nums[i - 1] + 1)
                use = nouse + m[nums[i]] * nums[i];
            else
                use = max(nouse, use) + m[nums[i]] * nums[i];
            nouse = max(nouse, tmp);
            res = max(use, nouse);
        }

        return res;
    }
};
```