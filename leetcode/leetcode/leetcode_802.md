---
title: Find Eventual Safe States
date: 2021-01-04
---
In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.

Which nodes are eventually safe?  Return them as an array in sorted order.

The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Here is a diagram of the above graph.



Note:

graph will have length at most 10000.
The number of edges in the graph will not exceed 32000.
Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].

#### Solutions


1. ##### dfs


```cpp
class Solution {
public:
    enum State {UNVISITED, VISITING, VISITED};
    bool dfs(vector<State> & states, vector<vector<int>> & g, int cur) {
        if (states[cur] != UNVISITED)
            return states[cur] == VISITED;
        states[cur] = VISITING;
        for (auto out : g[cur])
        // skip visited, return false if the next node is within cycle
            if (states[out] != VISITED 
                && !dfs(states, g, out))
                return false;
        states[cur] = VISITED;
        return true;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<State> states(graph.size(), UNVISITED);
        vector<int> res;
        for (int i = 0; i < graph.size(); i++) {
            if (dfs(states, graph, i))
                res.push_back(i);
        }

        return res;
    }
};
```

2. ##### topological sort

- Borrowed from the official answer
- Reverse all edges and use bfs search for acyclic path starting with all 0 indgree(revered) nodes. Then all nodes has been popped by queue are safe nodes.

```cpp
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> indegree(n);
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) {
            for (auto ind : graph[i])
                g[ind].push_back(i);
            indegree[i] += graph[i].size();
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (!indegree[i])
                q.push(i);
        
        vector<int> safe(n);
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            safe[cur] = true;
            for (auto out : g[cur])
                if (--indegree[out] == 0)
                    q.push(out);
        }

        vector<int> res;
        for (int i = 0; i < n; i++)
            if (safe[i]) res.push_back(i);
        
        return res;
    }
};
```