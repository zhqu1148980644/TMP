#### Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

```
Example:

Input:  [1,2,1,3,2,5]
Output: [3,5]
```

#### Note:

-    The order of the result is not important. So in the above example, [5, 3] is also correct.
-    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?


#### Solutions

1. ##### bit operations

- Use xor operations to get the single number as we did in `problem 136`.
- However, there are two single numbers, the xor result of all numbers equals to `num1 ^ num2`.
- Thus, we separate all numbers into two groups with each single number inside one group.
- Bits setted to 1 in `num1 ^ num2` represents the bits where num1 and num2 differ.

```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int res = 0;
        for (auto & num : nums)
            res ^= num;
        // get the right most bit set to 1.
        int diff = res & -res;

        int a = 0, b = 0;
        // separate numbers into two groups
        for (auto & num : nums) {
            if (num & diff)
                a ^= num;
            else
                b ^= num;
        }
        return {a, b};
    }
};
```