#### Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

```
For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
```

#### Note:

- Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.


#### Solutions

1. ##### top-down dynamic programming

```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> lastrow(triangle.size(), 0);
        lastrow[0] = triangle[0][0];

        for (int i = 1; i < triangle.size(); i++) {
            int prev = lastrow[0];
            // the second row needs special treatment
            int cur = i == 1 ? INT_MAX : lastrow[1];

            lastrow[0] = prev + triangle[i][0];
            for (int j = 1; j < i; j++) {
                lastrow[j] = min(prev, cur) + triangle[i][j];
                prev = cur;
                cur = lastrow[j + 1]; 
            }
            lastrow[i] = prev + triangle[i][i];
        }

        return *min_element(lastrow.begin(), lastrow.end()); 

    }
};
```

2. ##### bottom-up dynamic programming


```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> minpath(triangle[triangle.size() - 1]);

        for (int i = triangle.size() - 2; i >= 0; i--) {
            for (int j = 0; j < i + 1; j++)
                minpath[j] = min(minpath[j], minpath[j + 1]) + triangle[i][j];
        }

        return minpath[0];
    }
};
```


Or a inplace version

```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {

        for (int i = triangle.size() - 2; i >= 0; i--) {
            for (int j = 0; j < i + 1; j++)
                triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1])
                                 + triangle[i][j];
        }

        return triangle[0][0];
    }
};
```