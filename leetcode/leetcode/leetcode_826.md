---
title: Most Profit Assigning Work
date: 2021-01-04
---
We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job. 

Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i]. 

Every worker can be assigned at most one job, but one job can be completed multiple times.

For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete any job, his profit is $0.

What is the most profit we can make?

Example 1:

Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100 
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.
Notes:

1 <= difficulty.length = profit.length <= 10000
1 <= worker.length <= 10000
difficulty[i], profit[i], worker[i]  are in range [1, 10^5]

#### Solutions

1. ##### sort O(nlog(n))

- Firstly remove(filter) worthless jobs using monostack based on jobs sorted by profit.
    - ie. remove jobs with higher difficulty but with lower profit.
    - Another idea is to record the maximum profit can be made in each difficulty.
- Then sort both filtered jobs and workers by difficulty/ability in ascending order.
- Finally use two pointer to search for the maximum profit can be made for each worker.

```cpp
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int m = difficulty.size(), n = worker.size();
        vector<pair<int, int>> vp(m);
        int w = 0;
        for (int i = 0; i < difficulty.size(); i++)
            vp[w++] = {profit[i], difficulty[i]};
        sort(vp.begin(), vp.end());
        // use monostack to remove jobs with heigh difficulty but with lower profit.
        vector<pair<int, int>> jobs; jobs.push_back({0, INT_MIN});
        for (auto & p : vp) {
            while (!jobs.empty() && jobs.back().second >= p.second)
                jobs.pop_back();
            jobs.push_back(p);
        }
        // sort both jobs and workers by difficulty in ascending order
        sort(jobs.begin(), jobs.end(), [](auto & p1, auto & p2) {
            return p1.second < p2.second;
        });
        sort(worker.begin(), worker.end());
        // two pointers to scan for the best profit for each worker
        int i = jobs.size() - 1, j = n - 1, res = 0;
        while (i >= 0 && j >= 0) {
            if (jobs[i].second > worker[j])
                i--;
            else {
                res += jobs[i].first;
                j--;
            }
        }

        return res;
    }
};
```

- More concise version from the official answer.
- Search from the lowest difficulty to the highest and record the maximum profit under the current difficulty.

```cpp
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int m = difficulty.size(), n = worker.size();
        vector<pair<int, int>> jobs(m);
        int w = 0;
        for (int i = 0; i < m; i++)
            jobs[w++] = {difficulty[i], profit[i]};
        
        sort(jobs.begin(), jobs.end());
        sort(worker.begin(), worker.end());

        int res = 0, maxpro = 0;
        for (int i = 0, j = 0; i < n; i++) {
            while (j < m && jobs[j].first <= worker[i])
                maxpro = max(maxpro, jobs[j++].second);
            res += maxpro;
        }

        return res;
    }
};
```