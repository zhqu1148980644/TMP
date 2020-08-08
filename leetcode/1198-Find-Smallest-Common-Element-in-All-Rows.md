Given a matrix mat where every row is sorted in strictly increasing order, return the smallest common element in all rows.

If there is no common element, return -1.

 

Example 1:

Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
Output: 5
 

Constraints:

1 <= mat.length, mat[i].length <= 500
1 <= mat[i][j] <= 10^4
mat[i] is sorted in strictly increasing order.

#### Solutions

1. ##### binary search

- For each element in the first row, search in other rows using binary search to check if the current element exists.

```c++
class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        for (int j = 0; j < n; j++) {
            int cur = mat[0][j];
            bool found = true;
            for (int i = 1; i < m; i++) {
                auto it = lower_bound(mat[i].begin(), mat[i].end(), cur);
                if (it == mat[i].end() || *it != cur) {
                    found = false; break;
                }
            }
            if (found) return cur;
        }

        return -1;
    }
};
```