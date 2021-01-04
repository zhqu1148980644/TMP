---
title: Cheapest Flights Within K Stops
date: 2021-01-04
---
There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.

Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 

Constraints:

The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
The size of flights will be in range [0, n * (n - 1) / 2].
The format of each flight will be (src, dst, price).
The price of each flight will be in the range [1, 10000].
k is in the range of [0, n - 1].
There will not be any duplicated flights or self cycles.

#### Solutions

- Shortest path problem, check `problem 743`


1. ##### Bellman-Ford O(ke)


```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 0x3f3f3f3f;
        vector<int> cost(n, INF);
        cost[src] = 0;
        
        for (int i = 0; i <= K; i++) {
            // must use a newcost array, otherwise may forward multiple steps
            vector<int> newcost(cost);
            bool update = false;
            for (auto & e : flights) {
                if (cost[e[0]] + e[2] < newcost[e[1]]) {
                    newcost[e[1]] = cost[e[0]] + e[2];
                    update = true;
                }
            }
            cost = move(newcost);
            // preexit
            if (!update) break;
        }

        return cost[dst] == INF ? -1 : cost[dst];
    }
};
```

2. ##### dijkstra

- In ordinary dijkstra algorihtm, the minimum cost with steps > K would forbid other costs with lower steps to be recorded. A simple solution is to put all path into the heap and discard the `mincost and visited` table. As a consequence, duplicate path or impossible path would be recorded, the time complexity would be much higher than traditional dijkstra.


```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 0x3f3f3f3f;
        if (src == dst) return 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto & e : flights)
            g[e[0]].emplace_back(e[1], e[2]);
        
        K++;
        using State = tuple<int, int, int>;
        priority_queue<State, vector<State>, greater<>> q;
        q.emplace(0, 0, src);

        while (!q.empty()) {
            auto [cost, step, cur] = q.top(); q.pop();
            if (cur == dst) return cost;
            if (step + 1 > K) continue;
            for (auto [out, w] : g[cur]) {
                q.emplace(cost + w, step + 1, out);
            }
        }

        return -1;
    }
};
```

- borrowed from the official answer
- A minor optimization is to keep track of both cost and step info, permitting multiple path being recorded while still discard path with low priority(The same step but with more cost).
- In particular we use `nstep * 1000 + node` as the unique key representing the minimum cost at `node` with exactly `nstep` steps passed.

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 0x3f3f3f3f;
        if (src == dst) return 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto & e : flights)
            g[e[0]].emplace_back(e[1], e[2]);
        
        K++;
        using State = tuple<int, int, int>;
        unordered_map<int, int> costs; costs[src] = 0;
        priority_queue<State, vector<State>, greater<>> q;
        q.emplace(0, 0, src);

        while (!q.empty()) {
            auto [cost, step, cur] = q.top(); q.pop();
            if (cur == dst) return cost;
            if (step + 1 > K) continue;
            for (auto [out, w] : g[cur]) {
                int newcost = cost +  w;
                int outkey = (step + 1) * 1000 + out;
                if (costs.count(outkey) && newcost > costs[outkey])
                    continue;
                q.emplace(newcost, step + 1, out);
                costs[outkey] = newcost;
            }
        }

        return -1;
    }
};
```

3. ##### bfs

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 0x3f3f3f3f;
        if (src == dst) return 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto & e : flights)
            g[e[0]].emplace_back(e[1], e[2]);
        
        K++;
        using State = tuple<int, int, int>;
        queue<State> q; q.emplace(0, 0, src);
        vector<int> costs(n, INF); costs[src] = 0;

        while (!q.empty()) {
            auto [cost, step, cur] = q.front(); q.pop();
            // if cur == dst, can not return
            // there may be other routes with less cost
            if (cur == dst || step + 1 > K)
                continue;
            for (auto [out, w] : g[cur]) {
                // since the graph has no cycle, all updates has the same step.
                if (cost + w >= costs[out]) continue;
                q.emplace(costs[out] = cost + w, step + 1, out);
            }
        }

        return costs[dst] == INF ? -1 : costs[dst];
    }
};
```

or

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 0x3f3f3f3f;
        if (src == dst) return 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto & e : flights)
            g[e[0]].emplace_back(e[1], e[2]);
        
        K++;
        queue<pair<int, int>> q; q.emplace(0, src);
        vector<int> costs(n, INF); costs[src] = 0;

        while (!q.empty() && K--) {
            int size = q.size();
            while (size--) {
                auto [cost, cur] = q.front(); q.pop();
                // can not return, there may be other better routes did not get to the target yet(Need more step)
                if (cur == dst) continue;
                for (auto [out, w] : g[cur]) {
                // since the graph has no cycle, all updates has the same step.
                    if (cost + w > costs[out])
                        continue;
                    q.emplace(costs[out] = cost + w, out);
                }
            }
        }

        return costs[dst] == INF ? -1 : costs[dst];
    }
};

```