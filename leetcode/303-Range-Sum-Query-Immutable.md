#### Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

```
Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
```

#### Note:

-    You may assume that the array does not change.
-    There are many calls to sumRange function.

#### Solutions

1. ##### sum prefix

```c++
class NumArray {
private:
    vector<int> accum;
public:
    NumArray(vector<int>& nums) : accum(nums.size() + 1, 0) {
        for (int i = 0; i < nums.size(); i++)
            accum[i + 1] = accum[i] + nums[i];
    }

    int sumRange(int i, int j) {
        return accum[j + 1] - accum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
```