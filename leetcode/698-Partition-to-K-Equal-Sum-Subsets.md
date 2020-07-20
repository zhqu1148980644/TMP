Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

 

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 

Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.


#### Solutions

1. ##### backtrack

- The main trick is to start searching subsets from the largest available number to the smallest. why?
- If the searching order is reversed, a hash map for recording bad states should be matained.

```c++
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k) return false;
        int target = total / k, allused = 0, len = nums.size();
        for (int i = 0; i < len; i++) {
            allused <<= 1; allused |= 1;
        }
        sort(nums.begin(), nums.end());
        if (nums.back() > target) return false;

        // state is a interger representing usage info for each num, you could instead use a `visited` hash set
        function<bool(int, int, int)> solve = [&](int state, int sum, int ed) {
            if (state == allused) return true;
            int max = target - (sum % target);
            for (int i = ed; i >= 0; i--) {
                if ((state & (1 << i)) || nums[i] > max) continue;
                if (solve(state | (1 << i), sum + nums[i], nums[i] == max ? len - 1 : i - 1))
                    return true;
            }
            return false;
        };

        return solve(0, 0, len - 1);
    }
};
```