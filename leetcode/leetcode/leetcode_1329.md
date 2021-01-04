---
title: Sort the Matrix Diagonally
date: 2021-01-04
---
Given a m * n matrix mat of integers, sort it diagonally in ascending order from the top-left to the bottom-right then return the sorted array.



```
Example 1:

Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
```


#### Constraints:

-    m == mat.length
-    n == mat[i].length
-    1 <= m, n <= 100
-    1 <= mat[i][j] <= 100


#### Solutions

1. ##### straight forward

- Sort each diagonal in a temporary array.

```cpp

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        if (!mat.size() || !mat[0].size()) return {{}};
        int m = mat.size(), n = mat[0].size();
        for (int c = 0; c < n; c++) {
            vector<int> tmp;
            for (int i = 0, j = c; i < m && j < n; i++, j++)
                tmp.push_back(mat[i][j]);
            sort(tmp.begin(), tmp.end());
            int k = 0;
            for (int i = 0, j = c; i < m && j < n; i++, j++)
                mat[i][j] = tmp[k++];
            
        }
        
        for (int r = 0; r < m; r++) {
            vector<int> tmp;
            for (int j = 0, i = r; i < m && j < n; i++, j++)
                tmp.push_back(mat[i][j]);
            sort(tmp.begin(), tmp.end());
            int k = 0;
            for (int j = 0, i = r; i < m && j < n; i++, j++)
                mat[i][j] = tmp[k++];
        }
        
        return mat;
    }
};
```

- A python version
- borrowed from others

```python
class Solution:
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:
        from collections import defaultdict
        m, n, diags = len(mat), len(mat[0]), defaultdict(list)
        for i, j in itertools.product(range(m), range(n)):
            diags[i - j].append(mat[i][j])
        diags = {dis : iter(sorted(array)) 
                for dis, array in diags.items()}
        for i, j in itertools.product(range(m), range(n)):
            mat[i][j] = next(diags[i - j])
        
        return mat
```

2. ##### inplace

```cpp


```