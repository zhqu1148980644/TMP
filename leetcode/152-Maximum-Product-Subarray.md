#### Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

```
Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
```

#### Solutions

1. ##### dynamic programming

- Use a dp table to record maximum product and minimum product of continuous subarrays ends with each position.
- `maxp[i] = maxp[i] * num if num > 0 else max(minp[i] * num, num)`

```c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int lastmin = 1, lastmax = 1;
        int maxproduct = INT_MIN;
        for (auto & num : nums) {
            int tmp = max(lastmax * num, max(lastmin * num, num));
            lastmin = min(lastmax * num, min(lastmin * num, num));
            lastmax = tmp;
            if (lastmax > maxproduct)
                maxproduct = lastmax;
        }
        return maxproduct;
    }
};
```



2. ##### two pass

- reference: https://leetcode-cn.com/problems/maximum-product-subarray/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--36/
- The maximum product subarray must contain even number of negative numbers(0 is even).

```c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int product = 1, max = INT_MIN;

        for (int i = 0; i <= nums.size() - 1; i++) {
            product *= nums[i];
            if (product > max)
                max = product;
            if (!product)
                product = 1;
        }

        product = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            product *= nums[i];
            if (product > max)
                max = product;
            if (!product)
                product = 1;
        }

        return max;
    }
};
```