---
title: Summary Ranges
date: 2021-01-04
---
#### Given a sorted integer array without duplicates, return the summary of its ranges.

```
Example 1:

Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.

Example 2:

Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
```

#### Solutions

1. ##### two pointers

- Here I used to_string function in c++, you can write an new one.

```cpp
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;

        int i = 0, j = 0;

        while (j < nums.size()) {
            if (!(j + 1 < nums.size() && nums[j + 1] == nums[j] + 1)) {
                string cur = to_string(nums[i]);
                if (j != i)
                    cur += "->" + to_string(nums[j]);
                res.push_back(cur);
                i = j + 1;
            }
            j++;
        }
        return res;
    }
};
```