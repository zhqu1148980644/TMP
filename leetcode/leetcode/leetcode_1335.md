---
title: Minimum Difficulty of a Job Schedule
date: 2021-01-04
---
You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.

Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

 

```
Example 1:

Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7 

Example 2:

Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.

Example 3:

Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.

Example 4:

Input: jobDifficulty = [7,1,7,1,7,1], d = 3
Output: 15

Example 5:

Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
Output: 843
```

 

#### Constraints:

-    1 <= jobDifficulty.length <= 300
-    0 <= jobDifficulty[i] <= 1000
-    1 <= d <= 10


#### Solutions

1. ##### dynamic programming O(n3)

- `dp[i][d]` represents we have finished `jobs[:i]` at the end of `day[d]`.
- `dp[i][d] = min(dp[i][d], d[k][d - 1] + maxdifficulty(k + 1, i))` means finished `i - k` jobs at day `d` and `k` jobs at the end of day `d - 1`

```cpp
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        if (jobDifficulty.size() < d) return -1;
        int n = jobDifficulty.size(), day = d;
        vector<vector<int>> dp(n, vector<int>(d, INT_MAX));
        dp[0][0] = jobDifficulty[0];
        for (int i = 1; i < n; i++)
            dp[i][0] = max(dp[i - 1][0], jobDifficulty[i]);
        
        for (int d = 1; d < day; d++) {
            // each day must finish at least one job
            for (int jobi = d; jobi < n; jobi++) {
                int maxd = INT_MIN;
                // each day must finish at least one job
                for (int prevjobi = jobi - 1; prevjobi >= d - 1; prevjobi--) {
                    maxd = max(jobDifficulty[prevjobi + 1], maxd);
                    dp[jobi][d] = min(dp[jobi][d], dp[prevjobi][d - 1] + maxd);
                }
            }
        }

        return dp[n - 1][d - 1];
    }
};
```