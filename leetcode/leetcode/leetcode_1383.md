---
title: Maximum Performance of a Tea
date: 2021-01-04
---
There are n engineers numbered from 1 to n and two arrays: speed and efficiency, where speed[i] and efficiency[i] represent the speed and efficiency for the i-th engineer respectively. Return the maximum performance of a team composed of at most k engineers, since the answer can be a huge number, return this modulo 10^9 + 7.

The performance of a team is the sum of their engineers' speeds multiplied by the minimum efficiency among their engineers. 

 

```
Example 1:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
Output: 60
Explanation: 
We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
Example 2:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
Output: 68
Explanation:
This is the same example as the first but k = 3. We can select engineer 1, engineer 2 and engineer 5 to get the maximum performance of the team. That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
Example 3:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
Output: 72
```
 

##### Constraints:

1 <= n <= 10^5
speed.length == n
efficiency.length == n
1 <= speed[i] <= 10^5
1 <= efficiency[i] <= 10^8
1 <= k <= n


#### Solutions


1. ##### sort + heap nlog(n)


- Sort engineers based on their efficiency in an descending order.
- Maintaining a group of engineers with top k speeds when traversing engineers from the highest efficiency to the lowest, since each traversed engineer's efficiency is the lowest among those have been met, performance can be calculated in O(1) time.

```cpp
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        if (k == 0) return 0;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++)
            v[i] = {efficiency[i], i};
        
        sort(v.begin(), v.end(), greater<>());
        priority_queue<int, vector<int>, greater<>> pq;

        long maxp = 0, sumspeed = 0;
        for (auto [e, i] : v) {
            if (pq.size() >= k) {
                sumspeed -= pq.top();
                pq.pop();
            }
            maxp = max(maxp, (sumspeed + speed[i]) * e);
            sumspeed += speed[i];
            pq.push(speed[i]);
        }
        
        return maxp % 1000000007;
    }
};
```