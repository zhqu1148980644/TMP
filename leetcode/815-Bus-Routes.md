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

- Find all buses will be acrossed at each stop.
- The traffic network is a graph composed of multiple stops and these stops are connected by buses.
- Then this problem equals to find the minumum path in a graph.
- Caution: `Do not use vector` to store buses as some test case contains TOO MANY duplicate stops.


```c++
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;
        unordered_map<int, set<int>> out_buses;
        for (int bus = 0; bus < routes.size(); bus++)
            for (auto & stop : routes[bus])
                out_buses[stop].insert(bus);

        unordered_set<int> seen;
        queue<int> q;
        int bus_count = 0;
        q.push(S);
        seen.insert(S);

        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int stop = q.front(); q.pop();
                for (auto & bus : out_buses[stop]) {
                    for (auto & nextstop : routes[bus]) {
                        if (seen.count(nextstop))
                            continue;
                        if (nextstop == T)
                            return bus_count + 1;
                        q.push(nextstop);
                        seen.insert(nextstop);
                    }
                    routes[bus].clear();
                }
            }
            bus_count++;
        }

        return -1;
    }
};
```


2. ##### Another method

- Treat buses as nodes.

```c++
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;
        unordered_map<int, set<int>> out_buses;
        for (int bus = 0; bus < routes.size(); bus++)
            for (auto & stop : routes[bus])
                out_buses[stop].insert(bus);

        vector<bool> seen(routes.size(), false);
        queue<int> q;
        int bus_count = 0;
        for (auto & bus : out_buses[S]) {
            q.push(bus);
            seen[bus] = true;
        }

        while (!q.empty()) {
            bus_count++;
            int size = q.size();
            while (size--) {
                int bus = q.front(); q.pop();
                for (auto & stop : routes[bus]) {
                    if (stop == T)
                        return bus_count;
                    for (auto & bus : out_buses[stop]) {
                        if (seen[bus])
                            continue;
                        q.push(bus);
                        seen[bus] = true;
                    }
                }
            }

        }

        return -1;
    }
};


```