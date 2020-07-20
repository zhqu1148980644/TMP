Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.

 

Example 1:

Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:

Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
 

Constraints:

The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.

#### Solutions

1. ##### prefix sum

- Caution: `k = 0` should be considered separately.
- Since all numbers are positive, even though `k` may be negative, `positive % negative` are always positive.

```c++
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // k equals to 0 equals could cause
        // 1. mod raise error
        // 2. There is already a 0(0, -1) inserted into the map before. ie function return true when ever meet a single zero
        if (k == 0) {
            for (int i = 0; i < nums.size() - 1; i++)
                if (nums[i] == nums[i + 1] && nums[i] == 0)
                    return true;
            return false;
        }
        unordered_map<int, int> m {{0, -1}};
        int sum = 0, n;
        for (int i = 0; i < nums.size(); i++) {
            n = nums[i]; sum += n;
            if (m.count(sum % k)) {
                if (i - m[sum % k] >= 2)
                    return true;
            }
            else
                // only if it doesn't exist in the map, otherwise record a new one with larger index would miss the result.
                m.emplace(sum % k, i);
        }

        return false;
    }
};
```

or when k equals to 0, degrade the algorithm into normal version. ie: record real prefixsum. Sum of continuous subarray equals to 0 only when `prefixsum[cur] == prefixsum[index before cur]`.

```c++
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m {{0, -1}};
        int sum = 0, n;
        for (int i = 0; i < nums.size(); i++) {
            n = nums[i]; sum += n;
            int find = k ? sum % k : sum;
            if (m.count(find)) {
                if (i - m[find] >= 2)
                    return true;
            }
            else
                m.emplace(find, i);
        }

        return false;
    }
};
```