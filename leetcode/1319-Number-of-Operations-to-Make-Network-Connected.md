#### There are n computers numbered from 0 to n-1 connected by ethernet cables connections forming a network where connections[i] = [a, b] represents a connection between computers a and b. Any computer can reach any other computer directly or indirectly through the network.

Given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected. Return the minimum number of times you need to do this in order to make all the computers connected. If it's not possible, return -1. 

 

```
Example 1:

Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.

Example 2:

Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2

Example 3:

Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.

Example 4:

Input: n = 5, connections = [[0,1],[0,2],[3,4],[2,3]]
Output: 0
```

 

#### Constraints:

-    1 <= n <= 10^5
-    1 <= connections.length <= min(n*(n-1)/2, 10^5)
-    connections[i].length == 2
-    0 <= connections[i][0], connections[i][1] < n
-    connections[i][0] != connections[i][1]
-    There are no repeated connections.
-    No two computers are connected by more than one cable.


#### Solutions

- The idea is to save the number of connections as much as possible. ie: only if the connection reduces the number of communities.
- After utilizing valid connections, the remaining connections can be utilized to combine seprated components together.

1. ##### Union Find/ greedy

```c++
class UnionFind {
public:
    int * nodes;
    int size;
    UnionFind(int size) {
        nodes = new int[size];
        for (int i = 0; i < size; i++)
            nodes[i] = i;
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
            nodes[f1] = f2;
            return true;
        }
    }
};
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int comsize = n, conn = 0;
        UnionFind uf(n);
        
        for (auto & e : connections)
            if (uf.merge(e[0], e[1]))
                comsize--;
            else // store redundant connections
                conn++;
        // 3 nodes need 2 connections
        return conn < comsize - 1 ? -1 : comsize - 1;
    }
};
```

2. ##### dfs

