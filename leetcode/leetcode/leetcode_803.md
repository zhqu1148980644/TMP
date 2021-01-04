---
title: Bricks Falling When Hit
date: 2021-01-04
---
#### We have a grid of 1s and 0s; the 1s in a cell represent bricks.  A brick will not drop if and only if it is directly connected to the top of the grid, or at least one of its (4-way) adjacent bricks will not drop.

We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j), the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.

Return an array representing the number of bricks that will drop after each erasure in sequence.

```
Example 1:
Input: 
grid = [[1,0,0,0],[1,1,1,0]]
hits = [[1,0]]
Output: [2]
Explanation: 
If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.

Example 2:
Input: 
grid = [[1,0,0,0],[1,1,0,0]]
hits = [[1,1],[1,0]]
Output: [0,0]
Explanation: 
When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.  Note that the erased brick (1, 0) will not be counted as a dropped brick.
```

 

#### Note:

-    The number of rows and columns in the grid will be in the range [1, 200].
-    The number of erasures will not exceed the area of the grid.
-    It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
-    An erasure may refer to a location with no brick - if it does, no bricks drop.


#### Solutions

1. ##### union find with reversed time reversed

- As the UnionFind structure is only capable of adding and merging elements, we need to revere the erasure process.
- By this way, we can utilize the efficient union operation of UF and count the increased number of bricks connected to the top(ceiling) at each erasure(add) step.

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int index) {
        while (nodes[index] != index) {
            nodes[index] = nodes[nodes[index]];
            index = nodes[index]; 
        }
        return index;
    }
    bool merge(int node1, int node2) {
        int father1 = find(node1);
        int father2 = find(node2);
        if (father1 == father2)
            return false;
        else {
            if (sizes[father1] > sizes[father2])
                swap(father1, father2);
            nodes[father1] = father2;
            sizes[father2] += sizes[father1];
            return true;
        }
    }
    int count(int node) {
        return this->sizes[find(node)];
    }
};
#define node(x, y) (((x) * ncol + (y)))
class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        // create a final grid containing bricks will not be erased
        // valid(former state is 1) erased items are marked as -1
        for (auto & x_y : hits)
            grid[x_y[0]][x_y[1]] *= -1;
        // create a community represent ceiling, bricks connected to ceiling will not drop
        int nrow = grid.size(), ncol = grid[0].size();
        UnionFind uf(nrow * ncol + 1);
        int ceil = nrow * ncol;
        // traverse all bricks and connect all nodes into communities
        for (int i = 0; i < nrow; i++) {
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] != 1)
                    continue;
                int cur = node(i, j);
                if (i == 0) uf.merge(cur, ceil);
                if (j + 1 < ncol && grid[i][j + 1] == 1)
                    uf.merge(cur, node(i, j + 1));
                if (i + 1 < nrow && grid[i + 1][j] == 1)
                    uf.merge(cur, node(i + 1, j));
            }
        }
        // Starting from the last erasure, put erased bricks onto the grid.
        // if the size of ceiling community increased after added the brick, the same number of bricks will fall when this bricks is removed.
        vector<int> increased(hits.size());
        for (int i = hits.size() - 1; i >= 0; i--) {
            int x = hits[i][0], y = hits[i][1];
            if (grid[x][y] == 0) continue;
            int cur = node(x, y);
            int precount = uf.count(ceil);
            if (x == 0)
                uf.merge(cur, ceil);
            else if (grid[x - 1][y] == 1)
                uf.merge(node(x - 1, y), cur);
            if (x + 1 < nrow && grid[x + 1][y] == 1)
                uf.merge(node(x + 1, y), cur);
            if (y - 1 >= 0 && grid[x][y - 1] == 1)
                uf.merge(node(x, y - 1), cur);
            if (y + 1 < ncol && grid[x][y + 1] == 1)
                uf.merge(node(x, y + 1), cur);
            if (uf.count(ceil) > precount)
                // 1 represents the erased element, it does not belong to dropped els
                increased[i] = uf.count(ceil) - precount - 1;
            // set to 1 to reverse the erasement
            grid[x][y] = 1;
        }

        return increased;
    }
};
```

2. ##### bfs

- Use the same idead but with different strategy for searching connected nodes.

```cpp

```


3. ##### other solutions

- Need to read.
- https://leetcode.com/problems/bricks-falling-when-hit/discuss/120057/C%2B%2B-DFS-(similar-to-LC749)
- https://leetcode.com/problems/bricks-falling-when-hit/discuss/119829/Python-Solution-by-reversely-adding-hits-bricks-back


