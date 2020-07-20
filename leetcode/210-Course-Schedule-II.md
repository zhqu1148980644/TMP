#### There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

```
Example 1:

Input: 2, [[1,0]] 
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
             course 0. So the correct course order is [0,1] .

Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both     
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. 
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
```

#### Note:

-    The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
-    You may assume that there are no duplicate edges in the input prerequisites.

#### Solutions

- Topological ordering of nodes(courses).

1. ##### Topological sort

```c++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indgree(numCourses, 0);
        unordered_map<int, vector<int>> adj;

        for (auto & cur_pre : prerequisites) {
            indgree[cur_pre[0]]++;
            adj[cur_pre[1]].push_back(cur_pre[0]);
        }

        queue<int> zerodeg;

        for (int i = 0; i < numCourses; i++)
            if (!indgree[i]) zerodeg.push(i);

        vector<int> learned;
        while (!zerodeg.empty()) {
            auto cur = zerodeg.front(); zerodeg.pop();
            learned.push_back(cur);
            for (auto & outnode : adj[cur])
                if (--indgree[outnode] == 0)
                    zerodeg.push(outnode);
        }

        return (learned.size() == numCourses) ? learned : vector<int>{};
    }
};
```

2. ##### dfs

- Be cautious about the appending order and the reversement at the end;

```c++
enum State {UNVISITED, VISITED, VISITING};

class Solution {
private:
    vector<int> learned;
    vector<State> states;
    unordered_map<int, vector<int>> adj;

    bool dfs(int root) {
        if (states[root] == VISITED)
            return true;
        else if (states[root] == VISITING)
            return false;
        else {
            states[root] = VISITING;
            for (auto & outnode : adj[root])
                if (!dfs(outnode)) return false;
            states[root] = VISITED;
            learned.push_back(root);
            return true;
        }
    }

public:

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        states = move(vector<State>(numCourses, UNVISITED));
        for (auto & cur_pre : prerequisites)
            adj[cur_pre[1]].push_back(cur_pre[0]);
        for (int i = 0; i < numCourses; i++)
            if (!dfs(i)) return {};
        reverse(learned.begin(), learned.end());
        return learned;
    }
};
```