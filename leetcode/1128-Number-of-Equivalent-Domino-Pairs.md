Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a==c and b==d), or (a==d and b==c) - that is, one domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].

 

Example 1:

Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1
 

Constraints:

1 <= dominoes.length <= 40000
1 <= dominoes[i][j] <= 

#### Solutions

1. ##### hash map

```c++
class Solution {
public:
#define node(x, y) ((x) * 10 + (y))
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        unordered_map<int, int> m;
        int res = 0;
        for (auto & d : dominoes) {
            int node1 = node(d[0], d[1]);
            int node2 = node(d[1], d[0]);
            if (m.count(node1)) 
                res += m[node1];
            if (d[0] != d[1] && m.count(node2))
                res += m[node2];
            m[node1]++;
        }
        return res;
    }
};
```