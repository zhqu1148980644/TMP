---
title: Dungeon Game
date: 2021-01-04
---
#### The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

 

#### Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

```
-2(k)  -3	 3
-5	   -10	 1
10	   30	 -5(p)
```

#### Note:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.


#### Solutions

1. ##### dynamic programming

- For standard dp problem, we need to start from the top-left corner of the dp table. However this problem require us to calculate the minimum health at this corner.
- A intuitive thought is that we can calculate from the right-bottom and back to this corner as the minimum health are required to get to the princess is definitely depends on the room where the princess are imprisoned. And we can iteratively fill in the dp table where `dp[i][j] <= 0` means the minimum health are required when start at `dp[i][j]`.
    - `dp[i][j] = -5` means when starting at this point, the knight must have at least 6 health, otherwise his health will reduces to below zero(dead) during the path to the princess.
- Remember to constrain the minimum health to `0` in dp table(can not work through a room if already died).
- dp formulas:
    - `dp[i, j] = dungeon[i, j] + max(dp[i + 1, j], dp[i, j + 1])`
    - `dp[i, j] = min(0, dp[i, j])`

```cpp
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int maxr = dungeon.size() - 1;
        int maxc = dungeon[0].size() - 1;
        int minih[maxc + 1]; minih[maxc] = 0;
        for (int i = 0; i < maxc; i++) minih[i] = INT_MIN;
        for (int i = maxr; i >= 0; i--) {
            // init the last item of each row in 2d dp table.
            minih[maxc] = min(0, dungeon[i][maxc] + minih[maxc]);
            for (int j = maxc - 1; j >= 0; j--)
                minih[j] = min(0, dungeon[i][j] + (max(minih[j], minih[j + 1])));
        }
        // this is a non-negative(may be zero) integer.
        // -5 means at least 6 health are required to pass this room and future rooms till she reaches the end with health 1.
        return -minih[0] + 1;
    }
};
```