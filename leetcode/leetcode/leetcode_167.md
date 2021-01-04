---
title: Two Sum II Input array is sorte
date: 2021-01-04
---
#### Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

#### Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.

```
Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
```

#### Solutions

1. ##### two pointers

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while ( numbers[i] + numbers[j] != target) {
            if (numbers[i] + numbers[j] > target)
                j--;
            else
                i++;
        }
        return {i + 1, j + 1};
    }
};
```

2. ##### one pointer with binary search

- Loop through each item.
- Use binary search to check if the candidate exists.