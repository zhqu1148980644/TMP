In a country popular for train travel, you have planned some train travelling one year in advance.  The days of the year that you will travel is given as an array days.  Each day is an integer from 1 to 365.

#### Train tickets are sold in 3 different ways:

-    a 1-day pass is sold for costs[0] dollars;
-    a 7-day pass is sold for costs[1] dollars;
-    a 30-day pass is sold for costs[2] dollars.

The passes allow that many days of consecutive travel.  For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

Return the minimum number of dollars you need to travel every day in the given list of days.

 

```
Example 1:

Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation: 
For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total you spent $11 and covered all the days of your travel.

Example 2:

Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation: 
For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total you spent $17 and covered all the days of your travel.
```

 

#### Note:

-    1 <= days.length <= 365
-    1 <= days[i] <= 365
-    days is in strictly increasing order.
-    costs.length == 3
-    1 <= costs[i] <= 1000


#### Solutions

1. ##### dynamic programming O(3 * 365)

- `dp[i]` represents the minimum cost when traveled in `days[i]`

```c++
class Solution {
public:
    vector<int> memo, plans;
    int mincost(vector<int> & costs, int day) {
        if (day < 1) return 0;
        if (memo[day] != INT_MAX) return memo[day];
        if (!plans[day])
            return mincost(costs, day - 1);
        int min1 = costs[0] + mincost(costs, day - 1);
        int min7 = costs[1] + mincost(costs, day - 7);
        int min30 = costs[2] + mincost(costs, day - 30);
        return memo[day] = min(min1, min(min7, min30));
    }
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        plans = vector<int>(366, false);
        memo = vector<int>(366, INT_MAX);
        for (auto d : days)
            plans[d] = true;
        return mincost(costs, 365);
    }
};
```

- Iterative version

```c++
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> plans(366, false), dp(366, INT_MAX);
        for (auto d : days)
            plans[d] = true;

        dp[0] = 0;
        for (int d = 1; d < 366; d++) {
            if (!plans[d])
                dp[d] = dp[d - 1];
            else {
                int min1 = costs[0] + dp[d - 1];
                int min7 = costs[1] + (d - 7 >= 0 ? dp[d - 7] : 0);
                int min30 = costs[2] + (d - 30 >= 0 ? dp[d - 30] : 0);
                dp[d] = min(min1, min(min7, min30));
            }
        }
        return dp[365];
    }
};
```


or


```c++
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> dp(396, 0);
        vector<bool> plans(396, false);
        for (auto & day : days)
            plans[day + 30] = true;
        for (int i = 30; i < 396; i++) {
            if (!plans[i])
                dp[i] = dp[i - 1];
            else {
                int cost1 = costs[0] + dp[i - 1];
                int cost7 =  costs[1] + dp[i - 7];
                int cost30 = costs[2] + dp[i - 30];
                dp[i] = min(cost1, min(cost7, cost30));
            }
        }

        return dp[395];
    }
};
```