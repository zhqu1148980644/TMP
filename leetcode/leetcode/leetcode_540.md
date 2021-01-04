---
title: Single Element in a Sorted Array
date: 2021-01-04
---
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. Find this single element that appears only once.

Follow up: Your solution should run in O(log n) time and O(1) space.

 

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10
 

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5

#### Solutions

1. ##### binary search

- For searching target in an array, only binary search can leads to `log(n)` time complexity.
- The searching direction will be influenced by the odevity of the half-part's size.
    - for example:
    - `1133 4 4566`, half size is `4(even)`, when `nums[mid] == nums[mid + 1] -> 4 = 4`, the singleton must be within the right half(not include mid) of the array.
    - `113 3 455`, half size is `3(odd)`, when `nums[mid] != nums[mid + 1] -> 3 != 4`, ...
    - Though it's safety to move the beginning of the searching range to `mid + 1` in both cases, in the first case, the final range may be `45`, it's unable to determine which one is the singleton. So we set `lo = mid` in the first case. In another perspective, we are actually maintaining the invariant that the length of the whole search range is `odd`.

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int half = (hi - lo) / 2;
            int mid = lo + ((hi - lo) / 2);
            if (half % 2) {
                if (nums[mid] != nums[mid + 1])
                    lo = mid + 1;
                else
                    hi = mid;
            }
            else {
                if (nums[mid] == nums[mid + 1])
                    lo = mid;
                else
                    hi = mid;
            }
        }
        return nums[lo];
    }
};
```

or merge these two conditions.

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int half = (hi - lo) / 2;
            int mid = lo + ((hi - lo) / 2);
            if ((nums[mid] == nums[mid + 1]) ^ (half & 1))
                lo = mid + (half & 1);
            else
                hi = mid;
        }
        return nums[lo];
    }
};
```