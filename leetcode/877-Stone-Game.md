Alex and Lee play a game with piles of stones.  There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].

The objective of the game is to end with the most stones.  The total number of stones is odd, so there are no ties.

Alex and Lee take turns, with Alex starting first.  Each turn, a player takes the entire pile of stones from either the beginning or the end of the row.  This continues until there are no more piles left, at which point the person with the most stones wins.

Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.

 

Example 1:

Input: [5,3,4,5]
Output: true
Explanation: 
Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10 points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we return true.
 

Note:

2 <= piles.length <= 500
piles.length is even.
1 <= piles[i] <= 500
sum(piles) is odd.

#### Solutions

1. ##### dfs with memoization O(n2)

```c++
class Solution {
public:
    vector<vector<int>> memo;
    int play(vector<int> & piles, int i, int j) {
        if (memo[i][j] != INT_MAX) return memo[i][j];
        if (i == j) return memo[i][j] = 1;
        return memo[i][j] = max(
            piles[i] - play(piles, i + 1, j), 
            piles[j] - play(piles, i, j - 1)
        );
    }
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        memo = vector<vector<int>>(n, vector<int>(n, INT_MAX));
        return play(piles, 0, piles.size() - 1) > 0;
    }
};
```

2. ##### dynamic programming O(n2)

```c++
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<int> dp(piles);

        for (int j = 0; j < n; j++)
            for (int i = j - 1; i >= 0; i--)
                dp[i] = max(piles[i] - dp[i + 1], piles[j] - dp[j]);

        return dp[n - 1];
    }
};
```

3. ##### math

- why?
- `piles.lengh == even`, then the first player always win.

```rust
impl Solution {
    pub fn stone_game(piles: Vec<i32>) -> bool {
        return true;
    }
}
```