---
title: Max Points on a Line
date: 2021-01-04
---
#### Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

```
Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4

Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
```

#### NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.


#### Solutions

1. ##### count slope O(n2) S(n)

- reference: https://leetcode.com/problems/max-points-on-a-line/discuss/47124/C%2B%2B-slope-counter
- For each point, check all possible lines could be found and record the maximum number of points reside in thoese lines.
- To get rid of precision problems, we use `gcd` pair to represents a unique line/slope.

```cpp
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int res = 0;
        for (int i = 0; i < points.size(); i++) {
            int dup = 1, maxc = 0;
            unordered_map<string, int> counter;
            for (int j = i + 1; j < points.size(); j++) {
                int x = points[j][0] - points[i][0];
                int y = points[j][1] - points[i][1];
                if (x == 0 && y == 0)
                    dup++;
                else {
                    int g = gcd(x, y);
                    int curcount = ++counter[to_string(x / g) + "_" + to_string(y / g)];
                    if (curcount > maxc)
                        maxc = curcount;
                }
            }

            res = max(res, maxc + dup);
        }
        return res;
    }
    int gcd(int x, int y) {
        while (y) {
            x = x % y;
            swap(x, y);
        }
        return x;
    }
};
```


2. ##### Another method

- reference: https://leetcode.com/problems/max-points-on-a-line/discuss/221044/