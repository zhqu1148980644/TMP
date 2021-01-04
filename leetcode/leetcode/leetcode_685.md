---
title: Redundant Connection II
date: 2021-01-04
---
In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

```
Example 1:

Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3

Example 2:

Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
```

#### Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.


#### Solutions

- Since the original graph is a rooted tree and there is only one additional edge, there are three possible cases in total.
    - All nodes have `one` parents(indegree). This inserted edge will convert the graph into a cyclic graph.
    - One node have `two` parents(indegree), we must remove one of two duplicate edges.
        - the graph is cyclic after we removed the one of two duplicate edges.
            - Solution: to make the tree non-cyclic, the only choice is to remove the other duplicate edge.
        - Else
            - Solution: remove the last duplicate edge(within the cycle)
        - As the question needs the one occured last, we fistly remove the last duplicate edge, and check if there is a cycle.
    - Anyway, there must be a cycle in the ordered gaph when there is one more edge.

```
case 1: contains merely cycle, remove the cycle
     1 -> 2
     ^    |
     |    v
     4 <- 3

case 2: No cycle exists after removed the last duplicate edge(the last between 2->3 and 1->3)

  1
 / \
v   v
2-->3


case 3: Cycle exists after removeed the last duplicate edge(5->1), remove the other edge(4->1)
 5-->1 -> 2
     ^    |
     |    v
     4 <- 3
```

1. ##### union find

```cpp
struct UnionFind {
    int * nodes;
    int * sizes;
    UnionFind(int n) {
        nodes = new int[n];
        sizes = new int[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = i;
            sizes[i] = 1;
        }
    }
    int find(int node) {
        while (nodes[node] != node) {
            nodes[node] = nodes[nodes[node]];
            node = nodes[node];
        }
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1);
        int f2 = find(node2);
        if (f1 == f2)
            return false;
        else {
            if (sizes[f2] < sizes[f1])
                swap(f1, f2);
            nodes[f1] = f2;
            sizes[f2] += sizes[f1];
            return true;
        }
    }
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<int> parents(n);
        // find nodes with two parents
        vector<int> edge1 = {0, 0}, edge2 = {0, 0}, edgec = {0, 0};
        for (auto & e : edges) {
            int src = e[0], tgt = e[1];
            if (parents[tgt]) {
                edge1 = {parents[tgt], tgt};
                edge2 = e;
                // remove the last edge
                e = {0, 0};
                break;
            }
            parents[tgt] = src;
        }
        // find cycle
        UnionFind uf(n);
        for (auto e : edges) {
            // e[0] == 0 only if this edge is removed
            if (e[0] == 0)
                continue;
            if (!uf.merge(e[0], e[1])) {
                edgec = e;
                break;
            }
        }

        if (edge1[0] != 0)
            if (edgec[0] != 0)
                return edge1;
            else
                return edge2;
        else
            return edgec;
    }
};
```

2. ##### cycle

```cpp
class Solution {
public:
    bool hascycle(vector<int> & parents, int node) {
        int cur = parents[node];
        while (cur) {
            if (cur == node)
                return true;
            else
                cur = parents[cur];
        }
        return false;
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<int> parents(n, 0);
        
        vector<int> edge1 = {0, 0}, edge2 = {0, 0}, edgec = {0, 0};

        for (auto & e : edges) {
            int src = e[0], tgt = e[1];
            if (parents[tgt]) {
                edge1 = {parents[tgt], tgt};
                edge2 = e;
                e = {0, 0};
                break;
            }
            parents[tgt] = src;
        }

        parents = vector<int> (n);
        for (auto & e : edges) {
            if (e[0] == 0)
                continue;
            parents[e[1]] = e[0];
            if (hascycle(parents, e[1])) {
                edgec = e;
                break;
            }
        }

        if (edge1[0] != 0)
            if (edgec[0] != 0)
                return edge1; 
            else
                return edge2;
        else
            return edgec;
    }
};
```

or more concisely

```cpp
class Solution {
public:
    bool hascycle(vector<int> & parents, int node) {
        int cur = parents[node];
        while (cur) {
            if (cur == node)
                return true;
            else
                cur = parents[cur];
        }
        return false;
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<int> parents(n);
        vector<int> edge1 = {0, 0}, edge2 = {0, 0}, edgec = {0, 0};

        for (auto & e : edges) {
            int src = e[0], tgt = e[1];
            if (parents[tgt]) {
                edge1 = {parents[tgt], tgt};
                edge2 = e;
                continue;
            }
            parents[tgt] = src;
            // here is the trick
            // if there is a cycle, no need to check again, otherwise the hascycle may run endlessly
            // Can not break when found a cycle, because the duplicate edge may not be recorded yet
            if (!edgec[0] && hascycle(parents, e[1]))
                edgec = e;
        }

        if (edge1[0] != 0) {
            if (edgec[0] != 0)
                return edge1;
            else
                return edge2;
        }
        else
            return edgec;
    }
};
```