Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).

 

Example 1:

Input: nums = [4,2,3]
Output: true
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:

Input: nums = [4,2,1]
Output: false
Explanation: You can't get a non-decreasing array by modify at most one element.
 

Constraints:

1 <= n <= 10 ^ 4
- 10 ^ 5 <= nums[i] <= 10 ^ 5

#### Solutions

1. ##### straight forward

- borrowed from others.
- count the number of pairs with `nums[i] > nums[i + 1]` or `nums[i - 1] > nums[i + 1]`, return false when either counts gets greater than `1`.
- Denotes counts of case `nums[i] > nums[i + 1]` is `r1`, and the other case is `r2` and `nums[i - 1]..nums[i + 2]` is represented as `a b c d`
    - if `r1 == 1 r2 == 0`, we have `a <= c && <= d  AND b <= d`, we can change `c` to any numbers between[b:d].
    - if `r1 == 0, r2 == 1`. This case is impossible. Because `r1 == 0`, we have `b >= a` which leads to `b >= a > c` ie: `r1 != 0`.
    - if `r1 == 1 r2 == 1`, the only case is `a > c and b >= a and b > c`, like the first case, cange `c` to numbers between [b:d] could make the sequence increasing(>=).

```c++
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        if (nums.size() <= 2) return true;
        int rnum1 = nums[0] > nums[1], rnum2 = 0;
        for (int i = 1; i < nums.size() - 1; i++) {
            if (nums[i] > nums[i + 1])
                rnum1++;
            if (nums[i - 1] > nums[i + 1])
                rnum2++;
            if (rnum1 > 1 || rnum2 > 1)
                return false;
        }
        return true;
    }
};
```