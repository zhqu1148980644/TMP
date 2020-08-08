A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.

Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?  (Each subgrid is contiguous).

 

Example 1:

Input: [[4,3,8,4],
        [9,5,1,9],
        [2,7,6,2]]
Output: 1
Explanation: 
The following subgrid is a 3 x 3 magic square:
438
951
276

while this one is not:
384
519
762

In total, there is only one magic square inside the given grid.
Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
0 <= grid[i][j] <= 15

#### Solutions

1. #### straight forward

- A magic square only conatains digits in `1-9` and without duplicates.

```c++
class Solution {
public:
    bool ismagic(array<int, 9> m) {
        int count[16] = {0};
        for (auto n : m)
            if (++count[n] > 1 || n > 9)
                return false;
        return m[0] + m[1] + m[2] == 15
            && m[3] + m[4] + m[5] == 15
            && m[6] + m[7] + m[8] == 15
            && m[0] + m[3] + m[6] == 15
            && m[1] + m[4] + m[7] == 15
            && m[2] + m[5] + m[8] == 15
            && m[0] + m[4] + m[8] == 15
            && m[2] + m[4] + m[6] == 15;
    }
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        if (grid.size() < 3 || grid[0].size() < 3)
            return 0;
        int m = grid.size(), n = grid[0].size();
        int res = 0;
        for (int i = 0; i <= m - 3; i++)
            for (int j = 0; j <= n - 3; j++) {
                if (grid[i + 1][j + 1] != 5)
                    continue;
                array<int, 9> v;
                int w = 0;
                for (int r = i; r < i + 3; r++)
                    for (int c = j; c < j + 3; c++)
                        v[w++] = grid[r][c];
                res += ismagic(v);
            }

        return res;
    }
};
```