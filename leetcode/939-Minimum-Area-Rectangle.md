Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, with sides parallel to the x and y axes.

If there isn't any rectangle, return 0.

 

Example 1:

Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4
Example 2:

Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2
 

Note:

1 <= points.length <= 500
0 <= points[i][0] <= 40000
0 <= points[i][1] <= 40000
All points are distinct.

##### Solutions

1. ##### match vertical lines

- From the official answer

```c++
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // must be treemap, to ensure x are visited from smallest to largest
        map<int, vector<int>> cols;
        for (auto & v : points)
            cols[v[0]].push_back(v[1]);
        // int value type is sufficient, will only records the nearest vertical line
        int res = INT_MAX;
        unordered_map<int, int> vlines;
        for (auto & [x, ys] : cols) {
            sort(ys.begin(), ys.end());
            for (int i = 0; i < ys.size(); i++)
                for (int j = i + 1; j < ys.size(); j++) {
                    int y1 = ys[i], y2 = ys[j];
                    int vline = y1 * 40001 + y2;
                    if (vlines.count(vline))
                        res = min(res, (x - vlines[vline]) * (y2 - y1));
                    vlines[vline] = x;
                }
        }

        return res == INT_MAX ? 0 : res;
    }
};
```

2. ##### match diagonal line O(n2)

- From the official answer
- For all possible lines made of two points(excluding lines within the same column or row), check if the other two points in the antidiagonal exists.

```c++
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size(), res = INT_MAX;
        unordered_set<int> seen;
        for (auto & p : points)
            seen.insert(p[0] * 40001 + p[1]);

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                // excluding lines in the same column of row, otherwise  res = 0
                if (x1 == x2 || y1 == y2) continue;
                int p3 = x1 * 40001 + y2;
                int p4 = x2 * 40001 + y1;
                if (seen.count(p3) && seen.count(p4))
                    res = min(res, abs(x1 - x2) * abs(y1 - y2));
            }

        return res == INT_MAX ? 0 : res;
    }
};
```