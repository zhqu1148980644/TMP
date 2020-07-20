Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

#### Note:

-    You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
-    0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

```
Example:

Input: [3,1,5,8]
Output: 167 
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
```

#### Solutions

1. ##### backtrack/dfs


```c++


```

2. ##### dynamic programming O(n3)

- In order to devide the problem into subproblems, all subproblems should be independent to each other.
- We can choose one of ballon to partition the problem into two subproblems, to make these two problems independent, we should keep this splitting ballon intact(not bursted) utill two subproblems are solved.
    - If the middle ballon is bursted before these two subproblems are solved, the score we can get by bursting ballons in the left part will depend on the bursting order of balloons in the right part. (The same for balloons in the right part).
- Thus, for each possible splitting ballon, we keep this ballon and two boundary ballons unbroken.


```c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int j = 2; j < n; j++) {
            for (int i = j - 2; i >= 0; i--) {
                for (int k = i + 1; k < j; k++)
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]);
            }
        }

        return dp[0][n - 1];
    }
};
```


- Recursive version with memoization.

```c++
class Solution {
public:
    vector<vector<int>> memo;
    int solve(vector<int> & nums, int i, int j) {
        if (memo[i][j] || j - i < 2)
            return memo[i][j];
        int maxscore = 0;
        for (int k = i + 1; k < j; k++)
            maxscore = max(maxscore, solve(nums, i, k) + solve(nums, k, j) + nums[i] * nums[k] * nums[j]);

        return memo[i][j] = maxscore;
    }
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        memo = vector<vector<int>>(n, vector<int>(n));
        return solve(nums, 0, n - 1);
    }
};
```

