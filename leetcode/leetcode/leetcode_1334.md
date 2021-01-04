---
title: Find the City With the Smallest Number of Neighbors at a Threshold Distance
date: 2021-01-04
---
There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

 

```
Example 1:

Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.

Example 2:

Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.
```

 

#### Constraints:

-    2 <= n <= 100
-    1 <= edges.length <= n * (n - 1) / 2
-    edges[i].length == 3
-    0 <= fromi < toi < n
-    1 <= weighti, distanceThreshold <= 10^4
-    All pairs (fromi, toi) are distinct.


#### Solutions

- It's a shortest path problem.

1. ##### floyd algorithm O(n3)

- Floyd algorithm computes shortest paths of all possible pairs of nodes in the graph.

```cpp
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // floyd algorithm
        vector<vector<int>> dp(n, vector<int>(n, 10000));
        for (auto & e : edges)
            dp[e[0]][e[1]] = dp[e[1]][e[0]] = e[2];
        
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dp[i][k] + dp[k][j] < dp[i][j])
                        dp[i][j] = dp[i][k] + dp[k][j];
        // count the number of reacheable cities within the given threshold
        int city = 0, minnum = INT_MAX;
        for (int i = 0; i < n; i++) {
            int num = 0;
            for (int j = 0; j < n; j++)
                num += i != j && dp[i][j] <= distanceThreshold;
            if (num <= minnum) {
                minnum = num;
                city = i;
            }
        }
        return city;
    }
};
```


2. ##### dijkstra algorithm O(n3)

- reference: https://leetcode-cn.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/solution/dijistra-by-mike-meng/
- Dijkstra computes the minimum distance from a single source to multiple target nodes, thus we need to run this algorithm for every node.
- ??? Why do not use minstack?

```cpp
typedef pair<int, int> E;
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        unordered_map<int, vector<E>> g;
        // adjacency table
        for (auto & e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }

        int minsize = INT_MAX, city = 0;
        // Do dijkstra for each node
        for (int i = 0; i < n; i++) {
            unordered_map<int, int> shortlen;
            queue<E> q; q.push({i, 0});
            shortlen[i] = 0;
            while (!q.empty()) {
                auto cur = q.front().first;
                auto curlen = q.front().second;
                q.pop();
                if (curlen > shortlen[cur])
                    continue;
                for (auto & e : g[cur]) {
                    if (curlen + e.second > distanceThreshold)
                        continue;
                    if (!shortlen.count(e.first) 
                        || curlen + e.second < shortlen[e.first]) {
                        shortlen[e.first] = curlen + e.second;
                        q.push({e.first, curlen + e.second});
                    }
                }
            }

            if (shortlen.size() <= minsize) {
                minsize = shortlen.size();
                city = i;
            }
        }

        return city;
    }
};
```

- Or a normal dijkstra method.

```cpp
typedef pair<int, int> E;
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        unordered_map<int, vector<E>> g;
        for (auto & e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }

        auto cmp = [](E & e1, E & e2) {
            return e1.second > e2.second;
        };
        int minsize = INT_MAX, city = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<int, int> shortlen;
            priority_queue<E, vector<E>, decltype(cmp)> q(cmp);
            q.push({i, 0}); shortlen[i] = 0;
    
            while (!q.empty()) {
                auto cur = q.top().first;
                auto curlen = q.top().second;
                q.pop();
                if (curlen > shortlen[cur])
                    continue;
                for (auto & e : g[cur]) {
                    int newdis = curlen + e.second;
                    if (newdis > distanceThreshold)
                        continue;
                    if (!shortlen.count(e.first) || newdis < shortlen[e.first]) {
                        shortlen[e.first] = newdis;
                        q.push({e.first, newdis});
                    }
                }
            }

            if (shortlen.size() <= minsize) {
                minsize = shortlen.size();
                city = i;
            }
        }

        return city;
    }
};
```

