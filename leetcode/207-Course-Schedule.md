#### There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?


```
Example 1:

Input: 2, [[1,0]] 
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.

Example 2:

Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
```

#### Note:

-    The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
-    You may assume that there are no duplicate edges in the input prerequisites.


#### Solutions

- This is a graph problem, we can finish all courses only if the dependency graph is a DAG.
- To check is a graph is a DAG, we can:
    - A DAG must have a topological ordering of all nodes.
    - check if there is a cycle in the dependency graph.

1. ##### topological sorting with bfs

- In each step, remove a node with node indgree(dependency).

```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indeg(numCourses, 0);
        unordered_map<int, vector<int>> adj;

        for (auto & cur_pre : prerequisites) {
            indeg[cur_pre[0]]++;
            adj[cur_pre[1]].push_back(cur_pre[0]);
        }
        queue<int> zeroIn;
        for (int node = 0; node < numCourses; node++)
            if (indeg[node] == 0)
                zeroIn.push(node);

        int removed = 0;
        while (!zeroIn.empty()) {
            int cur = zeroIn.front(); zeroIn.pop();
            removed++;
            for (auto & outnode : adj[cur])
                if (--indeg[outnode] == 0)
                    zeroIn.push(outnode);
        }

        return removed == numCourses;
    }
};
```


2. ##### dfs

```c++
enum State {UNVISITED, VISITED, VISITING};

class Solution {
private:
    vector<State> states;
    unordered_map<int, vector<int>> adj;

public:
    bool dfs(int root) {
        if (states[root] == VISITED)
            return true;
        else if (states[root] == VISITING)
            return false;
        else {
            states[root] = VISITING;
            for (auto & out : adj[root])
                if (!dfs(out)) return false;
            states[root] = VISITED;
            return true;
        }
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        states = move(vector<State>(numCourses, UNVISITED));

        for (auto & cur_pre : prerequisites)
            adj[cur_pre[1]].push_back(cur_pre[0]);

        for (int node = 0; node < numCourses; node++)
            if (!dfs(node)) return false;

        return true;
    }
};
```