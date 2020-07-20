Given the coordinates of four points in 2D space, return whether the four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array with two integers.

Example:

Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
 

Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four equal angles (90-degree angles).
Input points have no order.

#### Solutions

1. ##### math

```c++
class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        auto norm = [](auto & v1, auto & v2) {
            int i = v2[0] - v1[0];
            int j = v2[1] - v1[1];
            return sqrt(i * i + j * j);
        };
        vector<double> el {
            norm(p1, p2), norm(p1, p3), norm(p1, p4), 
            norm(p2, p3), norm(p2, p4), norm(p3, p4)
        };
        sort(el.begin(), el.end());
        return el[0] > 0 && count(el.begin(), el.begin() + 4, el[0]) == 4 
                && el[4] == el[5] 
                && 2 * pow(el[0], 2) - pow(el[5], 2) < 1e-6;
    }
};
```