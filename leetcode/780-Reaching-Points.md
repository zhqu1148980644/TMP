A move consists of taking a point (x, y) and transforming it to either (x, x+y) or (x+y, y).

Given a starting point (sx, sy) and a target point (tx, ty), return True if and only if a sequence of moves exists to transform the point (sx, sy) to (tx, ty). Otherwise, return False.

Examples:
Input: sx = 1, sy = 1, tx = 3, ty = 5
Output: True
Explanation:
One series of moves that transforms the starting point to the target is:
(1, 1) -> (1, 2)
(1, 2) -> (3, 2)
(3, 2) -> (3, 5)

Input: sx = 1, sy = 1, tx = 2, ty = 2
Output: False

Input: sx = 1, sy = 1, tx = 1, ty = 1
Output: True

Note:

sx, sy, tx, ty will all be integers in the range [1, 10^9].

#### Solutions

1. ##### backtrack

- Reversely search for the source.
- Time limit exceed

```c++
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx >= sx && ty >= sy) {
            if (tx == sx && ty == sy)
                return true;
            if (tx > ty)
                tx = tx - ty;
            else
                ty = ty - tx;
        }
        return false;
    }
};
```

- optimized version: use mod to speed up the search speed(multiple plus/minus)
- if `ty == sy` at some point, must manually check otherwize `tx % ty` would be smaller than `sy`.

```c++
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if (tx < sx || ty < sy) return false;
        while (tx >= sx && ty >= sy) {
            if (tx > ty) {
                if (ty == sy)
                    return (tx - sx) % sy == 0;
                tx %= ty;
            }
            else {
                if (tx == sx)
                    return (ty - sy) % sx == 0;
                ty %= tx;
            }
        }
        return sx == tx && sy == ty;
    }
};
```