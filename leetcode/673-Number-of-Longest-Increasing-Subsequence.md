#### Given an unsorted array of integers, find the number of longest increasing subsequence.

```
Example 1:

Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:

Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
```

#### Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int. 


#### Solutions

1. ##### dynamic programming

- Add another `dp table` to record the `number` of longest increasing subsequences ending with each position based on the solution in `problem 300`.

```c++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int> maxlen(nums.size(), 1);
        vector<int> count(nums.size(), 1);
        int final_maxlen = 1;

        for (int j = 0; j < nums.size(); j++) {
            int curlen = 1;
            int curcount = 1;
            for (int i = 0; i < j; i++) {
                if (nums[i] < nums[j]) {
                    if (maxlen[i] + 1 > curlen) {
                        curlen = maxlen[i] + 1;
                        curcount = count[i];
                    }
                    else if (maxlen[i] + 1 == curlen)
                        curcount += count[i];
                }
            }
            maxlen[j] = curlen;
            count[j] = curcount;
            final_maxlen = max(final_maxlen, curlen);
        }
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
            if (maxlen[i] == final_maxlen)
                res += count[i];
        return res;
    }
};
```

2. ##### interval tree

3. ##### binary search

- A extension to binary search method used in problem 300.
- reference: https://leetcode.com/problems/number-of-longest-increasing-subsequence/discuss/228153/C%2B%2B-8ms-O(N*log(N))-beats-100-queue-easy-to-understand