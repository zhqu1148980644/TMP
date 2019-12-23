#### Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

```
Example 1:

Input: 
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output: 
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]
Example 2:

Input: 
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output: 
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]
```

#### Follow up:

- A straight forward solution using O(mn) space is probably a bad idea.
- A simple improvement uses O(m + n) space, but still not the best solution.
- Could you devise a constant space solution?


#### Solutions

1. ##### use the first row and the first column as marker

- When ever meet an zero item ouside the first column/row, set the corresponding position in the first column/row to zero.
- To aoid confusion in whether the first column/row contain zeros, use two bool value to record this information.

```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        // check if the first column/row contain zeros.
        bool rzero = false, czero = false;
        if (matrix[0][0] == 0)
            rzero = czero = true;
        else {
            for (auto & num : matrix[0])
                if (num == 0) 
                { rzero = true; break; }
            for (int i = 1; i < matrix.size(); i++)
                if (matrix[i][0] == 0) 
                { czero = true; break; }
        }
        // check every item and record in the first column/row.
        for (int i = 1; i < matrix.size(); i++)
            for (int j = 1; j < matrix[0].size(); j++)
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
            }
        // seting columns/rows marked with zero to zero.
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[0].size(); j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
        }
        // set the first column/row to zero if necessary
        if (rzero)
            for (auto & num : matrix[0])
                num = 0;
        if (czero)
            for (int i = 0; i < matrix.size(); i++)
                matrix[i][0] = 0;
    }
};
```


Seems two messy.