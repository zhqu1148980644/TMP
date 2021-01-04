---
title: Longest Continuous Increasing Subsequence
date: 2021-01-04
---
#### Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

```
Example 1:

Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4. 

Example 2:

Input: [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
```

#### Note: Length of the array will not exceed 10,000. 

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (!nums.size()) return 0;
        int maxlen = 1, cnt = 1, res = 1;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] < nums[i + 1])
                cnt++;
            else {
                res = max(res, cnt);
                cnt = 1;
            }
        }
        res = max(res, cnt);

        return res;
    }
};
```