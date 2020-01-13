#### Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

```
Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
```

#### Note:

-    You must do this in-place without making a copy of the array.
-    Minimize the total number of operations.

#### Solutions

1. ##### two pointers

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0, j = 0;
        while (j < nums.size()) {
            if (nums[j] != 0)
                nums[i++] = nums[j];
            j++;
        }

        while (i < nums.size())
            nums[i++] = 0;

    }
};
```

- The first version will do redundant assingment operations at the end of the the array if the array contains too much zeroes.
- This version ensures that elements between i and j are always zeroes.

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0, j = 0;
        while (j < nums.size()) {
            if (nums[j] != 0)
                swap(nums[i++], nums[j]);
            j++;
        }
    }
};
```