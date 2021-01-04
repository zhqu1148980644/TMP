---
title: Split Array With Same Average
date: 2021-01-04
---
In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)

Return true if and only if after such a move, it is possible that the average value of B is equal to the average value of C, and B and C are both non-empty.

Example :
Input: 
[1,2,3,4,5,6,7,8]
Output: true
Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.
Note:

The length of A will be in the range [1, 30].
A[i] will be in the range of [0, 10000].

#### Solutions

- The answer exists only if `sum * len(part1) == sum(part1) * n`

1. ##### dynamic programming O(sum * len^2)

- `dp[sum][k]` represents if sum can be made from k numbers
- When updating sates, each number can only be used once.
- Time limit exceed;

```cpp
class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int len = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);
        if (sum == 0) return A.size() > 1;
        vector<vector<bool>> dp(sum + 1, vector<bool>(len));
        dp[0][0] = 1;
        // reverse search to ensure dp[s - n] is not setted in the same step(curn)
        // try to use each element
        for (auto n : A)
            for (int s = sum - 1; s >= n; s--)
                for (int k = 0; k < len - 1; k++)
                    if (dp[s][k + 1] || dp[s - n][k])
                        dp[s][k + 1] = true;

        for (int s = 1; s < sum; s++)
            if ((s * len) % sum == 0)
                if (dp[s][(s * len) / sum])
                    return true;

        return false;
    }
};
```

- Optimized version, use bit position represents k. O(sum * len)


```cpp
class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int len = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);
        if (sum == 0) return A.size() > 1;
        vector<int> dp(sum);
        dp[0] |= 1;
        // reverse search to ensure dp[s - n] is not setted in the same step(curn)
        // try to use each element
        for (auto n : A)
            for (int s = sum - 1; s >= n; s--)
                dp[s] |= (dp[s - n] << 1);

        for (int s = 1; s < sum; s++)
            if ((s * len) % sum == 0 
                && dp[s] & (1 << (s * len) / sum))
                    return true;

        return false;
    }
};
```

```Rust
impl Solution {
    pub fn split_array_same_average(a: Vec<i32>) -> bool {
        let sum = a.iter().sum::<i32>() as usize;
        if sum == 0 { return a.len() > 1; }
        let mut dp: Vec<u32> = vec![0; sum];
        dp[0] = 1;
        for num in &a {
            let num = *num as usize;
            for s in (num..sum).rev() {
                dp[s] |= dp[s - num] << 1;
            }
        }
        for s in 1..sum {
            if s * a.len() % sum == 0 {
                let k = s * a.len() / sum;
                if dp[s] & (1 << k) != 0 {
                    return true;
                }
            }
        }
        false
    }
}
```

or search for `len(part1)`.

```cpp
class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int sum = accumulate(A.begin(), A.end(), 0);
        if (sum == 0) return A.size() > 1;
        int len = A.size(), half = len / 2;

        bool possible = false;
        for (int k = 1; k <= half; k++)
            if (sum * k % len == 0) {
                possible = true; break;
            }
        if (!possible) return false;

        vector<unordered_set<int>> dp(half + 1);
        dp[0].insert(0);
        for (auto n : A)
            // Check backwards to avoid using the current number multiple times
            for (int k = half; k > 0; k--)
                for (auto s : dp[k - 1])
                    dp[k].insert(s + n);

        for (int k = 1; k <= half; k++)
            if (sum * k % len == 0 && dp[k].count(sum * k / len))
                return true;
        
        return false;
    }
};
```


2. ##### dfs search O((N/2)!)

```cpp
class Solution {
public:
    // vector<bool> visited;
    bool search(vector<int> & nums, int len, int target, int st) {
        if (len == 0) return target == 0;
        if (st == nums.size()) return false;
        // return if the target is too small
        if (target < len * nums[st]) return false;
        // break if left nums is less than need of the current number > target
        for (int i = st; i <= nums.size() - len && nums[i] <= target; i++) {
            if (i > st && nums[i] == nums[i - 1]) continue;
            if (search(nums, len - 1, target - nums[i], i + 1))
                return true;
        }
        return false;
    }
    bool splitArraySameAverage(vector<int>& A) {
        int sum = accumulate(A.begin(), A.end(), 0);
        if (sum == 0) return A.size() > 1;
        int len = A.size(), half = len / 2;

        bool possible = false;
        for (int k = 1; k <= half; k++)
            if (sum * k % len == 0) {
                possible = true; break;
            }
        if (!possible) return false;

        sort(A.begin(), A.end());
        for (int k = 1; k <= half; k++)
            if (sum * k % len == 0)
                if (search(A, k, (sum * k) / len, 0))
                    return true;

        return false;
    }
};
```