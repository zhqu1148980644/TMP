---
title: Minimum Size Subarray Su
date: 2021-01-04
---
#### Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

```
Example: 

Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
```

#### Follow up:
- If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n). 

#### Solutions

1. ##### sliding window O(n)

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int i = 0, j = 0, sum = 0, minlen = nums.size() + 1;
        while (j < nums.size()) {
            if ((sum += nums[j++]) >= s) {
                while (sum >=  s)
                    sum -= nums[i++];
                minlen = min(minlen, j - i + 1);
            }
        }
        return minlen == nums.size() + 1 ? 0 : minlen;
    }
};
```

2. ##### binary search O(n + xlog(n))

- Maintain an array of accumulated sum for each element and use binary search to search for the left-closest element `j` that is larger than `accm[i] - s`, then the minimum subarray with sumvalue larger/equal than s ending with `i` is `num[j - 1, i]` 

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (!nums.size() && s) return 0;
        vector<int> accum(nums.size(), 0);
        accum[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
            accum[i] = nums[i] + accum[i - 1];

        int minlen = nums.size() + 1;
        for (int i = nums.size() - 1; i >= 0 && accum[i] >= s; i--) {
            int left = upper_bound(accum.begin(), accum.begin() + i, accum[i] - s) - accum.begin();
            minlen = min(minlen, i - left + 1);
        }
        return minlen == nums.size() + 1 ? 0 : minlen;
    }
};
```