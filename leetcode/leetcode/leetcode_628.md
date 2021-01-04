---
title: Maximum Product of Three Numbers
date: 2021-01-04
---
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:

Input: [1,2,3]
Output: 6
 

Example 2:

Input: [1,2,3,4]
Output: 24
 

Note:

The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.

##### Solutions

1. ##### math

- Denote `min1,2, max1,2,3` as the minimum/maximum numbers in the sorted array, the maximum product of three numbers must be one of `min1(<0) * min2(<)) * max1` and `max1 * max2 * max3`.

```cpp
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int min1 = 0, min2 = 0;
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        int res = INT_MIN;
        for (auto n : nums) {
            if (n < min1) {
                min2 = min1;
                min1 = n;
            }
            else if (n < min2)
                min2 = n;
            if (n > max1) {
                max3 = max2;
                max2 = max1;
                max1 = n;
            }
            else if (n > max2) {
                max3 = max2;
                max2 = n;
            }
            else if (n > max3)
                max3 = n;

            if (max3 != INT_MIN)
                res = max(min1 * min2 * max1, max1 * max2 * max3);
        }

        return res;
    }
};
``

