---
title: Best Time to Buy and Sell Stock IV
date: 2021-01-04
---
#### Say you have an array for which the i-th element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

#### Note:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

```
Example 1:

Input: [2,4,1], k = 2
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: [3,2,6,5,0,3], k = 2
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
             Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
```


1. ##### dynamic programming

see problem 123


2. ##### priority queue and stack


- reference: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54118/C%2B%2B-Solution-with-O(n-%2B-klgn)-time-using-Max-Heap-and-Stack

- This problem can be seen as a special(constrained) case of problem 122 where we find all contiguous vally-peak pair then buy in valley and sell in peak, thus summing up all differences of vally-peak will get the answer. Since `k` is constrained, instead of picking all v-p pairs, only the highest `k` pairs can be selected.
- The key piont is to find all vp pairs, however, the number of transactions are limited, we may need to merge some vp_pairs into one transaction.
    - In the first case, as making one merged transaction has profit `p2 - v1` which is definitly smaller than single transaction with either `p1 - v1` or `p2 - v2` profit. Merging this two transactions into one transaction is meaningless(choose the largest between `p1 - v1` and `p2 - v2` is more suitable).
    - In the second case, though making two transactions has higher profit than the profit of merging them into one transaction(`p2 - v1`), when k is constrained and only `one` transaction is left, choosing the merged transaction is better than either one of two single transactions.
        -  To combine these two possible transactions, treat `p2 - v1` as one transaction and `p1 - v2` as the other. When two transactions are available, choose both `p2 - v1` and `p1 - v2`. When one transaction is available, choose `p2 - v1`: ie: the merged transaction.
```
The first case:  v2 <= v1
       .       .
 .    . .     .
  .  .   .   .
   .      . .
           .
   v1  p1  v2  p2

The second case: v2 > v1
            .
.      .   . 
 .    . . . 
  .  .   . 
   .      
  v1 p1 v2  p2
```

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int ret = 0;
        int n = prices.size();
        int v = 0;
        int p = 0;

        vector<int> profits;
        stack<pair<int, int>> vp_pairs;
        while (p < n) {
            for (v = p; (v < n - 1) && prices[v + 1] < prices[v]; v++);
            for (p = v + 1; (p < n) && prices[p] > prices[p - 1]; p++);
            // v1 < v0 < p1
            while (!vp_pairs.empty() && prices[v] < prices[vp_pairs.top().first]) {
                profits.push_back(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]);
                vp_pairs.pop();
            }
            // v0 < v1 < p1 < p2
            while (!vp_pairs.empty() && prices[p - 1] > prices[vp_pairs.top().second - 1]) {
                profits.push_back(prices[vp_pairs.top().second - 1] - prices[v]);
                v = vp_pairs.top().first;
                vp_pairs.pop();
            }
            vp_pairs.push(pair<int, int>(v, p));
        }

        while (!vp_pairs.empty()) {
            profits.push_back(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]);
            vp_pairs.pop();
        }
        if (k >= profits.size()) {
            ret = accumulate(profits.begin(), profits.end(), 0);
        } else {
            // items before `n - k` will be smaller or equal than `(n - k)'th` item(if in ordered).
            nth_element(profits.begin(), profits.begin() + profits.size() - k, profits.end());
            ret = accumulate(profits.begin() + profits.size() - k, profits.end(), 0);
        }
        return ret;
    }
};
```


3. #####

- reference: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/solution/yi-chong-ji-yu-wqs-er-fen-de-you-xiu-zuo-x36r/
- Needs to be Done