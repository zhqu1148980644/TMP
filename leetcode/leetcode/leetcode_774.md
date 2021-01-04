---
title: Minimize Max Distance to Gas Station
date: 2021-01-04
---
On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.

Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

Return the smallest possible value of D.

Example:

Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
Note:

stations.length will be an integer in range [10, 2000].
stations[i] will be an integer in range [0, 10^8].
K will be an integer in range [1, 10^6].
Answers within 10^-6 of the true value will be accepted as correct.

#### Solutions

1. ##### priority queue O(nlog(n))

- At each step, cut the range with the maximum distance

```cpp
class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        using pii = pair<double, int>;
        auto cmp = [](auto & p1, auto & p2) {
            return p1.first / p1.second < p2.first / p2.second;
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp); 
        for (int i = 1; i < stations.size(); i++)
            pq.emplace(stations[i] - stations[i - 1], 1);
        
        while (K--) {
            auto maxd = pq.top(); pq.pop();
            maxd.second++;
            pq.push(maxd);
        }

        return pq.top().first / pq.top().second;
    }
};
```

2. ##### binary search O(log(1e8)n)

- Use binary search to find the target distance. For a suspected distance, if the requiered number of cuts (can split all ranges into subranges <= the suspected distance) is greater than `K`, then the suspected distance must be underestimated.

```cpp
class Solution {
public:
    int numcuts(vector<int> & stations, double maxdis) {
        int res = 0;
        for (int i = 1; i < stations.size(); i++)
            res += (double)(stations[i] - stations[i - 1]) / maxdis;
        return res;
    }
    double minmaxGasDist(vector<int>& stations, int K) {
        double lo = 0, hi = 1e8;
        while (hi - lo > 1e-6) {
            double mid = lo + ((hi - lo) / 2);
            if (numcuts(stations, mid) > K)
                lo = mid;
            else
                hi = mid;
        }

        return lo;
    }
};
```