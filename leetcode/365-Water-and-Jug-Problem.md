You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs.

If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.

#### Operations allowed:

-    Fill any of the jugs completely with water.
-    Empty any of the jugs.
-    Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.

```
Example 1: (From the famous "Die Hard" example)

Input: x = 3, y = 5, z = 4
Output: True

Example 2:

Input: x = 2, y = 6, z = 5
Output: False
```

#### Solutions

1. ##### bfs search O(xy)

- Time limit exceed

```c++
class Solution {
public:
#define node(i, j) (((long)(i) * (y + 1) + (j)))
    bool canMeasureWater(int x, int y, int z) {
        queue<pair<int, int>> q;
        unordered_set<long> seen;
        q.push({0, 0});
        seen.insert(node(0, 0));
        
        int curx, cury;
        while (!q.empty()) {
            curx = q.front().first;
            cury = q.front().second;
            q.pop();
            if (curx == z || cury == z || curx + cury == z)
                return true;
            pair<int, int> states[6] = {
                {x, cury}, {curx, y},
                {0, cury}, {curx, 0},
                {min(curx + cury, x), cury - min(x - curx, cury)}, 
                {curx - min(y - cury, curx), min(curx + cury, y)}
            };
            for (auto & s : states)
                if (!seen.count(node(s.first, s.second))) {
                    seen.insert(node(s.first, s.second));
                    q.push(s);
                }
        }
        return false;
    }
};

```


2. ##### math

- The solution exists only if `z = ax + by s.t. a, b (- R`.
- `x = m * g, y = n * g  ->   z = (am + bn) * g` g is gcd.

```c++
class Solution {
public:
    int gcd(int x, int y) {
        while (y) {
            x = x % y;
            swap(x, y);
        }
        return x;
    }
    bool canMeasureWater(int x, int y, int z) {
        return z == 0 || (x + y >= z && z % gcd(x, y) == 0);
    }
};
```