---
title: Missing Element in Sorted Array
date: 2021-01-04
---
Given a sorted array A of unique numbers, find the K-th missing number starting from the leftmost number of the array.

 

Example 1:

Input: A = [4,7,9,10], K = 1
Output: 5
Explanation: 
The first missing number is 5.
Example 2:

Input: A = [4,7,9,10], K = 3
Output: 8
Explanation: 
The missing numbers are [5,6,8,...], hence the third missing number is 8.
Example 3:

Input: A = [1,2,4], K = 3
Output: 6
Explanation: 
The missing numbers are [3,5,6,7,...], hence the third missing number is 6.
 

Note:

1 <= A.length <= 50000
1 <= A[i] <= 1e7
1 <= K <= 1e8

#### Solutions

1. ##### straight forward O(n)

```cpp
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        nums.push_back((int)(1e9));
        for (int i = 0; i < nums.size() - 1; i++) {
            int prevk = k;
            k -= nums[i + 1] - nums[i] - 1;
            if (k <= 0)
                return nums[i] + prevk;
        }

        return -1;
    }
};
```

2. ##### binary search O(log(n))

- search for the insertion point(left boundary) of the the k'th missing number. The the count of missing numbers before `nums[mid]` can be calculated in `O(1)` time.

```cpp
class Solution {
public:
    inline int missnum(vector<int> & nums, int i) {
        // actualy (nums[i] - nums[0] + 1) - (i + 1)
        return nums[i] - nums[0] - i;
    }
    int missingElement(vector<int>& nums, int k) {
        int st = nums[0], lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            // again, when missnum(mid) is slower than k, we are not sure if the k'th miss number resides in nums[mid]:nums[mid + 1].
            // however, if missnum(mid + 1) is slower than k, I am sure that the left boundary should be at least `mid + 1`
            // another way is to search for the right boundary, then just check missnum(mid) < k is ok.
            if (missnum(nums, mid + 1) < k)
                lo = mid + 1;
            else
                hi = mid;
        }

        return nums[lo] + (k - missnum(nums, lo));
    }
};
```