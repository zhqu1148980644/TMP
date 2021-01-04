---
title: Maximum Height by Stacking Cuboids
date: 2021-01-04
---
Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.

You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj. You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.

Return the maximum height of the stacked cuboids.

 

Example 1:



Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
Output: 190
Explanation:
Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
Cuboid 0 is placed next with the 45x20 side facing down with height 50.
Cuboid 2 is placed next with the 23x12 side facing down with height 45.
The total height is 95 + 50 + 45 = 190.
Example 2:

Input: cuboids = [[38,25,45],[76,35,3]]
Output: 76
Explanation:
You can't place any of the cuboids on the other.
We choose cuboid 1 and rotate it so that the 35x3 side is facing down and its height is 76.
Example 3:

Input: cuboids = [[7,11,17],[7,17,11],[11,7,17],[11,17,7],[17,7,11],[17,11,7]]
Output: 102
Explanation:
After rearranging the cuboids, you can see that all cuboids have the same dimension.
You can place the 11x7 side down on all cuboids so their heights are 17.
The maximum height of stacked cuboids is 6 * 17 = 102.
 

Constraints:

n == cuboids.length
1 <= n <= 100
1 <= widthi, lengthi, heighti <= 100

#### Solutions

1. ##### dynamic programming


```cpp
class Solution {
public:
    template <typename T>
    bool ok(T & sq1, T & sq2) {
        return (sq1[0] <= sq2[0] && sq1[1] <= sq2[1]) || (sq1[0] <= sq2[1] && sq1[1] <= sq2[0]);
    }
    int maxHeight(vector<vector<int>>& cuboids) {
        using State = __int128;
        
        int n = cuboids.size();
        vector<vector<int>> sorted;
        // for all possible rorations
        for (int i = 0; i < n; i++) {
            auto sq = cuboids[i];
            int w1 = sq[0], w2 = sq[1], w3 = sq[2];
            sorted.push_back({w1, w2, w3, i + 2});
            sorted.push_back({w1, w3, w2, i + 2});
            sorted.push_back({w2, w3, w1, i + 2});
        }
        // sort them by thier area and height
        sorted.push_back({0, 0, 0, 0, 0});
        sort(sorted.begin(), sorted.end(), [](auto & s1, auto & s2) {
            if (s1[2] == s2[2])
                return s1[0] * s1[1] <= s2[0] * s2[1];
            else
                return s1[2] <= s2[2];

        });
        
        vector<pair<int, State>> dp(sorted.size());
        dp[0].second &= 1;
        int res = 0;
        for (int j = 1; j < dp.size(); j++) {
            auto & sq2 = sorted[j];
            int h = sq2[2], maxh = h, maxi = 0;
            auto cur = (State{1} << sq2[3]);
            for (int i = j - 1; i >= 0; i--) {
                if ((dp[i].second & cur)  || !ok(sorted[i], sq2))
                    continue;
                if (dp[i].first + h > maxh) {
                    maxi = i;
                    maxh = dp[i].first + h;
                }
            }
            dp[j] = {maxh, dp[maxi].second | cur};
            res = max(res, maxh);
        }
        return res;
    }
};
```