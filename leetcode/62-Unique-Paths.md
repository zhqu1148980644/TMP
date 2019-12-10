### A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


![a](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)

Above is a 7 x 3 grid. How many possible unique paths are there?

### Note: 
m and n will be at most 100.

```
Example 1:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right
Example 2:

Input: m = 7, n = 3
Output: 28
```

### Solutions

1. #### Dynamic programming

```c++
int uniquePaths(int m, int n){
    if (m == 1 || n == 1) return 1;
    if (m < n) swap(m, n);
    int row[n];
    for (int i = 0; i < n; i++) row[i] = 1;
    for (int i = 1; i < m; i++) {
        row[0] = 1;
        for (int j = 1; j < n; j++) {
            row[j] = row[j] + row[j - 1];
        }
    }
    return row[n - 1];
}
```

2. #### another perspective

- No matter how to move(only down and right are permitted), The total number of move operations will be m - 1 + n - 1; ie(reach the lower right)
- The unique path is the choose m - 1 operations to go down or n - 1 operations to go right; C(m + n - 2, m - 1)

```c++
int uniquePaths(int m, int n) {
    if (m == 1 || n == 1) return 1;
    if (m < n) swap(m, n);
    m--; n--;
    long res = 1;
    int j = 1;
    for (int i = m + 1; i <= m + n; i++, j++) {
        res *= i;
        res /= j;
    }
    return (int)res;
}
```
