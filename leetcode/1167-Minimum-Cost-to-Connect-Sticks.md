You have some sticks with positive integer lengths.

You can connect any two sticks of lengths X and Y into one stick by paying a cost of X + Y.  You perform this action until there is one stick remaining.

Return the minimum cost of connecting all the given sticks into one stick in this way.

 

Example 1:

Input: sticks = [2,4,3]
Output: 14
Example 2:

Input: sticks = [1,8,3,5]
Output: 30
 

Constraints:

1 <= sticks.length <= 10^4
1 <= sticks[i] <= 10^4

#### Solutions

1. ##### priority queue o(nlog(n))

```c++
class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        using PQ = priority_queue<int, vector<int>, greater<>>;
        PQ pq(sticks.begin(), sticks.end());

        int cost = 0;
        while (pq.size() >= 2) {
            auto min1 = pq.top(); pq.pop();
            auto min2 = pq.top(); pq.pop();
            cost += min1 + min2;
            pq.push(min1 + min2);
        }

        return cost;
    }
};
```