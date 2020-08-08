Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number N on the chalkboard.  On each player's turn, that player makes a move consisting of:

Choosing any x with 0 < x < N and N % x == 0.
Replacing the number N on the chalkboard with N - x.
Also, if a player cannot make a move, they lose the game.

Return True if and only if Alice wins the game, assuming both players play optimally.

 

Example 1:

Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.
Example 2:

Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.

#### Solutions

1. ##### math

- When the initial number is an even number, then he can choose 1, then the other player meet an odd number, since factors of odd numbers are odd numbers too, when he choose a odd numbers, the left number for the first player is an even number again, at last, the first player can always get 2(means he wins).


```c++
class Solution {
public:
    bool divisorGame(int N) {
        return  !(N & 1);
    }
};
```

2. ##### dynamic programming O(n2)

-  `dp[i]` represent if the first player woud win when he starts the game with number `i`.
- Check all possible factors, check if `cur - factor`'s state is loose, if this is true, then `dp[cur] = true`.

```c++
class Solution {
public:
    bool divisorGame(int N) {
        vector<int> dp(max(N + 1, 3));
        dp[1] = false; dp[2] = true;
        for (int i = 3; i <= N; i++)
            for (int j = 1; j < i; j++) {
                if (i % j == 0 && !dp[i - j]) {
                    dp[i] = true; break;
                }
            }
        return dp[N];
    }
};
```