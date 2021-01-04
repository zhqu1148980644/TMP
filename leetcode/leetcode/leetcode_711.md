---
title: Number of Distinct Islands II
date: 2021-01-04
---
#### Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if they have the same shape, or have the same shape after rotation (90, 180, or 270 degrees only) or reflection (left/right direction or up/down direction).

```
Example 1:

11000
10000
00001
00011

Given the above grid map, return 1.

Notice that:

11
1

and

 1
11

are considered same island shapes. Because if we make a 180 degrees clockwise rotation on the first island, then two islands will have the same shapes.

Example 2:

11100
10001
01001
01110

Given the above grid map, return 2.

Here are the two distinct islands:

111
1

and

1
1


Notice that:

111
1

and

1
111

are considered same island shapes. Because if we flip the first array in the up/down direction, then they have the same shapes.
```

#### Note: The length of each dimension in the given grid does not exceed 50. 


#### Solutions

- reference: https://www.cnblogs.com/grandyang/p/8542820.html
- Compared to the previous problem 694, this one is more complicated.
- The main point is to design a mapping function that islands with the same shape can be mapped to a unique key.
- A unique shape contains 8 transformation: 4 by `rotation` and 4 by `reversion(mirror)`.
- We `normalize` all coordinates within an island relative to the `left-top` point. ie: for a transformation: we just sort all points by their corrdinates and compute their relative coordinates with respect to the left-top one.
    - The choice of the base line point is not unique, other points could works too as long as all islands are normalized by the same rule.
- Then, we choose the minimum normalized shape as the unique key of each unique shape.


1. ##### dfs

```cpp
class Solution {
public:
    void dfs(vector<vector<int>> & grid, vector<pair<int, int>> & coor, int x, int y) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != 1)
            return;
        coor.push_back({x, y});
        // you may want to restore the original grid.
        grid[x][y] = 2;
        dfs(grid, coor, x + 1, y);
        dfs(grid, coor, x, y + 1);
        dfs(grid, coor, x - 1, y);
        dfs(grid, coor, x, y - 1);
    }

    vector<pair<int, int>> normalize(vector<pair<int, int>> & coor) {
        vector<vector<pair<int, int>>> shapes(8);
        for (auto & co : coor) {
            // 8 transformations.
            int x = co.first, y = co.second;
            shapes[0].push_back({x ,y});
            shapes[1].push_back({-x ,y});
            shapes[2].push_back({x ,-y});
            shapes[3].push_back({-x ,-y});
            shapes[4].push_back({y ,x});
            shapes[5].push_back({-y ,x});
            shapes[6].push_back({y ,-x});
            shapes[7].push_back({-y ,-x});
        }
        for (auto & shape : shapes) {
            // normalize coordinates with respect to the left-top point.
            sort(shape.begin(), shape.end());
            int basex = shape[0].first, basey = shape[0].second;
            for (auto & co : shape) {
                co.first -= basex;
                co.second -= basey;
            }
        }
        // we only need to choose one transformation as long as they are choosed by the same rule.
        sort(shapes.begin(), shapes.end());
        return shapes[0];
    }

    int numDistinctIslands2(vector<vector<int>>& grid) {
        set<vector<pair<int, int>>> islands;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] != 1)
                    continue;
                vector<pair<int, int>> coor;
                dfs(grid, coor, i, j);
                islands.insert(normalize(coor));
            }
        return islands.size();
    }
};
```