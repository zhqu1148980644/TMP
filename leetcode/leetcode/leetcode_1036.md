---
title: Escape a Large Maze
date: 2021-01-04
---
In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.

We start at the source square and want to reach the target square.  Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.

Return true if and only if it is possible to reach the target square through a sequence of moves.

 

```
Example 1:

Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
Output: false
Explanation: 
The target square is inaccessible starting from the source square, because we can't walk outside the grid.

Example 2:

Input: blocked = [], source = [0,0], target = [999999,999999]
Output: true
Explanation: 
Because there are no blocked cells, it's possible to reach the target square.
```
 

#### Note:

-    0 <= blocked.length <= 200
-    blocked[i].length == 2
-    0 <= blocked[i][j] < 10^6
-    source.length == target.length == 2
-    0 <= source[i][j], target[i][j] < 10^6
-    source != target


#### Solutions

1. ##### bfs

- Since the total number of blocked cell is 200, the maximum area can be enclosed will not larger than 20000, in another way, the maximum level reach by bfs search will not exceed 200.

```
....*
...*
..*
.*
*
```


```cpp

#define node(x, y) (((x) * 1000000l) + (y))
class Solution {
public:
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    bool block(unordered_set<long> & blocked, long x, long y, long tx, long ty) {
        queue<long> q; q.push(node(x, y));
        unordered_set<long> visited;
        visited.insert(node(x, y));
        int level = -1, nx, ny;
        int maxlevel = blocked.size();

        while (!q.empty()) {
            if (++level >= maxlevel)
                return false;
            int size = q.size();
            while (size--) {
                x = q.front() / 1000000; y = q.front() % 1000000;
                q.pop();
                if (x == tx && y == ty)
                    return false;
                for (int i = 0; i < 4; i++) {
                    nx = x + dir[i][0]; ny = y + dir[i][1];
                    long n = node(nx, ny);
                    if (nx >= 0 && ny >= 0 && nx < 1e6 && ny < 1e6
                        && !visited.count(n) && !blocked.count(n)) {
                        visited.insert(n);
                        q.push(n);
                    }
                }
            }
        }
        return true;
    }
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& s, vector<int>& t) {
        if (!blocked.size()) return true;
        unordered_set<long> b;
        for (auto & pos : blocked)
            b.insert(node(pos[0], pos[1]));
        return !block(b, s[0], s[1], t[0], t[1])
            && !block(b, t[0], t[1], s[0], s[1]);
    }
};
```


- Optimised version.
- Think of the best case when there are 200 blocked cells surrounded the source cell which is the center of the circle, when bfs reaches this circle, the queue size will be 200.
- When the queue size is larger than 200, there must be holes in the circle,.

```cpp
#define node(x, y) (((x) * 1000000l) + (y))
class Solution {
public:
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    bool block(unordered_set<long> & blocked, long x, long y, long tx, long ty) {
        queue<long> q; q.push(node(x, y));
        unordered_set<long> visited;
        visited.insert(node(x, y));
        int level = -1, nx, ny;

        while (!q.empty()) {
            if (q.size() > blocked.size())
                return false;
            int size = q.size();
            while (size--) {
                x = q.front() / 1000000; y = q.front() % 1000000;
                q.pop();
                if (x == tx && y == ty)
                    return false;
                for (int i = 0; i < 4; i++) {
                    nx = x + dir[i][0]; ny = y + dir[i][1];
                    long n = node(nx, ny);
                    if (nx >= 0 && ny >= 0 && nx < 1e6 && ny < 1e6
                        && !visited.count(n) && !blocked.count(n)) {
                        visited.insert(n);
                        q.push(n);
                    }
                }
            }
        }
        return true;
    }
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& s, vector<int>& t) {
        if (!blocked.size()) return true;
        unordered_set<long> b;
        for (auto & pos : blocked)
            b.insert(node(pos[0], pos[1]));
        return !block(b, s[0], s[1], t[0], t[1])
            && !block(b, t[0], t[1], s[0], s[1]);
    }
};
```

2. ##### dfs

```cpp
#define node(x, y) ((x) * 1000000l + (y))
class Solution {
public:
    unordered_set<long> blocked;
    unordered_set<long> seen;
    bool dfs(int x, int y, int & tx, int & ty) {
        long n = node(x, y);
        if (x < 0 || y < 0 || x > 1e6 || y > 1e6 
            || blocked.count(n) || seen.count(n))
            return false;
        seen.insert(n);
        if (seen.size() >= 20000 || (x == tx && y == ty))
            return true;
        return dfs(x + 1, y, tx, ty)
                || dfs(x, y + 1, tx, ty)
                || dfs(x - 1, y, tx, ty)
                || dfs(x, y - 1, tx, ty);
    }
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        for (auto & v : blocked)
            this->blocked.insert(node(v[0], v[1]));
        bool st = dfs(source[0], source[1], target[0], target[1]);
        seen.clear();
        bool ts = dfs(target[0], target[1], source[0], target[1]);
        return st && ts;
    }
};
```