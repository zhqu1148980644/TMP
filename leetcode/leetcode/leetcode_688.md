---
title: Knight Probability in Chessboar
date: 2021-01-04
---
On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

 

 

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly K moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.

 

```
Example:

Input: 3, 2, 0, 0
Output: 0.0625
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
```

 

#### Note:

-    N will be between 1 and 25.
-    K will be between 0 and 100.
-    The knight always initially starts on the board.


#### Solutions

1. ##### dynamic programming O(k * n2) S(n2)

- Similar to problem 576, we firstly count the number of unique pairs within the board after k moves, then the probability of staying on the board equals to `numpath / 8 ** k`.

```cpp
typedef long long ll;
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<double>> dp(N, vector<double>(N));
        int dirs[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
                          {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
        dp[r][c] = 1;
        for (int k = 1; k <= K; k++) {
            vector<vector<double>> dp1(N, vector<double>(N));
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (auto & d : dirs) {
                        int nx = i + d[0], ny = j + d[1];
                        if (!(nx < 0 || ny < 0 || nx >= N || ny >= N))
                            dp1[nx][ny] += dp[i][j];
                    }
            dp = move(dp1);
        }

        double count = 0;
        for (auto & v : dp)
            for (auto & n : v)
                count += n;
        
        return count / pow(8, K);
    }
};
```

or

```cpp
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<double>> dp(N, vector<double>(N));
        int dirs[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};

        dp[r][c] = 1;
        for (int k = 1; k <= K; k++) {
            vector<vector<double>> dp1(N, vector<double>(N));
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (auto & d : dirs) {
                        int nx = i + d[0], ny = j + d[1];
                        if (!(nx < 0 || ny < 0 || nx >= N || ny >= N))
                            dp1[nx][ny] += dp[i][j] / 8;
                    }
            dp = move(dp1);
        }

        double res = 0;
        for (auto & v : dp)
            for (auto n : v)
                res += n;
        
        return res;
    }
};
```

- Like problem 576, we can thought of this problem in a reversed perspective. ie: starting from any point within the board and arrived the given points after k steps.

```cpp
class Solution {
public:
    vector<vector<vector<double>>> dp;
    int N;
    double solve(int k, int r, int c) {
        // already outside of the board
        if (r < 0 || c < 0 || r >= N || c >= N)
            return 0;
        // No steps left, The probability of staying within the board after 0 steps is 1
        if (k <= 0) return 1;
        if (dp[r][c][k]) return dp[r][c][k];
        double prob = solve(k - 1, r - 2, c - 1)
                    + solve(k - 1, r - 1, c - 2)
                    + solve(k - 1, r + 1, c - 2)
                    + solve(k - 1, r + 2, c - 1)
                    + solve(k - 1, r + 2, c + 1)
                    + solve(k - 1, r + 1, c + 2)
                    + solve(k - 1, r - 1, c + 2)
                    + solve(k - 1, r - 2, c + 1);
            
        return dp[r][c][k] = prob / 8;
    }
    double knightProbability(int N, int K, int r, int c) {
        this->N = N;
        dp = vector<vector<vector<double>>>(N, vector<vector<double>>(N, vector<double>(K + 1)));
        return solve(K, r, c);
    }
};
```


2. ##### matrix power