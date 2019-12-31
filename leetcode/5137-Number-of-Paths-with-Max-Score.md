#### You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.

You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

In case there is no path, return [0, 0].

 

```
Example 1:

Input: board = ["E23","2X2","12S"]
Output: [7,1]
Example 2:

Input: board = ["E12","1X1","21S"]
Output: [4,2]
Example 3:

Input: board = ["E11","XXX","11S"]
Output: [0,0]
```
 

#### Constraints:

- 2 <= board.length == board[i].length <= 100

#### Solutions

1. ##### dynamic programming

```c++
struct Info {
    int score;
    int count;
    Info(int score = 0, int count = 0) : score(score) , count(count) {}
};

#define forbid(x, y) (board[x][y] == 'X')
#define score(x, y) (board[x][y] - '0')
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int nrow = board.size();
        int ncol = board[0].size();
        if (!nrow || !ncol) return {0, 0};
        vector<Info> dp(ncol, Info(0, 0));
        dp[0] = Info(0, 1);
        Info prel, left, up;

        for (int j = 1; j < ncol; j++)
            if (!(forbid(0, j) || !dp[j - 1].count))
                (dp[j] = dp[j - 1]).score += score(0, j);

        for (int i = 1; i < nrow; i++) {
            prel = dp[0];
            if (!(forbid(i, 0) || !dp[0].count))
                dp[0].score += score(i, 0);
            else
                dp[0] = Info(0, 0);

            for (int j = 1; j < ncol; j++) {
                up = dp[j];
                left = dp[j - 1];
                int maxcount = max(prel.count, max(up.count, left.count));
                int maxscore = max(prel.score, max(up.score, left.score));
                if (maxcount > 0 && !forbid(i, j)) {
                    int count = 0;
                    if (prel.score == maxscore)
                        count += prel.count;
                    if (up.score == maxscore)
                        count += up.count;
                    if (left.score == maxscore)
                        count += left.count;
                    if (count > 1000000007)
                        count %= 1000000007;
                    dp[j] = Info(maxscore + score(i, j), count);
                }  else {
                    dp[j] = Info(0, 0);
                }
                prel = up;
            }
        }

        if (dp[ncol - 1].count > 0) {
            return {dp[ncol - 1].score - ('S' - '0'), dp[ncol - 1].count};
        } else
            return {0, 0};
    }
};
```

2. ##### dfs