Starting with an undirected graph (the "original graph") with nodes from 0 to N-1, subdivisions are made to some of the edges.

The graph is given as follows: edges[k] is a list of integer pairs (i, j, n) such that (i, j) is an edge of the original graph,

and n is the total number of new nodes on that edge. 

Then, the edge (i, j) is deleted from the original graph, n new nodes (x_1, x_2, ..., x_n) are added to the original graph,

and n+1 new edges (i, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n-1}, x_n), (x_n, j) are added to the original graph.

Now, you start at node 0 from the original graph, and in each move, you travel along one edge. 

Return how many nodes you can reach in at most M moves.

 

```
Example 1:

Input: edges = [[0,1,10],[0,2,1],[1,2,2]], M = 6, N = 3
Output: 13
Explanation: 
The nodes that are reachable in the final graph after M = 6 moves are indicated below.

Example 2:

Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], M = 10, N = 4
Output: 23
```

 

#### Note:

-    0 <= edges.length <= 10000
-    0 <= edges[i][0] < edges[i][1] < N
-    There does not exist any i != j for which edges[i][0] == edges[j][0] and edges[i][1] == edges[j][1].
-    The original graph has no parallel edges.
-    0 <= edges[i][2] <= 10000
-    0 <= M <= 10^9
-    1 <= N <= 3000
-    A reachable node is a node that can be travelled to using at most M moves starting from node 0.


#### Solutions

- Treat the number of nodes within each edge as weights.


1. ##### dijkstra method

- `curw` represent the weight sum of the shortest path containing the current node. ie. we moved `curw` steps and reached the current node.

```c++
#define edge(x, y) (x < y ? x * N + y : y * N + x)

using E = pair<int, int>;
class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        unordered_map<int, vector<E>> g;
        unordered_map<int, vector<int>> mg;
        for (auto & e : edges) {
            // to make path sum equals to the number of visited nodes, we increment the number of inner nodes by 1. ie. after moved `num + 1` steps, we will be at the target node of this edge.
            g[e[0]].push_back({e[1], e[2] + 1});
            g[e[1]].push_back({e[0], e[2] + 1});
            mg[edge(e[0], e[1])] = {0, 0, e[2] + 1};
        }

        unordered_map<int, int> cost;
        // caution: Comp in priority queue is different from Comp in sort.
        auto cmp = [](E & e1, E & e2) {
            return e1.second > e2.second;
        };
        // min stack
        priority_queue<E, vector<E>, decltype(cmp)> pq(cmp);
        // the 0 node is counted in weight sum.
        pq.push({0, 0}); cost[0] = 0;
        int res = 0;

        while (!pq.empty()) {
            int cur = pq.top().first;
            int curw = pq.top().second;
            pq.pop();
            if (curw > cost[cur] || curw > M)
                continue;
            // curw may be equal to M, which means the current node is the last node
            res++;
            for (auto & e : g[cur]) {
                int next = e.first, neww = curw + e.second;
                auto & used = mg[edge(cur, next)][cur > next];
                used = max(used, min(e.second, M - curw));
                if (!cost.count(next) || neww < cost[next]) {
                    cost[next] = neww;
                    pq.push({next, neww});
                }
            }
        }
        // since the weight is incremented 1, we only count the number of inner nodes.
        for (auto & [ei, ev] : mg) {
            int used = ev[0] + ev[1];
            res += used >= ev[2] ? ev[2] - 1 : used;
        }

        return res;
    }
};
```

- Another version
- In this version, `curw` denotes the moved steps.

```c++
typedef pair<int, int> E;

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        unordered_map<int, vector<E>> g;
        for (vector<int> & e: edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }

        auto cmp = [](E & e1, E & e2) {
            return e1.second > e2.second;
        };
    
        map<E, int> used;
        unordered_map<int, int> cost;
        for (int i = 1; i < N; ++i)
            cost[i] = M + 1;

        priority_queue<E, vector<E>, decltype(cmp)> pq(cmp);
        pq.push({0, 0}); cost[0] = 0;
        int res = 0;
    
        while (!pq.empty()) {
            int cur = pq.top().first;
            int curw = pq.top().second;
            pq.pop();
            if (curw > cost[cur])
                continue;
            res++;
            // No need to worry about when M - curw == 0, as each edge(directed) will only be visited once
            for (auto & e: g[cur]) {
                int next = e.first, weight = e.second;
                used[{cur, next}] = min(weight, M - curw);

                int neww = curw + weight + 1;
                if (neww < min(cost[next], M + 1)) {
                    pq.push({next, neww});
                    cost[next] = neww;
                }
            }
        }

        for (vector<int> & e: edges)
            res += min(e[2], used[{e[0], e[1]}] + used[{e[1], e[0]}]);

        return res;
    }
};

```