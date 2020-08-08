There are 2N people a company is planning to interview. The cost of flying the i-th person to city A is costs[i][0], and the cost of flying the i-th person to city B is costs[i][1].

Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.

 

Example 1:

Input: [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation: 
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
 

Note:

1 <= costs.length <= 100
It is guaranteed that costs.length is even.
1 <= costs[i][0], costs[i][1] <= 1000

#### Solutions

1. ##### greedy O(nlog(n)) or O(n)

- from the official answer.
- Suppose all people go to B, than select some guys flies to A, then the price changes of these people would be sum of `A[i] - B[i]`. Thus the answer can be solved by selecting first N people go to A when all persons are sorted by `A[i] - B[i]`. How to prove?
- An optimization would be to use quick sort for selecting the first lower half.

```c++
class Solution {
public:

    int twoCitySchedCost(vector<vector<int>>& costs) {
        vector<int> flya(costs.size());
        iota(flya.begin(), flya.end(), 0);
        sort(flya.begin(), flya.end(), [&](int i, int j) {
            return costs[i][0] - costs[i][1] < costs[j][0] - costs[j][1];
        });

        int res = 0, N = costs.size() / 2;
        for (int i = 0; i < N; i++)
            res += costs[flya[i]][0];
        
        for (int i = N; i < 2 * N; i++)
            res += costs[flya[i]][1];
        
        return res;
    }
};
```