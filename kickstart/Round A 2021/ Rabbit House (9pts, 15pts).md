Problem
Barbara got really good grades in school last year, so her parents decided to gift her with a pet rabbit. She was so excited that she built a house for the rabbit, which can be seen as a 2D grid with R rows and C columns.

Rabbits love to jump, so Barbara stacked several boxes on several cells of the grid. Each box is a cube with equal dimensions, which match exactly the dimensions of a cell of the grid.

However, Barbara soon realizes that it may be dangerous for the rabbit to make jumps of height greater than 1 box, so she decides to avoid that by making some adjustments to the house. For every pair of adjacent cells, Barbara would like that their absolute difference in height be at most 1 box. Two cells are considered adjacent if they share a common side.

As all the boxes are superglued, Barbara cannot remove any boxes that are there initially, however she can add boxes on top of them. She can add as many boxes as she wants, to as many cells as she wants (which may be zero). Help hew determine what is the minimum total number of boxes to be added so that the rabbit's house is safe.

Input
The first line of the input gives the number of test cases, T. T test cases follow.

Each test case begins with a line containing two integers R and C.

Then, R lines follow, each with C integers. The j-th integer on i-th line, Gi,j, represents how many boxes are there initially on the cell located at the i-th row and j-th column of the grid.

Output
For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the minimum number of boxes to be added so that the rabbit's house is safe.

Limits
Memory limit: 1 GB.
1≤T≤100.
0≤Gi,j≤2⋅106, for all i, j.
Test Set 1
Time limit: 20 seconds.
1≤R,C≤50.
Test Set 2
Time limit: 40 seconds.
1≤R,C≤300.
Sample
Sample Input
save_alt
content_copy
3
1 3
3 4 3
1 3
3 0 0
3 3
0 0 0
0 2 0
0 0 0
Sample Output
save_alt
content_copy
Case #1: 0
Case #2: 3
Case #3: 4
In Sample Case #1, the absolute difference in height for every pair of adjacent cells is already at most 1 box, so there is no need to add any extra boxes.

In Sample Case #2, the absolute difference in height of the left-most cell and the middle cell is 3 boxes. To fix that, we can add 2 boxes to the middle cell. But then, the absolute difference of the middle cell and the right-most cell will be 2 boxes, so Barbara can fix that by adding 1 box to the right-most cell. After adding these 3 boxes, the safety condition is satisfied.

In Sample Case #3, the cell in the middle of the grid has an absolute difference in height of 2 boxes with all of its four adjacent cells. One solution is to add exactly 1 box to all of the middle's adjacent cells, so that the absolute difference between any pair of adjacent cells will be at most 1 box. That requires 4 boxes in total.


#### Solutions

- Note that the answer may  be larger than the limits of a 32-bit integer.

1. ##### greedy approach with pq

```c++
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t; cin >> t;
    for (int ti = 0; ti < t; ti++) {
        int r, c; cin >> r >> c;
        vector<vector<int>> grid(r, vector<int>(c));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cin >> grid[i][j];
        
        auto node = [&](int i, int j) {
            return i * c + j;
        };
        vector<bool> settled(r + c);
        auto cmp = [&](auto & t1, auto & t2) {
            return t1.first < t2.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                pq.emplace(grid[i][j], node(i, j));
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        size_t res = 0;
        while (pq.size()) {
            auto [h, n] = pq.top(); pq.pop();
            int x = n / c, y = n % c;
            if (grid[x][y] > h) continue;
            for (auto & d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
                if (h > grid[nx][ny] + 1) {
                    res += h - 1 - grid[nx][ny];
                    pq.emplace(h - 1, node(nx, ny));
                    grid[nx][ny] = h - 1;
                }
            }
        }
        cout << "Case #" << (ti + 1) << ": " << res << endl;
    
    }
}
```

2. ##### greedy approach with dp

- similar to `leetcode 135 candy`


```c++
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t; cin >> t;
    for (int ti = 0; ti < t; ti++) {
        int r, c; cin >> r >> c;
        vector<vector<int>> grid(r, vector<int>(c));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cin >> grid[i][j];

        size_t res = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                int h = max(i != 0 ? grid[i - 1][j] : 0, j != 0 ? grid[i][j - 1] : 0) - 1;
                if (h > grid[i][j]) {
                    res += h - grid[i][j];
                    grid[i][j] = h;
                }
            }
        }
        
        for (int i = r - 1; i >= 0; i--)
            for (int j = c - 1; j >= 0; j--) {
                int h = max(i != r - 1 ? grid[i + 1][j] : 0, j != c - 1 ? grid[i][j + 1] : 0) - 1;
                if (h > grid[i][j]) {
                    res += h - grid[i][j];
                    grid[i][j] = h;                    
                }
            }
        
        cout << "Case #" << (ti + 1) << ": " << res << endl;
    
    }
}
```