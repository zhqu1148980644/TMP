Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.

Example 1:

Input: nums = [1,2,3,1], k = 3, t = 0
Output: true
Example 2:

Input: nums = [1,0,1,1], k = 1, t = 2
Output: true
Example 3:

Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false

#### Solutions

- Tree set supports both range search and insert/remove in O(log(n)) time.

```c++
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (t < 0) return false;
        set<long> s;
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) s.erase(nums[i - k - 1]);
            auto lo = s.lower_bound((long)nums[i] - t);
            if (lo != s.end() && *lo <= (long)nums[i] + t)
                return true;
            s.insert(nums[i]);
        }
        return false;
    }
};
```