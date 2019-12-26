#### Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

#### Note: You are not suppose to use the library's sort function for this problem.

```
Example:

Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
```

#### Follow up:

- A rather straight forward solution is a two-pass algorithm using counting sort.
- First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
- Could you come up with a one-pass algorithm using only constant space?


#### Solutions

1. ##### quick sort

- use two pinters to separate the array into three part.
- When moving the `cur` pointer, the invariance is:
    - elements before `i` are always smaller than 1 and elements after `j` are always larger than 1.
    - elements in `array[i:cur)` are always 1. `i == cur` means no 1 ecountered.

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i = 0, j = nums.size() - 1, cur = 0;
        // visit cur even when cur == j
        while (cur <= j)
            if (nums[cur] < 1)
                // nums[i] can be either 1 or 0. The invariance won't change in either case.
                swap(nums[cur++], nums[i++]);
            else if (nums[cur] > 1)
                // can not move cur forward, the swapped num[j] may be 0, moving cur forward will leave a zero in array[i: cur)
                swap(nums[cur], nums[j--]);
            else
                // we are not moving the i or j, the invariance maitains.
                cur++;
    }
};
```