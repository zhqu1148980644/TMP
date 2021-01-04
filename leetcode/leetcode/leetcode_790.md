---
title: Domino and Tromino Tiling
date: 2021-01-04
---
We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.

XX  <- domino

XX  <- "L" tromino
X
Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.

(In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)

Example:
Input: 3
Output: 5
Explanation: 
The five different ways are listed below, different letters indicates different tiles:
XYZ XXZ XYY XXY XYY
XYZ YYZ XZZ XYY XXY
Note:

N  will be in range [1, 1000].

#### Solutions

1. ##### dynamic programming

- Note that every square must be covered by a tile.
- `dp[i][state]` represents the states of the i'th column

```
dp[i][0b00] comes from
10   ->   10
10        10

dp[i][0b10]/dp[i][0b01] comes from
00   ->  11       00   ->  11
00       10       10       10


dp[i][0b11] comes from
00   ->  11          10   ->  11        00   ->  11          10   ->  11
00       11          00       11        10       11          10       11

```

```cpp
class Solution {
public:
    int numTilings(int N) {
        const int MOD = 1e9 + 7;
        long dp[4] = {1, 0, 0 , 1};
        for (int i = 2; i <= N; i++) {
            long dp1[4];
            dp1[0b00] = dp[0b11] % MOD;
            dp1[0b10] = (dp[0b00] + dp[0b01]) % MOD;
            dp1[0b01] = (dp[0b00] + dp[0b10]) % MOD;
            dp1[0b11] = (dp[0b01] + dp[0b10] + dp[0b11] + dp[0b00]) % MOD;
            swap(dp, dp1);
        }
        return dp[0b11];
    }
};
```


2. ##### fast power

```
[[0, 0, 0, 1], ^ (N -1)  *  [1
 [1, 0, 1, 0],              0   
 [1, 1, 0, 0],              0
 [1, 1, 1, 1]]              1]
 

```

```cpp
class Solution {
public:
    const int MOD = 1e9 + 7;
    using Col = vector<long>;
    using Matrix = vector<vector<long>>;
    Matrix multiply(const Matrix & m1, const Matrix & m2) {
        Matrix res(m1.size(), Col(m2[0].size()));
        for (int i = 0; i < res.size(); i++)
            for (int j = 0; j < res[0].size(); j++)
                for (int k = 0; k < m1[0].size(); k++) {
                    res[i][j] += m1[i][k] * m2[k][j];
                    res[i][j] %= MOD;
                }
        return res;
    }
    Matrix power(const Matrix & m, int n) {
        if (n == 1) return m;
        auto half = power(m, n >> 1);
        return n & 1 ? multiply(multiply(half, half), m) : multiply(half, half);
    }
    int numTilings(int N) {
        Matrix trans = {{0, 0, 0, 1}, {1, 0, 1, 0}, {1, 1, 0, 0}, {1, 1, 1, 1}};
        Matrix state = {{1}, {0}, {0}, {1}};
        return N >= 2 ? multiply(power(trans, N - 1), state)[3][0] : state[3][0];;
    }
};
```

or

```cpp
class Solution {
public:
    const int MOD = 1e9 + 7;
    template <typename T, size_t r1, size_t c1, size_t r2, size_t c2>
    auto multiply(const array<array<T, c1>, r1> & m1, 
                  const array<array<T, c2>, r2> & m2) {
        // must initialize to zero
        array<array<T, c2>, r1> res; res.fill({});
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c2; j++)
                for (int k = 0; k < c1; k++) {
                    res[i][j] += m1[i][k] * m2[k][j];
                    res[i][j] %= MOD;
                }
        return res;
    }
    template <typename Matrix>
    Matrix power(const Matrix & m, int n) {
        if (n == 1) return m;
        auto half = power(m, n >> 1);
        return n & 1 ? multiply(multiply(half, half), m) : multiply(half, half);
    }
    int numTilings(int N) {
        array<array<long, 4>, 4> trans {{{0, 0, 0, 1}, {1, 0, 1, 0}, {1, 1, 0, 0}, {1, 1, 1, 1}}};
        array<array<long, 1>, 4> state = {{{1}, {0}, {0}, {1}}};
        return N >= 2 ? multiply(power(trans, N - 1), state)[3][0] : state[3][0];;
    }
};
```