---
title: Minimum Jumps to Reach Home
date: 2021-01-04
---
A certain bug's home is on the x-axis at position x. Help them get there from position 0.

The bug jumps according to the following rules:

It can jump exactly a positions forward (to the right).
It can jump exactly b positions backward (to the left).
It cannot jump backward twice in a row.
It cannot jump to any forbidden positions.
The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.

Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.

 

Example 1:

Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
Output: 3
Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
Example 2:

Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
Output: -1
Example 3:

Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
Output: 2
Explanation: One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug home.
 

Constraints:

1 <= forbidden.length <= 1000
1 <= a, b, forbidden[i] <= 2000
0 <= x <= 2000
All the elements in forbidden are distinct.
Position x is not forbidden.


#### Solutions

1. ##### bfs

- Compared to the ordinary bfs, there are two states in each position, representing the cost when reaches the position at the first time by moving forward/backward.

```cpp
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        if (x == 0) return 0;
        vector<bool> forbid(4001);
        for (auto pos : forbidden)
            forbid[pos] = true;
        
        bool vis[4001][2];
        memset(vis, 0, sizeof(vis));
        queue<int> q; q.emplace(0);
        vis[0][0] = true;

        int n = 4001, step = 0;
        while (q.size()) {
            int size = q.size();
            // traversing one level
            while (size--) {
                int cur = q.front() % n;
                int back = q.front() / n;
                q.pop();
                // reaches the target point
                if (cur + a == x || (!back && cur - b == x))
                    return step + 1;
                // move forward
                if (cur + a < n && !vis[cur + a][0] && !forbid[cur + a]) {
                    vis[cur + a][0] = true;
                    q.emplace(cur + a);
                }
                // move backward only when the previous step is not moving backwards.
                if (!back && cur - b >= 0 && !vis[cur - b][1] && !forbid[cur - b]) {
                    vis[cur - b][1] = true;
                    q.emplace(n + cur - b);
                }
            }
            step++;
        }

        return -1;
    }
};
```