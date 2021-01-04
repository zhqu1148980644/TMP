---
title: Remove Max Number of Edges to Keep Graph Fully Traversable
date: 2021-01-04
---
Alice and Bob have an undirected graph of n nodes and 3 types of edges:

Type 1: Can be traversed by Alice only.
Type 2: Can be traversed by Bob only.
Type 3: Can by traversed by both Alice and Bob.
Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if it's impossible for the graph to be fully traversed by Alice and Bob.

 

Example 1:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
Output: 2
Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
Example 2:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
Output: 0
Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.
Example 3:



Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
Output: -1
Explanation: In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.
 

 

Constraints:

1 <= n <= 10^5
1 <= edges.length <= min(10^5, 3 * n * (n-1) / 2)
edges[i].length == 3
1 <= edges[i][0] <= 3
1 <= edges[i][1] < edges[i][2] <= n
All tuples (typei, ui, vi) are distinct.

#### Solutions


1. ##### greedy with UnionFind

- In the first step, remove redundant `type3` edges, then remove redundant edges of the other two types while building the graph.

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
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFind uf1(n + 1), uf2(n + 1);
        unordered_set<int> dup;
        int size1 = n, size2 = n;

        auto insert1 = [&](int st, int ed, int ei) {
            if (uf1.merge(st, ed))
                size1--;
            else
                dup.insert(ei);
        };
        auto insert2 = [&](int st, int ed, int ei) {
            if (uf2.merge(st, ed))
                size2--;
            else
                dup.insert(ei);
        };
        // remove redundant edges for type 3
        int ei = 0;
        for (auto & e : edges) {
            int st = e[1], ed = e[2], type = e[0];
            if (type != 3) continue;
            insert1(st, ed, ei); insert2(st, ed, ei);
            ei++;
        }
        // remove redundant edges for type 1 or 2
        // ei = 0; can be omitted, since ei must be different
        for (auto & e : edges) {
            int st = e[1], ed = e[2], type = e[0];
            if (type == 1) insert1(st, ed, ei);
            if (type == 2) insert2(st, ed, ei);
            ei++; 
        }
        // check if graphs is connected for both people
        if (size1 != 1 || size2 != 1) return -1;

        return dup.size();
    }
};
```