---
title:  Largest Multiple of Three
date: 2021-01-04
---
Given an integer array of digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order.

Since the answer may not fit in an integer data type, return the answer as a string.

If there is no answer return an empty string.

 

```
Example 1:

Input: digits = [8,1,9]
Output: "981"

Example 2:

Input: digits = [8,6,7,1,0]
Output: "8760"

Example 3:

Input: digits = [1]
Output: ""

Example 4:

Input: digits = [0,0,0,0,0,0]
Output: "0"
```

 

#### Constraints:

-    1 <= digits.length <= 10^4
-    0 <= digits[i] <= 9
-    The returning answer must not contain unnecessary leading zeros.

#### Solutions

- reference: https://leetcode-cn.com/problems/largest-multiple-of-three/solution/c-qu-diao-zui-xiao-zhi-8ms-by-yusenzhang_chatc/
- If the `sum` of digits of a number is a multiple of `3`, then this number is a multiple of `3`.
- Thus the problem equals to finding the subarray with maximum sum and the sum's remainder of `3` is `0`.
    - There are three cases:
    - `sum % 3 == 0`, take all numbers.
    - `sum % 3 == 1`, try to remove the smallest `number(num % 3 == 1)`, otherwise remove `2` smallest `number(num % 3 == 2)`.
    - `sum % 3 == 2`, remove the smallest `number(num % 3 == 2` or `2` smallest `number(num % 3 == 1)`.


1. ##### math

```cpp
class Solution {
public:
    vector<int> m = vector<int>(10);
    bool remove(int d) {
        for (int i = d; i < 9; i += 3)
            if (m[i]-- > 0)
                return true;
        return false;
    }
    string largestMultipleOfThree(vector<int>& digits) {
        for (auto n : digits) m[n]++;
        if (m[0] == digits.size()) return "0";

        int sum = accumulate(digits.begin(), digits.end(), 0);
        if (sum % 3 == 1) {
            if (!remove(1)) {
                remove(2); remove(2);
            }
        }
        else if (sum % 3 == 2) {
            if (!remove(2)) {
                remove(1); remove(1);
            }
        }
        
        string res;
        for (int i = 9; i >= 0; i--)
            while (m[i]-- > 0)
                res.push_back(i + '0');
        
        return res;
    }
};
```