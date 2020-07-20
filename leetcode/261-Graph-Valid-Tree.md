#### Given n nodes labeled from 0 to n-1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

```
Example 1:

Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
Output: true

Example 2:

Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
Output: false
```

#### Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0,1] is the same as [1,0] and thus will not appear together in edges.

#### Solutions

1. ##### Union Find

- If all nodes makes up a tree, then:
    - the graph is a `DAG` with topological ordering(not cycle).
    - The graph contains one single connected component.

```c++
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        while (nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
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
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;
        UnionFind uf(n);

        for (auto & e : edges)
            if (!uf.merge(e[0], e[1]))
                return false;
            else n--;
        
        return n == 1;
    }
};
```


2. ##### dfs with recursion

- Check if the total number of visited nodes equals n.
- Use a variable `prenode` to represent the previous node.  `a --> b` when visiting the neighbors of b, as the adjacency table is undirected, `a` will be a neigbor of `b` and `a` has been visited before.
- Return false if there is a visited node in the current node's neighbors except for the previous node.

```c++
class Solution {
public:
    int dfs(int node, vector<vector<int>> & adjs, vector<bool> & visited, int prenode) {
            int count = 1;
            visited[node] = true;
            for (auto & outnode : adjs[node]) {
                if (prenode == outnode) continue;
                if (!visited[outnode])
                    count += dfs(outnode, adjs, visited, node);
                else
                    return -1;
            }
            return count;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n, vector<int>());
        for (auto & e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n, false);

        return dfs(0, adjs, visited, -1) == n;
    }
};
```

Or use set to count the number of visited nodes.

```c++
class Solution {
public:
    bool dfs(int node, vector<vector<int>> & adjs, unordered_set<int> & visited, int prenode) {
            visited.insert(node);
            for (auto & outnode : adjs[node]) {
                if (prenode == outnode)
                    continue;
                if (visited.count(outnode))
                    return false;
                if (!dfs(outnode, adjs, visited, node))
                    return false;
            }
            return true;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n, vector<int>());
        for (auto & e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        unordered_set<int> visited;
        bool nocycle = dfs(0, adjs, visited, -1);
        return nocycle && (visited.size() == n);
        // Do not use dfs(0, adjs, visited, -1) && visited.size() == n
        // The right side of && will be executed first.
    }
};
```

3. ##### bfs with queue

```c++
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n, vector<int>());
        for (auto & e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        queue<pair<int, int>> q;
        vector<bool> visited(n, false);

        q.push(make_pair(0, -1));
        int visited_nodes = 0;

        while (!q.empty()) {
            int pre = q.front().second;
            int cur = q.front().first;
            q.pop();
            visited[cur] = true;
            visited_nodes++;
            for(auto & outnode : adjs[cur]) {
                if (outnode == pre) continue;
                if (visited[outnode]) return false;
                q.push(make_pair(outnode, cur));
            }
        }

        return visited_nodes == n;
    }
};
```