##### Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

```
Example:

Input:  [1,2,3,4]
Output: [24,12,8,6]
```

#### Note: Please solve it without division and in O(n).

#### Follow up:
Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)

#### Solutions

Note that the problem said we cannot use devision.

1. ##### two pass o(n) S(n)/S(1)

- Calculate the product of all elements left/right to each item.
- The product except an item itself is the multiplication of product of all elements left and right to this item.

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++)
            left[i] = left[i - 1] * nums[i - 1];

        vector<int> res(nums.size(), 1);

        for (int i = nums.size() - 2; i >= 0; i--)
            res[i] = res[i + 1] * nums[i + 1];

        for (int i = 0; i < nums.size(); i++)
            res[i] *= left[i];

        return res;
    }
};
```

Or we can use a variable denoted as `right` to record the multiplication of items on the right.

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++)
            left[i] = left[i - 1] * nums[i - 1];

        int right = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            left[i] = left[i] * right;
            right *= nums[i];
        }

        return left;
    }
};
```

2. ##### two pointers one pass O(n) S(1)

- Combine the multiplication of left product and right product in one loop and update the output array at the same time.

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);

        int i = 0, j = nums.size() - 1;
        int leftpro = 1, rightpro = 1;
        for (int i = 0, j = nums.size() - 1; i < nums.size(); i++, j--) {
            res[i] *= leftpro;
            leftpro *= nums[i];
            res[j] *= rightpro;
            rightpro *= nums[j];
        }

        return res;
    }
};
```
