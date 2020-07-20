A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
 

Example 1:

Input:
matrix = [
  [1,2,3,4],
  [5,1,2,3],
  [9,5,1,2]
]
Output: True
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.
Example 2:

Input:
matrix = [
  [1,2],
  [2,2]
]
Output: False
Explanation:
The diagonal "[1, 2]" has different elements.

Note:

matrix will be a 2D array of integers.
matrix will have a number of rows and columns in range [1, 20].
matrix[i][j] will be integers in range [0, 99].

Follow up:

What if the matrix is stored on disk, and the memory is limited such that you can only load at most one row of the matrix into the memory at once?
What if the matrix is so large that you can only load up a partial row into the memory at once?

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        if (!matrix.size()) return true;
        int m = matrix.size(), n = matrix[0].size();
        auto same = [&](int i, int j) {
            int origin = matrix[i++][j++];
            while (i < m && j < n) {
                if (matrix[i][j] != origin)
                    return false;
                i++; j++;
            }
            return true;
        };
        
        for (int j = 0; j < n; j++)
            if (!same(0, j)) return false;
        for (int i = 1; i < m; i++)
            if (!same(i, 0)) return false;
        return true;
    }
};
```

- or reverse the checking order

```c++
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        if (!matrix.size()) return false;
        int m = matrix.size(), n = matrix[0].size();

        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i - 1][j - 1] != matrix[i][j])
                    return false;
        return true;
    }
};
```


2. ##### row by row

- Solution for the first follow up

```c++
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        if (!matrix.size()) return false;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row;
        for (auto & v : matrix) {
            if (row.size()) {
                for (int i = 0; i < n - 1; i++)
                    if (row[i] != v[i + 1])
                        return false;
            }
            row =  move(v);
        }

        return true;
    }
};
```