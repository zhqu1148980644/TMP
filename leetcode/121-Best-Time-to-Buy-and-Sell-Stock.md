#### Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

#### Note that you cannot sell a stock before you buy one.

```
Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

#### Solutions

1. ##### Brute force O(n2)

- Traverse all buy-sell pairs and record the max profit.

```c++
int maxProfit(int * prices, int pricesSize) {
    int max = 0;
    for (int i = 0; i < pricesSize - 1; i++)
        for (int j = i + 1; j < pricesSize; j++)
            if (prices[j] - prices[i] > max):
                max = prices[j] - prices[i];
    return max;
}
```

2. ##### Staight forward O(n)

- Record the minimum price before each time point and upadte the maximum profit we can get when sell at that point when traversing each day.

```c++
int maxProfit(int* prices, int pricesSize){
    if (!pricesSize) return 0;
    int max = 0;
    int min = prices[0];
    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < min)
            min = prices[i];
        else if (prices[i] - min > max)
            max = prices[i] - min;
    }
    return max > 0 ? max : 0;
}

```

3. ##### maximum continues sum O(n)

- Convert prices of each day into the difference between this day's and the last day's prices.
- Then this problem equals to calculating the maximum continues sum problem(problem 53 Maximum subarray).


```c++
#define max(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int * prices, int pricesSize) {
    if (pricesSize <= 1) return 0;
    int max_p = 0, last = 0;
    for (int i = 1; i < pricesSize; i++) {
        int diff = prices[i] - prices[i - 1];
        last = max(last + diff, diff);
        max_p = max(max_p, last);
    }
    return max_p;
}
```

4. ##### Dynamic programming O(n)

See problem 123.