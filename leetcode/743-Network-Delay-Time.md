There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

 

Example 1:



Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2
 

Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.

#### Solutions

- Shortest path problem.
- reference: https://www.cnblogs.com/thousfeet/p/9229395.html


1. ##### dfs O(n^n)

```c++
class Solution {
public:
    vector<int> arrive;
    unordered_map<int, vector<pair<int, int>>> g;
    void dfs(int node, int time) {
        if (time > arrive[node])
            return;
        arrive[node] = time;
        for (auto & [out, t] : g[node])
            dfs(out, time + t);
    }
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        if (times.size() < N - 1) return -1;
        for (auto & v : times)
            g[v[0]].emplace_back(v[1], v[2]);
        
        arrive = vector<int>(N + 1, INT_MAX);
        dfs(K, 0);
        int maxt = *max_element(dis[K].begin(), dis[K].end());

        return maxt == INT_MAX ? -1 : maxt;
    }
};
```

2. ##### dijkstra O((n + e)log(n))

```c++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        if (times.size() < N - 1) return -1;
        using pii = pair<int, int>;
        vector<vector<pair<int, int>>> g(N + 1);
        for (auto & e : times)
            g[e[0]].emplace_back(e[1], e[2]);

        const int INF = 0x3f3f3f3f;
        vector<bool> visited(N + 1);
        vector<int> dis(N + 1, INF); dis[K] = 0;
        priority_queue<pii, vector<pii>, greater<>> pq;
        pq.emplace(0, K);

        while (!pq.empty()) {
            // connect neighbors with the minimum distance
            auto [curdis, cur] = pq.top(); pq.pop();
            if (visited[cur]) continue;
            // mark as the minimum dis to K has been settled.
            visited[cur] = true;
            for (auto & [out, t] : g[cur]) {
                if (visited[out]) continue;
                if (curdis + t < dis[out]) {
                    dis[out] = curdis + t;
                    pq.emplace(dis[out], out);
                }
            }
        }
        
        int maxt = *max_element(dis[K].begin(), dis[K].end());

        return maxt == INF  ? -1 : maxt;
    }
};
```

3. ##### Floyd O(n3)

```c++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        if (times.size() < N - 1) return -1;
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> dis(N + 1, vector<int>(N + 1, INF));
        for (int i = 1; i <= N; i++)
            dis[i][i] = 0;
        for (auto & e : times)
            dis[e[0]][e[1]] = e[2];
        dis[K][0] = 0;

        for (int k = 1; k <= N; k++)
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        
        int maxt = *max_element(dis[K].begin(), dis[K].end());

        return maxt == INF ? -1 : maxt;
    }
};
```

3. ##### Bellman-Ford O(ne)

```c++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        const int INF = 0x3f3f3f3f;
        vector<int> dis(N + 1, INF); dis[0] = 0;
        dis[K] = 0;
        // there are at most N - 1 steps to reach the target.
        for (int n = 1; n < N; n++) {
            bool find = false;
            // check if any edges can update mindis
            for (auto & e : times)
                if (dis[e[0]] + e[2] < dis[e[1]]) {
                    dis[e[1]] = dis[e[0]] + e[2];
                    find = true;
                }
            if (!find) break;
        }
        
        int maxt = *max_element(dis.begin(), dis.end());

        return maxt == INF ? -1 : maxt;
    }
};
```


4. ##### SPFA avg(O(e)), worst(O(ne))

- compared to Bellman-Ford algorithm, only check edges sourced from updated nodes.

```c++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        const int INF = 0x3f3f3f3f;
        vector<vector<pair<int, int>>> g(N + 1);
        for (auto & e : times)
            g[e[0]].emplace_back(e[1], e[2]);
        
        vector<int> dis(N + 1, INF), vis(N + 1);
        dis[0] = dis[K] = 0; vis[K] = true;
        queue<int> q; q.push(K);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            vis[cur] = false;
            for (auto [out, t] : g[cur]) {
                if (dis[cur] + t < dis[out]) {
                    dis[out] = dis[cur] + t;
                    if (!vis[out]) {
                        q.push(out);
                        vis[out] = true;
                    }
                }
            }
        }
        int maxt = *max_element(dis.begin(), dis.end());

        return maxt == INF ? -1 : maxt;
    }
};
```