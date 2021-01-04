---
title: Checking Existence of Edge Length Limited Paths
date: 2021-01-04
---
An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.

Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .

Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.

 

Example 1:


Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
Output: [false,true]
Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
Example 2:


Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
Output: [true,false]
Exaplanation: The above figure shows the given graph.
 

Constraints:

2 <= n <= 105
1 <= edgeList.length, queries.length <= 105
edgeList[i].length == 3
queries[j].length == 3
0 <= ui, vi, pj, qj <= n - 1
ui != vi
pj != qj
1 <= disi, limitj <= 109
There may be multiple edges between two nodes.

##### Solutions

1. ##### Union Find

- Use Union Find data structure to find if two nodes are connected in a undirected graph at nearly `O(1)` cost.
- Construct the graph incrementally by adding edges with increasing edge weight.

```cpp
struct UnionFind {
    vector<int> nodes;
    UnionFind(int k) : nodes(k) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        return (nodes[node] == node) ? node : (nodes[node] = find(nodes[node]));
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        else {
            nodes[f1] = f2;
            return true;
        }
    }

};

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        vector<bool> res(queries.size());
        map<int, vector<int>> qs;
        for (int i = 0; i < queries.size(); i++)
            qs[queries[i][2]].push_back(i);

        // sort by edge weight in increasing order
        sort(edgeList.begin(), edgeList.end(), [&](auto & e1, auto & e2) {
            return e1[2] <= e2[2];
        });
        edgeList.push_back({0, 0, INT_MAX});
        UnionFind uf(n);

        for (auto & e : edgeList) {
            int dis = e[2];
            while (qs.size() && dis >= qs.begin()->first) {
                for (auto qi : qs.begin()->second) {
                    int st = queries[qi][0];
                    int ed = queries[qi][1];
                    // connected means there has a path.
                    if (uf.find(st) == uf.find(ed))
                        res[qi] = true;
                }
                qs.erase(qs.begin());
            }
            uf.merge(e[0], e[1]);
        }

        return res;
    }
};
```