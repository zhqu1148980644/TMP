---
title: Number of Music Playlists
date: 2021-01-04
---
Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  You create a playlist so that:

Every song is played at least once
A song can only be played again only if K other songs have been played
Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.

 

Example 1:

Input: N = 3, L = 3, K = 1
Output: 6
Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].
Example 2:

Input: N = 2, L = 3, K = 0
Output: 6
Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2]
Example 3:

Input: N = 2, L = 3, K = 1
Output: 2
Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2]
 

Note:

0 <= K < N <= L <= 100

#### Solutions

1. ##### dynamic programming

- from the official answer
- `dp[i][j]` represents the number of play lists with length of `i` and contains `j` unique songs.
```cpp
class Solution {
public:
    int numMusicPlaylists(int N, int L, int K) {
        vector<vector<long>> dp(L + 1, vector<long>(N + 1));
        dp[0][0] = 1;
        long mod = 1e9 + 7;
        for (int i = 1; i <= L; i++)
            for (int j = 1; j <= N; j++) {
                // choose a new song
                dp[i][j] += dp[i - 1][j - 1] * (N - j + 1);
                // choose an already existing song, their are `j - K` possibilities.
                dp[i][j] += dp[i - 1][j] * max(j - K, 0);
                dp[i][j] %= mod;
            }
        
        return dp[L][N];
    }
};
```