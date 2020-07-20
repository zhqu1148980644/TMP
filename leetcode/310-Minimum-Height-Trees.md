For an undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3 

Output: [1]
Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5 

Output: [3, 4]
Note:

According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.



#### Solutions

1. ##### bfs from leaf nodes

- Iteratively removing leaf nodes from the tree.
- Root numbers can only be `2` or `1`.

```c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (!edges.size()) return {0};
        vector<int> degree(n);
        unordered_map<int, vector<int>> g;
        for (auto & e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
            degree[e[0]]++; degree[e[1]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (degree[i] == 1)
                q.push(i);
        
        int visited = q.size();
        while (visited != n) {
            int size = q.size();
            while (size--) {
                auto cur = q.front(); q.pop();
                degree[cur]--;
                for (auto outnode : g[cur])
                    if (degree[outnode] > 0 && --degree[outnode] == 1) {
                        q.push(outnode);
                        visited++;
                    }
            }
        }
        vector<int> res;
        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }
        return res;
    }
};
```