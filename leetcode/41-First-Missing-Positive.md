### Given an unsorted integer array, find the smallest missing positive integer.

```
Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
```

### Note:

Your algorithm should run in O(n) time and uses constant extra space.

### Solutions

1. #### bucket sort O(n)

- In-place bucket sort.
    - right bucket, `[1, 2, 3, 4, 5, 6... ,n]`
    - the mixing interger can't be bigger than n + 1; n: length of vector
- Iteratively check the array from the beginning till find the first element whose value is not in the right position.

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int max_num = nums.size();
        for (int i = 0; i < max_num; i++) {
            while (nums[i] != i + 1)
                if (nums[i] <= 0 || nums[i] > max_num || nums[i] == nums[nums[i] - 1])
                    break;
                else
                    swap(nums[i], nums[nums[i] - 1]);
        }
        for (int i = 0; i < max_num; i++) {
            if (nums[i] != i + 1)
                return i + 1;
        }
        return max_num + 1;
    }
};
```
