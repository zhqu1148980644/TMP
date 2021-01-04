---
title: Bus Routes
date: 2021-01-04
---
#### We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.

We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.

```
Example:
Input: 
routes = [[1, 2, 7], [3, 6, 7]]
S = 1
T = 6
Output: 2
Explanation: 
The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
```

#### Note:

-    1 <= routes.length <= 500.
-    1 <= routes[i].length <= 500.
-    0 <= routes[i][j] < 10 ^ 6.

#### Solutions

1. ##### bfs with queue

- The traffic network is a graph composed of multiple stops and these stops are connected by buses.
- Then this problem equals to find the minumum path in a graph.
- Caution: `Do not use vector` to store buses as some test case contains TOO MANY duplicate stops.


```cpp
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;
        unordered_map<int, unordered_set<int>> g;
        for (int route = 0; route < routes.size(); route++)
            for (auto & stop : routes[route])
                g[stop].insert(route);
            
        unordered_set<int> seen;
        queue<int> q;
        int bus_cnt = 0;
        q.push(S); seen.insert(S);
        
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int stop = q.front(); q.pop();
                for (auto route : g[stop]) {
                    for (auto nextstop : routes[route]) {
                        if (seen.count(nextstop))
                            continue;
                        if (nextstop == T)
                            return bus_cnt + 1;
                        q.push(nextstop);
                        seen.insert(nextstop);
                    }
                    // do not use one route multiple times
                    routes[route].clear();
                }
            }
            bus_cnt++;
        }

        return -1;
    }
};
```

or

```cpp
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;
        unordered_map<int, unordered_set<int>> g;
        for (int route = 0; route < routes.size(); route++)
            for (auto stop : routes[route])
                g[stop].insert(route);
        
        vector<bool> seen(routes.size());
        queue<int> q;
        int bus_cnt = 0;
        for (auto route : g[S]) {
            q.push(route);
            seen[route] == true;
        }

        while (!q.empty()) {
            bus_cnt++;
            int size = q.size();
            while (size--) {
                auto route = q.front(); q.pop();
                for (auto stop : routes[route]) {
                    if (stop == T) return bus_cnt;
                    for (auto outroute : g[stop]) {
                        if (seen[outroute])
                            continue;
                        q.push(outroute);
                        seen[outroute] = true;
                    }
                }
                routes[route].clear();
            }
        }
        return -1;
    }
};
```