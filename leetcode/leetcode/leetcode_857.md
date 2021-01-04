---
title: Minimum Cost to Hire K Workers
date: 2021-01-04
---
There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum wage expectation.
Return the least amount of money needed to form a paid group satisfying the above conditions.

 

Example 1:

Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately. 
 

Note:

1 <= K <= N <= 10000, where N = quality.length = wage.length
1 <= quality[i] <= 10000
1 <= wage[i] <= 10000
Answers within 10^-5 of the correct answer will be considered correct.

#### Solutions

1. ##### greedy with priority

- The minimum price of a group equals to `max(wage[i]/quality[i]) * sumquality` in greedy mode.
    - for `(p1, q1)` and `(p2, q2)` and `p1/q1 > p2/q2`, if we give the first person `p1` wage, according to the rule, the second person would need at least `p1 * (q2/q1) == (p1/p1) * p2 > p2`, thus the second person is satisfied now.
- To find the minimum cost, we scan all people with thier `w/q` being the maximum among the group. So we can sort all people by their `w/q` in ascending order, then for the current people, all people in the left has a less `w/q` that means they are candidates groupmates.
- How to select K people among people with lower `w/q`? By removing people with higer qualities, `sumquality` would have chance to decrease(may not increase due to the current person's quality) and then the total price would be decreased(may be) following the formula mentioned above.
    - To achieve this, we use a maximum heap keeps dropping employees with highest quality.

```cpp
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int n = wage.size();
        vector<int> people(n); iota(people.begin(), people.end(), 0);
        // all people left would have lower wage/quality
        sort(people.begin(), people.end(), [&](int i1, int i2) {
            return (double)wage[i1] / quality[i1] < (double)wage[i2] / quality[i2];
        });
        // use heap to remove the one with high quality
        priority_queue<int> pq;
        double sumq = 0, res = INT_MAX;
        for (auto cur : people) {
            sumq += quality[cur];
            pq.push(quality[cur]);
            if (pq.size() > K)
                sumq -= pq.top(), pq.pop();
            if (pq.size() == K)
                res = min(res, sumq / quality[cur] * wage[cur]);
        }

        return res;
    }
};
```