We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.

#### Solutions

1. ##### greedy strategy

- Reverse all rows to make the first bit in each row to `1`.
    - `2 ^ n > 2^(n - 1) + 2^(n - 2) + ... 2^1`
- Then reversing `colums[1:]` to maximize the number of `1` in each column.

```c++
class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        if (!A.size()) return 0;
        int R = A.size(), C = A[0].size();
        int res = 0;
        for (int r = 0; r < R; r++)
            res +=  1 << (C - 1);  
        
        for (int c = 1; c < C; c++) {
            int num0 = 0;
            for (int r = 0; r < R; r++)
                num0 += A[r][c] ^ A[r][0];
            res += max(num0, R - num0) * (1 << (C - c - 1));
        }
        
        return res;
    }
};
```