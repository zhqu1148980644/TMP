---
title: Rotate Array
date: 2021-01-04
---
#### Given an array, rotate the array to the right by k steps, where k is non-negative.

```
Example 1:

Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
```

#### Note:

Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?

#### Solutions

1. ##### use extra memory

- place each element in the right place.


2. ##### use cycle replacement

- Due to the limitation of constant space, we need to move items in place.
    - Each time we move an item to it's proper place, the item in that place needs to be moved too.
    - For simplicity, we can store the replaced item in the place of the moved item. Then back to the first step.
    - As all steps are always the same, this moving loop will finally back to the original place. i.e No need and no way to move anymore.
    - Then start at the next index.


```cpp
void rotate(int* nums, int numsSize, int k){
    k = k % numsSize;
    for (int i = 0, times = 0; times < numsSize; i++) {
        int cur_i = i;
        do {
            int next_i = (cur_i + k) % numsSize;
            int tmp = nums[next_i];
            nums[next_i] = nums[i];
            nums[i] = tmp;
            cur_i = next_i;
            times++;
        } while (cur_i != i);
    }
}
```

3. ###### reverse

- reverse the whole array: `n` items.
- reverse the front `k` items;
- reverse the left `n - k` items.

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```
