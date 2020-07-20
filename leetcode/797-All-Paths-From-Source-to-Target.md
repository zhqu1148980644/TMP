Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.

The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []] 
Output: [[0,1,3],[0,2,3]] 
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:

The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of nodes inside one path.

#### Solutions

1. ##### dfs

```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    void dfs(vector<vector<int>> & g, int cur) {
        if (cur == g.size() - 1)
            res.push_back(path);
        else {
            for (auto out : g[cur]) {
                path.push_back(out);
                dfs(g, out);
                path.pop_back();
            }
        }
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        path.reserve(graph.size() * 2);
        path.push_back(0);
        dfs(graph, 0);
        return res;
    }
};
```