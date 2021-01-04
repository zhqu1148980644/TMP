---
title: Contiguous Array
date: 2021-01-04
---
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

#### Solutions

1. ##### prefix sum with hash map O(n)

- The idea is to count the number of 1 and 0 meeted before and record when the difference between these two counts has been met before.

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> m;
        m.emplace(0, -1);

        int res = 0, n0 = 0, n1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            n0 += nums[i] == 0;
            n1 += nums[i] == 1;
            if (m.count(n1 - n0))
                res = max(res, i - m[n1 - n0]);
            else
                m.emplace(n1 - n0, i);
        }

        return res;
    }
};
```

Or replace diff to count of 1. This approach can be seen as replacing all 0s to -1, and finding continous ranges with equal number of 1 and 0 equals to find ranges with sum `0`.

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> m;
        m.emplace(0, -1);

        int res = 0, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i] == 1 ? 1 : -1;
            if (m.count(count))
                res = max(res, i - m[count]);
            else
                m.emplace(count, i);
        }

        return res;
    }
};
```