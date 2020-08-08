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
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        vector<int> dps(n, 0), dpc(n, 0);
        board[0][0] = '0'; dpc[0] = 1;
        
        for (int i = 0; i < n; i++) {
            // the diagonal of board[0][1] == 0.
            int diags = dps[0], diagc = i ? dpc[0] : 0;
            if (board[i][0] == 'X' || dpc[0] == 0)
                dps[0] = dpc[0] = 0;
            else
                dps[0] += board[i][0] - '0';
            for (int j = 1; j < n; j++) {
                int tmps = dps[j], tmpc = dpc[j];
                if (board[i][j] == 'X')
                    dps[j] = dpc[j] = 0;
                else {
                    // choose the maximum sum
                    int maxs = max(diags, max(dps[j - 1], dps[j]));
                    int curc = (diags == maxs) * diagc
                             + (dps[j - 1] == maxs) * dpc[j - 1]
                             + (dps[j] == maxs) * dpc[j];
                    curc %= 1000000007;
                    dps[j] = maxs + board[i][j] - '0'; dpc[j] = curc;
                }
                diags = tmps; diagc = tmpc;
            }
        }

        if (dpc[n - 1] > 0)
            return {dps[n - 1] - ('S' - '0'), dpc[n - 1]};
        else
            return {0, 0};

    }
};
```

2. ##### dfs