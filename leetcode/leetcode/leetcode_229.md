---
title: Majority Element II
date: 2021-01-04
---
#### Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

#### Note: 
The algorithm should run in linear time and in O(1) space.

```
Example 1:

Input: [3,2,3]
Output: [3]
Example 2:

Input: [1,1,1,3,3,2,2,2]
Output: [1,2]
```

#### Solutions

1. ##### Boyer-Moore voting algorithm

- As there are at most `two` numbers with occurrence greater than n / 3, we can simultaneously maintain two counts for the number appeared most and the number appeared the second most.

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int num1 = INT_MIN, num2 = INT_MAX;
        int count1 = 0, count2 = 0;

        for (auto & num : nums) {
            if (num == num1)
                count1++;
            else if (num == num2)
                count2++;
            else if (count1 == 0) {
                count1++; num1 = num;
            }
            else if (count2 == 0) {
                count2++; num2 = num;
            }
            else {
                count1--; count2--;
            }
        }
        count1 = count2 = 0;
        for (auto & num : nums) {
            if (num == num1) count1++;
            if (num == num2) count2++;
        }
        vector<int> res;
        if (count1 > nums.size() / 3)
            res.push_back(num1);
        if (count2 > nums.size() / 3)
            res.push_back(num2);

        return res;
    }
};
```
