---
title: Robot Bounded In Circle
date: 2021-01-04
---
On an infinite plane, a robot initially stands at (0, 0) and faces north.  The robot can receive one of three instructions:

"G": go straight 1 unit;
"L": turn 90 degrees to the left;
"R": turn 90 degress to the right.
The robot performs the instructions given in order, and repeats them forever.

Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.

 

Example 1:

Input: "GGLLGG"
Output: true
Explanation: 
The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.
Example 2:

Input: "GG"
Output: false
Explanation: 
The robot moves north indefinitely.
Example 3:

Input: "GL"
Output: true
Explanation: 
The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...
 

Note:

1 <= instructions.length <= 100
instructions[i] is in {'G', 'L', 'R'}

#### Solutions

1. ##### math

- there are two cases that the robot would be in a circle
    - after one loop of instructions, the robot's position remain unchanged.
    - the direction are different than the initial direction, we can draw a line between the initial point and the final point after one loop, than as long as robot continues go forward, these lines would eventualy make up a polygan.


```cpp
class Solution {
public:
    int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    void move(const string & s, int & r, int & c, int & curo) {
         for (auto ch : s) {
            if (ch == 'G') {
                r += dirs[curo][0];
                c += dirs[curo][1];
            }
            else if (ch == 'L')
                curo = (curo + 4 - 1) % 4;
            else
                curo = (curo + 1) % 4;
        }        
    }
    bool isRobotBounded(string instructions) {
        int r = 0, c = 0, curo = 1;
        move(instructions, r, c, curo);
        return (r == 0 && c == 0) || curo != 1; 
    }
};
```
