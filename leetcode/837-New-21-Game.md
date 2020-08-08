Alice plays the following game, loosely based on the card game "21".

Alice starts with 0 points, and draws numbers while she has less than K points.  During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.  Each draw is independent and the outcomes have equal probabilities.

Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?

Example 1:

Input: N = 10, K = 1, W = 10
Output: 1.00000
Explanation:  Alice gets a single card, then stops.
Example 2:

Input: N = 6, K = 1, W = 10
Output: 0.60000
Explanation:  Alice gets a single card, then stops.
In 6 out of W = 10 possibilities, she is at or below N = 6 points.
Example 3:

Input: N = 21, K = 17, W = 10
Output: 0.73278
Note:

0 <= K <= N <= 10000
1 <= W <= 10000
Answers will be accepted as correct if they are within 10^-5 of the correct answer.
The judging time limit has been reduced for this question.

#### Solutions

1. ##### dynamic programming O(min(N, K + W))

- Borrowed from the official answer. Check for details.
- The main idea to to reversely compute the probability of ending with sum less/eq then `N`.
- `dp[i]` represents the probability of ending(with sum >= K) with sum less/eq then `N` when started with `i` points.
- `N = 21, K = 17, W = 10` as example:
    - `dp[K] = dp[K + 1] = .. dp[21] = 1`, as the sum is already >= K, no selection are permitted, the game ends with sum <= 21. Thus the prob is 1.
    - `dp[K - 1]`. Since the current points(K - 1 = 16) is smaller than end mark(`K = 17`), we can select numbers between `[1:W]` with the probability of selecting each number equals to `1 / W`, this leads to `dp[K - 1] = sum(dp[k] + .... + dp[K + W - 1]) / W`.
    - In general, `dp[i] = sum(dp[i + 1] + ... + dp[i + W]) / W`

```c++
class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) return 1;
        vector<double> dp(K + W);
        // sum equals to N is valid too
        for (int i = K; i <= N && i < K + W; i++)
            dp[i] = 1;
        // the computation of dp[i] and dp[i + 1] has overlapped elements and they differs only in the first/last element.
        // this for loop can be replaced with dp[k - 1] = min(N - K + 1, N) / W;
        for (int j = 0; j < W; j++)
            dp[K - 1] += dp[K + j] / W;
        for (int i = K - 2; i >= 0; i--)
            dp[i] += dp[i + 1] + dp[i + 1] / W - dp[i + W + 1] / W;

        return dp[0];
    }
};
```