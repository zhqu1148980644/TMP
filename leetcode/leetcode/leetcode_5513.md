---
title: Min Cost to Connect All Points
date: 2021-01-04
---
You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

 

Example 1:



Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation:

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.
Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
Example 3:

Input: points = [[0,0],[1,1],[1,0],[-1,1]]
Output: 4
Example 4:

Input: points = [[-1000000,-1000000],[1000000,1000000]]
Output: 4000000
Example 5:

Input: points = [[0,0]]
Output: 0
 

Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 106
All pairs (xi, yi) are distinct.


#### Solutions

- A typical minimum spanning tree problem

1. ##### kruskal algorithm O(E^2log(E))

```cpp
struct UnionFind {
    vector<int> nodes;
    UnionFind(int size) : nodes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        return nodes[node] == node ? node : (nodes[node] = find(nodes[node]));
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        UnionFind uf(n);

        multimap<int, pair<int, int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto e = abs(points[i][0] - points[j][0]) 
                       + abs(points[i][1] - points[j][1]);
                edges.emplace(e, make_pair(i, j));
            }
        }

        int comsize = n, res = 0;
        for (auto & [e, p] : edges) {
            if (uf.merge(p.first, p.second)) {
                res += e;
                if (--comsize == 1) break;
            }
        }

        return res;
    }
};
```

2. ##### prim algorithm O(V2)

- reference: https://leetcode-cn.com/problems/min-cost-to-connect-all-points/solution/on2-primsuan-fa-by-lucifer1004/
- altered version of prim algorithm specialized for dense graph.

```cpp
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> vis(n);
        vector<int> mindis(n, INT_MAX);
        mindis[0] = 0;

        int comsize = n, res = 0;
        while (comsize--) {
            int out = -1;
            for (int i = 0; i < n; i++) {
                if (!vis[i] && (out == -1 || mindis[i] < mindis[out])) {
                    out = i;
                }
            }
            vis[out] = true;
            res += mindis[out];

            for (int i = 0; i < n; i++) {
                if (vis[i]) continue;
                mindis[i] = min(mindis[i], abs(points[i][0] - points[out][0])
                                         + abs(points[i][1] - points[out][1]));
            }
        }

        return res;
    }
};
```