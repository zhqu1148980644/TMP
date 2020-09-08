Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);


#### Solutions

1. ##### Reservoir Sampling

- reference: https://leetcode-cn.com/problems/random-pick-index/solution/xu-shui-chi-chou-yang-wen-ti-by-an-xin-9/
- Sample each element with probability 1 / n;
- Suppose there are `4` items, following the rule of selecting each encountered index with probability of `1 / numseen`(include self). we have:
- the prob of selected the first element at last is: `3/4 * 2/3 * 1/2 == 1/4`
-                          second                   `3/4 * 2/3 * 1/2 == 1/4`
-                          third                    `3/4 * 1/3       == 1/4`
-                          fourth                   `1/4             == 1/4`

```c++
class Solution {
public:
    vector<int> nums;
    Solution(vector<int>& nums) : nums(nums) {
    }

    int pick(int target) {
        int cnt = 0, index = -1;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] == target) {
                cnt++;
                // (1 / cnt) prob to slect the current index 
                if (rand() % cnt == 0)
                    index = i;
            }
        return index;
    }
};
```