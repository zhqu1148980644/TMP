---
title: Walking Robot Simulation
date: 2021-01-04
---
A robot on an infinite grid starts at point (0, 0) and faces north.  The robot can receive one of three possible types of commands:

-2: turn left 90 degrees
-1: turn right 90 degrees
1 <= x <= 9: move forward x units
Some of the grid squares are obstacles. 

The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])

If the robot would try to move onto them, the robot stays on the previous grid square instead (but still continues following the rest of the route.)

Return the square of the maximum Euclidean distance that the robot will be from the origin.

 

Example 1:

Input: commands = [4,-1,3], obstacles = []
Output: 25
Explanation: robot will go to (3, 4)
Example 2:

Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
Output: 65
Explanation: robot will be stuck at (1, 4) before turning left and going to (1, 8)
 

Note:

0 <= commands.length <= 10000
0 <= obstacles.length <= 10000
-30000 <= obstacle[i][0] <= 30000
-30000 <= obstacle[i][1] <= 30000
The answer is guaranteed to be less than 2 ^ 31.

#### Solutions

1. ##### straight forward

- Be careful about the order setting, faces north is `(0, 1)`.

```cpp
class Solution {
public:
    struct hash {
        size_t operator()(const pair<int, int> & p) const {
            return (p.first + 30000) * 30000 + (p.second + 30000);
        }
    };
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        const int n = 70000;
        unordered_set<pair<int, int>, hash> obs;
        for (auto & o : obstacles)
            obs.insert({o[0], o[1]});
        
        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int i = 0, j = 0, order = 0, res = 0;
        for (auto c : commands) {
            if (c == -2)
                order = (order + 4 - 1) % 4;
            else if (c == -1)
                order = (order + 1) % 4;
            else {
                auto & d = dirs[order];
                while (c--) {
                    i += d[0]; j += d[1];
                    if (obs.count({i, j})) {
                        i -= d[0]; j -= d[1];
                        break;
                    }
                }
                res = max(res, i * i + j * j);
            }
        }

        return res;
    }
};
```