We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime , endTime and profit arrays, you need to output the maximum profit you can take such that there are no 2 jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

 

Example 1:



Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job. 
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
Example 2:




Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job. 
Profit obtained 150 = 20 + 70 + 60.
Example 3:



Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6
 

Constraints:

1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
1 <= startTime[i] < endTime[i] <= 10^9
1 <= profit[i] <= 10^4

##### Solutions

1. ##### dynamic programming with binary search

- `dp[i]` represents the maximum profit can be achieved in the `range[:finish[i]]`
    - `dp[i] = max(profit[i] + dp[prevexclude], dp[i - 1])`

```c++
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> vs;
        for (int i = 0; i <  n; i++)
            vs.push_back({startTime[i], endTime[i], profit[i]});
        // sort by finish time
        sort(vs.begin(), vs.end(), [](auto & v1, auto & v2) {
            return v1[1] < v2[1];
        });

        int res = 0;
        vector<int> dp(n), target = {INT_MAX, 0, INT_MAX};
        res = max(res, dp[0] = vs[0][2]);
        for (int j = 1; j < n; j++) {
            dp[j] = vs[j][2];
            target[1] = vs[j][0];
            // find the nearest excluded job range in the left
            auto find = upper_bound(vs.begin(), vs.end(), target, 
            [&](auto & v1, auto & v2) { return  v1[1] < v2[1]; });
            if (find != vs.begin())
                dp[j] += dp[find - vs.begin() - 1];
            // choose the maximum one
            dp[j] = max(dp[j - 1], dp[j]);
            res = max(dp[j], res);
        }

        return res;
    }
};
```


or

```c++
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<int> index(n); iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i1, int i2) {
            return endTime[i1] < endTime[i2];
        });

        int res = 0;
        vector<int> dp(n), ends(n, INT_MAX);
        for (int j = 0; j < n; j++) {
            int st = startTime[index[j]], ed = endTime[index[j]];
            dp[j] = profit[index[j]];
            auto i = upper_bound(ends.begin(), ends.begin() + j, st) - ends.begin();
            if (i != 0) dp[j] += dp[i - 1];
            ends[j] = ed;
            dp[j] = max(dp[j], j ? dp[j - 1] : 0);
            res = max(res, dp[j]);
        }

        return res;
    }
};
```