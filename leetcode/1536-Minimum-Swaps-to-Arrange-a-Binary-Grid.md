Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

 

Example 1:


Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3
Example 2:


Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.
Example 3:


Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 200
grid[i][j] is 0 or 1

#### Solutions

1. ##### greedy

- Count the number of zeros in suffix of each rows
- Then starting from the first row, swap lower rows to make the current row has the minumum number of zeros it needed. If the current row already fits the requirements then just pass it.

```c++
class Solution {
public:
    int minswap(vector<int> & vzero) {
        int n = vzero.size(), res = 0;
        for (int i = 0; i < n; i++) {
            if (vzero[i] >= n - i - 1) continue;
            int j = i + 1;
            while (j < n && vzero[j] < n - i - 1) j++;
            if (j == n) return -1;
            while (j != i) {
                swap(vzero[j], vzero[j - 1]);
                res++;
                j--;
            }
        }
        return res;
    }
    int minSwaps(vector<vector<int>>& grid) {
        vector<int> vzero(grid.size());
        for (int i = 0; i < grid.size(); i++)
            for (int j = grid.size() - 1; j >= 0; j--)
                if (grid[i][j] == 0)
                    vzero[i]++;
                else break;
        return minswap(vzero);
    }
};
```