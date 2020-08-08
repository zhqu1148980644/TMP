Given an array of integers nums and an integer k. A subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

 

Example 1:

Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
Example 2:

Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.
Example 3:

Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
 

Constraints:

1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length

#### Solutions

1. ##### sliding window

```c++
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        nums.push_back(1);
        int i = 0, validj = 0, j = 0, odd = 0, res = 0;
        // prevj is the first time when the window has k odd numbers
        while (j < nums.size()) {
            if (nums[j++] & 1 && ++odd == k)
                validj = j - 1;
            if (odd > k) {
                while (odd > k) {
                    // for each valid i, it can be paired with (j - validj - 1) number of right boundaries
                    odd -= (nums[i++] & 1);
                    res += j - validj - 1;
                }
                // make sure to update validj
                validj = j - 1;
            }
        }

        return res;
    }
};
```

2. ##### prefix sum

- reference: https://leetcode-cn.com/problems/count-number-of-nice-subarrays/comments/358786
- Convert the problem into `the number of subarrays with sum equals to K with odd treated as 1 and even treated as 0`, then the problem is the same as `problem 560`.

```c++
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int res = 0, sum = 0;
        unordered_map<int, int> sums; sums[0] = 1;
        for (auto n : nums) {
            sum += n & 1;
            if (sums.count(sum - k))
                res += sums[sum - k];
            sums[sum]++;
        }

        return res;
    }
};
```