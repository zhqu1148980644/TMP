You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

```
Example 1:

Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.
```

#### Note:

-    The length of the given array is positive and will not exceed 20.
-    The sum of elements in the given array will not exceed 1000.
-    Your output answer is guaranteed to be fitted in a 32-bit integer.


#### Solutions

1. ##### dfs O(2**n)

```c++
class Solution {
public:
    int count = 0;
    void dfs(vector<int> & nums, int i, int sum, int target) {
        if (i < nums.size()) {
            dfs(nums, i + 1, sum + nums[i], target);
            dfs(nums, i + 1, sum - nums[i], target);
        }
        else if (sum == target)
            count++;
    }
    int findTargetSumWays(vector<int>& nums, int S) {
        dfs(nums, 0, 0, S);
        return count;
    }
};
```


2. ##### 01 knapsack problem O(n * w)  w: the target sum weight

- Denote `P` as the sum of numbers with positive signs in nums and `N` the sum of numbers with negative signs. 
- This problem is equal to find `P` and `N` such that `P - N = target`.
    - -> `P - N + P + N = target + P + N`
    - -> `2P = target + P + N`
    - -> `2P = target + sum`
    - -> `P = (target + sum) / 2`
- Thus we need to count the number of solutions that satisfy `P = (target + sum) / 2` which is similar to 01 knapsack problem.
- `dp[w]` represents the number of solutions with sum weight of `w`.

```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        long sum = 0;
        for (auto & n : nums)
            sum += n;
        if (((sum + S) % 2) != 0 || S > sum)
            return 0;
        long target = (sum + S) / 2;

        vector<long> dp(target + 1);
        // the number of olutions with sum equal to 0 is 1.
        dp[0] = 1;
        for (auto & cur : nums) {
            for (int w = target; w >= cur; w--)
                // dp[cur_i][w] = dp[cur_i - 1][w] + dp[cur_i - 1][w - cur]
                dp[w] += dp[w - cur];
        }

        return dp[target];
    }
};
```

3. ##### dynamic programming

- `dp[i][w]` represents the number of solutions uses `nums[:i]` with sum of `w`.
- Since the sum may be `negative`, all sums are increased by `1000`.


```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        if (S > 1000)
            return 0;
        vector<int> dp(2001);
        // dp[-1][0] = 1, no numbers included. The number of solutions with sum 0 is 1.
        dp[0 + 1000] = 1;

        for (int i = 0; i < nums.size(); i++) {
            vector<int> dp1(2001);
            for (int sum = -1000; sum <= 1000; sum++)
                if (dp[sum + 1000] > 0) {
                    dp1[sum - nums[i] + 1000] += dp[sum + 1000];
                    dp1[sum + nums[i] + 1000] += dp[sum + 1000];
                }
            dp = dp1;
        }

        return dp[S + 1000];
    }
};
```