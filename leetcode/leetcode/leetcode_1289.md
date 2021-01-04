---
title: Minimum Falling Path Sum II
date: 2021-01-04
---
#### Given a square grid of integers arr, a falling path with non-zero shifts is a choice of exactly one element from each row of arr, such that no two elements chosen in adjacent rows are in the same column.

Return the minimum sum of a falling path with non-zero shifts.

 

```
Example 1:

Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation: 
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.
```
 

#### Constraints:

- 1 <= arr.length == arr[i].length <= 200
- -99 <= arr[i][j] <= 99


#### Solutions

1. ##### dynamic programming O(n2)

- As no two elements chosen in adjacent rows are in the same column, we need to choose the smallest value(excluded the same column) in the last row. This additional step will increase the complexity of dp problem to `O(n3)`.
- Actually, iteratively exlcuding the same column and finding the smallest value is redundant, only the `minimum` number and the `second minimum` number are needed.
    - If the number in the same column in the last row is the minimum, then the second minimum is what we need.

```cpp
class Solution {
private:
    int rowmin(int * row, int length, int exclude) {
        int mini = 0;
        for (int i = 1; i < length; i++)
            if (i != exclude)
                // the first item may be the excluded item;
                if (row[i] < row[mini] || mini == exclude)
                    mini = i;
        return mini;
    }
public:
    int minFallingPathSum(vector<vector<int>> & arr) {
        int ncol = arr[0].size();
        int * last = new int[ncol];
        int * cur = new int[ncol];
        for (int i = 0; i< ncol; i++) last[i] = 0;
        for (int i = 0; i < arr.size(); i++) {
            int mini = rowmin(last, ncol, -1);
            int minini = rowmin(cur, ncol, mini);
            for (int j = 0; j < ncol; j++)
                cur[j] = arr[i][j] + ((j == mini) ? last[minini] : last[mini]);
            swap(last, cur);
        }
        int res = last[rowmin(last, ncol, -1)];
        delete [] last;
        delete [] cur;
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        int n = arr.size();
        vector<int> dp(arr[0]);

        for (int i = 1; i < n; i++) {
            int min1 = INT_MAX, min2 = INT_MAX, minj = -1;
            for (int j = 0; j < n; j++) {
                int num = dp[j];
                if (num < min1) {
                    min2 = min1; min1 = num; minj = j;
                }
                else if (num < min2)
                    min2 = num;
            }
            for (int j = 0; j < n; j++)
                dp[j] = (j == minj ? min2 : min1) + arr[i][j];
        }

        return *min_element(dp.begin(), dp.end());
    }
};
```