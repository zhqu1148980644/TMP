
#### Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

#### Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

```
Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

#### Soltuions

- reference: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/solution/yi-ge-tong-yong-fang-fa-tuan-mie-6-dao-gu-piao-w-5/

- As the problem becomes more and more complicate(more states), the answer can not be directly figured out by some trick used in problem 121 122. We need a more generic and systematic way to solve this kind of problem. i.e. dynamic programming.

- The maximum objective value can be achieved in a certain state is based on this state's last possible states(many), therefor to getto the target state we need to iterate over all possible state which can be seen as filling a 3d dp table where `dp[i][k][0]` represetns in the `i'th` day, `k` transactions are made, and `no` stock in hand.
- This dependency can be formulated as:
    - Since there are only two possible values in the third variable, we can easily list these two situations.
    - For a certain state, the number of possible former states are limited by the rules, otherwise any state can be converted to this state(most dp problems carry implicit rules.).
    - `dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + p[i])`
    - `dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - p[i])`
- The target state:
    - `dp[i - 1][k][0]`.  `dp[i - 1][k][1]` is definitely smaller.
- Base states: 
    - when filling the table, base state are not required to be filled.
    - `dp[-1][k][0] = dp[i][0][0] = 0`
    - `dp[-1][k][1] = dp[i][0][1] = -infinity` means impossible.

1. ##### problem 121

- `k = 1`. only `dp[i][1][0/1]` needs to be filled.
    - `dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + p[i])`
    - `dp[i][1][1] = max(dp[i - 1][1][1], d[i - 1][0][0] - p[i])`
        - Since `dp[i - 1][0][0]` equals 0, `k` will not be changed during the calculation.
        - Thus the 3d dp table can be replaced by a 2d table.

- More concise formulas are:
    - `dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + p[i])`
    - `dp[i][1][1] = max(dp[i - 1][1][1], -p[i])`

- Since `dp[i]` depends solely on `dp[i - 1]`, we can simply use two variales to represent `dp[i - 1][0]` and `dp[i - 1][1]` to save O(n) space which is supposed to be costed by dp table.

```c++
#define max(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int *prices, int pricesSize) {
    int last0 = 0, last1 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        last0 = max(last0, last1 + prices[i]);
        last1 = max(last1, -prices[i]);
    }
    return last0;
}
```

2. ##### problem 122

- `k = +infinity` means `k` doesn't affect the calculation of recursive formulas showed above(k - 1 == k).
    - `dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + p[i])`
    - `dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p[i])`

```c++
#define max(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int* prices, int pricesSize){
    int last0 = 0, last1 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        int tmp = last0;
        last0 = max(last0, last1 + prices[i]);
        last1 = max(last1, tmp - prices[i]);
    }
    return last0;
}
```

3. #### problem 309

- `k = +infinity` with cooldown: 1day
    - `dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + p[i])`
    - `dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - p[i])`

```c++

#define max(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int* prices, int pricesSize){
    int last0 = 0, last1 = INT_MIN, llast0 = 0;
    for (int i = 0; i < pricesSize; i++) {
        int tmp = last0;
        last0 = max(last0, last1 + prices[i]);
        last1 = max(last1, llast0 - prices[i]);
        llast0 = tmp;
    }
    return last0;
}
```

4. ##### problem 714


- `k = +infinity` with fee
    - `dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + p[i])`
    - `dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p[i]) - fee`

```c++
#define max(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int* prices, int pricesSize, int fee){
    int last0 = 0, last1 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        int tmp = last0;
        last0 = max(last0, last1 + prices[i]);
        last1 = max(last1, tmp - prices[i] - fee);
    }
    return last0;
}
```

5. ##### current problem: problem 123

- `k = 2`
    - `dp[i][2][0] = max(dp[i - 1][2][0], dp[i - 1][2][1] + p[i])`
    - `dp[i][2][1] = max(dp[i - 1][2][1], dp[i - 1][1][0] - p[i])`
    - `dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + p[i])`
    - `dp[i][1][1] = max(dp[i - 1][1][1], - p[i])`

```c++
#define max(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int* prices, int pricesSize){
    int last10 = 0, last11 = INT_MIN;
    int last20 = 0, last21 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        int tmp = last10;
        last10 = max(last10, last11 + prices[i]);
        last11 = max(last11, -prices[i]);
        last20 = max(last20, last21 + prices[i]);
        last21 = max(last21, tmp - prices[i]);
    }
    return last20;
}
```

6. ##### problem 188

- `k = n`
- Only one loop are used in former example because k are ignored when filling the tale. `k` in this problem cannot be ignored anymore, so a additional for loop will be used to iterate dimension `k`.

```c++
#define max(x, y) ((x) > (y) ? x : y)
int maxProfit(int k, int* prices, int pricesSize){
    if (!pricesSize) return 0;
    int size = pricesSize;
    if (k > (size / 2)) {
        int sum = 0, dif;
        while (--size) {
            dif = prices[size] - prices[size - 1];
            if (dif > 0) sum += dif;
        }
        return sum;
    }
    k += 1;
    int last0[k], last1[k], prelast0;
    size = k;
    while (size--) {
        last0[size] = 0;
        last1[size] = -prices[0];
    }
    last1[0] = INT_MIN;
    for (int i = 1; i < pricesSize; i++) {
        prelast0 = last0[0];
        for (int j = 1; j < k; j++) {
            int tmp = last0[j];
            last0[j] = max(last0[j], last1[j] + prices[i]); 
            last1[j] = max(last1[j], prelast0 - prices[i]);
            prelast0 = tmp;
        }
    }
    return last0[k - 1];
}
```

We used a `prelast0` variable to store the previous last0 which is overrittend in the last step of the loop. Looping from `k to 1` can save this work.

```c++

#define max(x, y) ((x) > (y) ? x : y)
int maxProfit(int k, int* prices, int pricesSize){
    if (!pricesSize) return 0;
    int size = pricesSize;
    if (k > (size / 2)) {
        int sum = 0, dif;
        while (--size) {
            dif = prices[size] - prices[size - 1];
            if (dif > 0) sum += dif;
        }
        return sum;
    }
    k += 1;
    int last0[k], last1[k];
    size = k;
    while (size--) {
        last0[size] = 0;
        last1[size] = -prices[0];
    }
    last1[0] = INT_MIN;
    for (int i = 1; i < pricesSize; i++) {
        int cur = prices[i];
        for (int j = k - 1; j > 0; j--) {
            last0[j] = max(last0[j], last1[j] + cur); 
            last1[j] = max(last1[j], last0[j - 1] - cur);
        }
    }
    return last0[k - 1];
}
```