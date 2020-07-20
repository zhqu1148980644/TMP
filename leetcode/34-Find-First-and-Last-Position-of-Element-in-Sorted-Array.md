### Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

```
Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
```


### Solutions

1. #### One time binary search.

- Binary seach the first one not smaller than the target(right boundary).
- Then find the first one not equal to the target starting from the right boundary.

2. #### Two times binary search.

When there are two many duplicates.

```c++
inline int binarySearch(vector<int> & nums, int target) {
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        //return the first not smaller than the target
        if (target <= nums[mid])
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int lo = binarySearch(nums, target);
        if (lo == nums.size() || nums[lo] != target)
            return vector<int>{-1, -1};
        else {
            int hi = (nums[nums.size() - 1] >= target + 1) ? binarySearch(nums, target + 1): nums.size();
            return vector<int>{lo, hi - 1};
        }
    }
};
```
