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
        if (!nums.size() || !k) return false;
        size_t total = accumulate(nums.begin(), nums.end(), size_t{0});
        
        if (total % k) return false;
        size_t target = total / k, len = nums.size();
        int allused = (1 << len) - 1;

        sort(nums.rbegin(), nums.rend());
        if (nums[0] > target) return false;

        // state is a interger representing usage info for each num, you could instead use a `visited` hash set
        function<bool(int, int, int)> solve = [&](int state, int sum, int st) {
            if (state == allused) return true;
            int max = target - (sum % target);
            for (int i = st; i < len; i++) {
                if (state & (1 << i) || nums[i] > max)
                    continue;
                if (solve(state | (1 << i), sum + nums[i], nums[i] == max ? 0 : i + 1))
                    return true;
            }
            return false;
        };

        return solve(0, 0, 0);
    }
};
```

2. ##### dynamic programming

- Check the official answer.