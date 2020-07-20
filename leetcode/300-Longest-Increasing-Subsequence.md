#### Given an unsorted array of integers, find the length of longest increasing subsequence.

```
Example:

Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
```

#### Note:

-    There may be more than one LIS combination, it is only necessary for you to return the length.
-    Your algorithm should run in O(n2) complexity.

#### Follow up:
Could you improve it to O(n log n) time complexity?

#### Solutions

1. ##### dynamic programming O(n2)

- `dp[i]` represents the length of the longest increasing subsequence within `s[:i]`

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

2. ##### binary search O(nlog(n))

- Hard to prove the correctness, here is my thought:
- `tails[i]` represents the minumum tail element among all increasing subsequences with length `i + 1`.
- There are two situations when looping through the sequence:
    - The current number is larger than the tail of `tails`: Pushing it at the back repsents the newly found increasing subsequence with longer length.
    - The current number is smaller than the tail: Use binary search to find the correct point in `tails` and replace the first larger/equal one with the current number. This step does not change the correctness of `tails`(invariant).

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;

        int i, j;
        for (auto & num : nums) {
            if (!tails.size() || num > tails.back())
                tails.push_back(num);
            else {
                i = 0, j = tails.size() - 1;
                while (i < j) {
                    int mid = i + ((j - i) >> 1);
                    if (num > tails[mid])
                        i = mid + 1;
                    else
                        j = mid;
                }
                tails[i] = num;
            }
        }

        return tails.size();
    }
};
```