---
title: Wiggle Sort II
date: 2021-01-04
---
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?


#### Soltuions

- Note that problem changed the ordering requirements of ajacent numbers to `nums[0] < nums[1] > nums[2]` compared to `nums[0] <= nums[1] >= nums[2]` in `problem 280`.

1. ##### sort into two parts O(nlog(n)) S(n)

- reference: https://leetcode-cn.com/problems/wiggle-sort-ii/solution/yi-bu-yi-bu-jiang-shi-jian-fu-za-du-cong-onlognjia/
- Sort the arry in ascending order and split into two parts, then iteratively putting elements in each part into the original array. To aviod breaking rules due to the existence of duplicate numbers, fetch elements in two parts from the end to start.
    - for example: 1 2 5 5 5 6 8, split into ` 1 2 5 5` and `5 6 8`, the merged array would be `1 5 2 5 5 6 8`.
    - If we merged them from the back: `5 5 2 1` and `8 6 5`, the merged array would be `5 8 5 6 2 5 1`

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> sorted(nums);
        sort(sorted.begin(), sorted.end());
        int mid = (nums.size() - 1) / 2;
        int i = mid, j = nums.size() - 1;
        int w = 0;
        while (j != mid) {
            nums[w++] = sorted[i--];
            nums[w++] = sorted[j--];
        }
        if (i >= 0) nums[w++] = sorted[i--];
    }
};
```

2. ##### partition into two parts O(n) S(n)

- Actually the ordering of numbers in each part is nonessential as long as:
    - the left part is smaller than the right part.
    - numbers equal to the median(mid value) are gathered in the middle.

```cpp
#include <experimental/random>
class Solution {
public:
    int quickselect(vector<int> & nums, int k) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            swap(nums[lo], nums[std::experimental::randint(lo, hi)]);
            int pivot = nums[lo];
            int i = lo, j = hi;
            while (i < j) {
                while (i < j && nums[j] >= pivot) j--;
                nums[i] = nums[j];
                while (i < j && nums[i] <= pivot) i++;
                nums[j] = nums[i];
            }
            nums[i] = pivot;
            if (i <= k) lo = i + 1;
            if (i >= k) hi = i - 1;
        }
        return nums[k];
    }
    void partition(vector<int> & nums, int val) {
        int i = 0, k = 0, j = nums.size() - 1;
        while (k < j) {
            if (nums[k] > val)
                swap(nums[k], nums[j--]);
            else if (nums[k] < val)
                swap(nums[i++], nums[k++]);
            else
                k++;
        }
    }
    void wiggleSort(vector<int>& nums) {
        int mid = (nums.size() - 1) / 2;
        vector<int> clone(nums);
        // or nth_element(clone.begin(), clone.begin() + mid, clone.end())
        int median = quickselect(clone, mid);
        partition(clone, median);
        int i = mid, j = nums.size() - 1, w = 0;
        while (j != mid) {
            nums[w++] = clone[i--];
            nums[w++] = clone[j--];
        }
        if (i >= 0) nums[w++] = clone[i--];
    }
};
```


3. ##### optimized  O(n) S(1)

- check reference

```cpp

```