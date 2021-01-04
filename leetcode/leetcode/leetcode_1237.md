---
title: Find Positive Integer Solution for a Given Equation
date: 2021-01-04
---
Given a function  f(x, y) and a value z, return all positive integer pairs x and y where f(x,y) == z.

The function is constantly increasing, i.e.:

f(x, y) < f(x + 1, y)
f(x, y) < f(x, y + 1)
The function interface is defined like this: 

interface CustomFunction {
public:
  // Returns positive integer f(x, y) for any given positive integer x and y.
  int f(int x, int y);
};
For custom testing purposes you're given an integer function_id and a target z as input, where function_id represent one function from an secret internal list, on the examples you'll know only two functions from the list.  

You may return the solutions in any order.

 

Example 1:

Input: function_id = 1, z = 5
Output: [[1,4],[2,3],[3,2],[4,1]]
Explanation: function_id = 1 means that f(x, y) = x + y
Example 2:

Input: function_id = 2, z = 5
Output: [[1,5],[5,1]]
Explanation: function_id = 2 means that f(x, y) = x * y
 

Constraints:

1 <= function_id <= 9
1 <= z <= 100
It's guaranteed that the solutions of f(x, y) == z will be on the range 1 <= x, y <= 1000
It's also guaranteed that f(x, y) will fit in 32 bit signed integer if 1 <= x, y <= 1000

#### Solutions

1. ##### binary search

- Be careful when shrinking the rigth boundary of the searching range.

```cpp
/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        for (int x = 1, y = 1000; x <= 1000 && y >= 1; x++) {
            // must plus 1.
            int lo = 1, hi = y + 1;
            // lower bound
            while (lo < hi) {
                int mid = lo + ((hi - lo) >> 1);
                if (z > customfunction.f(x, mid))
                    lo = mid + 1;
                else
                    hi = mid;
            }
            if (customfunction.f(x, lo) == z)
                res.push_back({x, lo});
            y = lo - 1;
        }

        return res;
    }
};
```

2. ##### two pointers O(n)

```cpp
/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        
        int x = 1, y = 1000;
        while (x <= 1000 && y >= 1) {
            while (y >= 1 && customfunction.f(x, y) > z)
                y--;
            if (y >= 1 && customfunction.f(x, y) == z)
                res.push_back({x, y});
            x++;
        }

        return res;
    }
};
```