---
title: Connecting Cities With Minimum Cost
date: 2021-01-04
---
#### There are N cities numbered from 1 to N.

You are given connections, where each connections[i] = [city1, city2, cost] represents the cost to connect city1 and city2 together.  (A connection is bidirectional: connecting city1 and city2 is the same as connecting city2 and city1.)

Return the minimum cost so that for every pair of cities, there exists a path of connections (possibly of length 1) that connects those two cities together.  The cost is the sum of the connection costs used. If the task is impossible, return -1.

 

```
Example 1:

Input: N = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
Output: 6
Explanation: 
Choosing any 2 edges will connect all cities so we choose the minimum 2.

Example 2:

Input: N = 4, connections = [[1,2,3],[3,4,4]]
Output: -1
Explanation: 
There is no way to connect all cities even if all edges are used.
```

 

#### Note:

-    1 <= N <= 10000
-    1 <= connections.length <= 10000
-    1 <= connections[i][0], connections[i][1] <= N
-    0 <= connections[i][2] <= 10^5
-    connections[i][0] != connections[i][1]

#### Solutions

- Equivalent to build a minimum spanning tree.

1. ##### kruskal algorithm with UnionFind O(elog(e))

- Sort connections by their costs in an increasing order.
- Then iteratively put connections into the min spanning tree if cities in connection is not connected.
- Check if the size of connected components equals to one to make sure all cities are connected.
    - The growing tree built by kruskal algorihtm is not guaranteed to be connected(sparse) as apposesed to prim algorithm.

```cpp
class UnionFind {
private:
    int * nodes;
    int * sizes;
public:
    UnionFind(int size) {
        nodes = new int[size];
        sizes = new int[size];
        for (int i = 0; i < size; i++) {
            nodes[i] = i;
            sizes[i] = 1;
        }
    }
    ~UnionFind() {
        delete [] nodes; delete [] sizes;
    }
    int find(int node) {
        while (nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1);
        int f2 = find(node2);
        if (f1 == f2)
            return false;
        else {
            if (sizes[f1] > sizes[f2])
                swap(f1, f2);
            nodes[f1] = f2;
            sizes[f2] += sizes[f1];
            return true;
        }
    }
};
class Solution {
public:
    int minimumCost(int N, vector<vector<int>>& connections) {
        UnionFind uf(N + 1);
        sort(connections.begin(), connections.end(), [](vector<int> & edge1, vector<int> & edge2) {
            return edge1[2] < edge2[2];
        });
        int num_com = N;
        int cost = 0;
        for (auto & e : connections) {
            if (uf.merge(e[0], e[1])) {
                num_com--;
                cost += e[2];
                if (num_com == 1)
                    return cost;
            }
        }
        return -1;
    }
};
```


2. ##### prim algorithm

- Ensure the connectivity during the graph expansion.
- In each step, find an edge with miminum cost with one node within the MST and another node outside.
- Use min heap to speed up the process of searching edge with the minimal cost.

```cpp
class Solution {
public:
    int minimumCost(int N, vector<vector<int>>& connections) {
        using E = pair<int, int>;
        vector<vector<E>> adjs(N + 1, vector<E>());
        for (auto & e : connections) {
            adjs[e[0]].emplace_back(e[2], e[1]);
            adjs[e[1]].emplace_back(e[2], e[0]);
        }

        int cost = 0, numnodes = 1;
        // visited represent nodes within the MSP
        vector<bool> visited(N + 1, false);
        visited[1] = true;
        priority_queue<E, vector<E>, greater<>> pq;
        for (auto & e : adjs[1])
            pq.push(e);

        while (!pq.empty()) {
            auto [w, cur] = pq.top(); pq.pop();
            if (visited[cur]) continue;
            visited[cur] = true; cost += w;
            if (++numnodes == N) return cost;
            for (auto [outw, out] : adjs[cur])
                if (!visited[out])
                    pq.emplace(outw, out);
        }

        return -1;
    }
};
```