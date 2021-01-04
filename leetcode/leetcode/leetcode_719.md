---
title: Find K th Smallest Pair Distance
date: 2021-01-04
---
Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.

Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0 
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.
Note:
2 <= len(nums) <= 10000.
0 <= nums[i] < 1000000.
1 <= k <= len(nums) * (len(nums) - 1) / 2.

#### Solutions

1. ##### binary search

- guess the k-th smallest distance using binary search, check if the number of pairs less/eq to the guessed distance is smaller than k, if this is true, the gussed distance must be underestimated, thus choose a higher one as the lower bound(mid + 1).

```cpp
class Solution {
public:
    int count(vector<int> & nums, int dis) {
        int i = 0, res = 0;
        for (int j = 0; j < nums.size(); j++) {
            while (nums[j] - nums[i] > dis)
                i++;
            res += j - i;
        }
        return res;
    }
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int lo = 0, hi = nums.back() - nums.front();

        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            // count num of pairs with distance <= gussed_dis(mid)
            if (count(nums, mid) < k)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
};
```

2. ##### priority queue


3. ##### binary search with prefix sunm