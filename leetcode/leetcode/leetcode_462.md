---
title: Minimum Moves to Equal Array Elements II
date: 2021-01-04
---
Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:

Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one element):

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]


#### Solutions

- As all elements can be increased/decreased by 1, a simple intution is that the target number must be in the middle of the range `(min, max)`.
- This middle node is the median number
    - if `n % 2 == 1`, select `nums[n / 2]`;
    - if `n % 2 == 0`, select either `nums[n / 2] or nums[n / 2 + 1]`

- See `problem 296` for simple solution.


1. ##### sort O(nlog(n))

```cpp
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int median = nums[nums.size() / 2];
        int res = 0;
        for (auto n : nums)
            res += abs(n - median);
        return res;
    }
};
```

2. ##### quick select O(n)

```cpp
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int k = nums.size() / 2;
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int i = lo, j = hi, mid = lo + ((hi - lo) / 2); auto it = nums.begin();
            std::__move_median_to_first(it + lo, it + lo + 1, it + mid, it + hi, 
                [](auto & it1, auto & it2) {return *it1 < *it2;});
            int pivot = nums[lo];
            while (i < j) { 
                while (i < j && pivot < nums[j]) j--;
                nums[i] = nums[j];
                while (i < j && nums[i] <= pivot) i++;
                nums[j] = nums[i];
            }
            nums[i] = pivot;
            if (i <= k) lo = i + 1;
            if (i >= k) hi = i - 1;
        }
        int median = nums[k];
        int res = 0;
        for (auto n : nums)
            res += abs(median - n);
        return res;
    }
};
```