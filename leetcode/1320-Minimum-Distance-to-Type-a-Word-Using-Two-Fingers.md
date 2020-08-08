#### You have a keyboard layout as shown above in the XY plane, where each English uppercase letter is located at some coordinate, for example, the letter A is located at coordinate (0,0), the letter B is located at coordinate (0,1), the letter P is located at coordinate (2,3) and the letter Z is located at coordinate (4,1).

Given the string word, return the minimum total distance to type such string using only two fingers. The distance between coordinates (x1,y1) and (x2,y2) is |x1 - x2| + |y1 - y2|. 

Note that the initial positions of your two fingers are considered free so don't count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.

 
```
Example 1:

Input: word = "CAKE"
Output: 3
Explanation: 
Using two fingers, one optimal way to type "CAKE" is: 
Finger 1 on letter 'C' -> cost = 0 
Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
Finger 2 on letter 'K' -> cost = 0 
Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
Total distance = 3

Example 2:

Input: word = "HAPPY"
Output: 6
Explanation: 
Using two fingers, one optimal way to type "HAPPY" is:
Finger 1 on letter 'H' -> cost = 0
Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
Finger 2 on letter 'P' -> cost = 0
Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
Total distance = 6

Example 3:

Input: word = "NEW"
Output: 3

Example 4:

Input: word = "YEAR"
Output: 7
```

 

#### Constraints:

-    2 <= word.length <= 300
-    Each word[i] is an English uppercase letter.


#### Solutions

1. ##### dynamic programming

- `dp[i][c1][c2`] represents the minimum cost when typed `word[i]` with one finger on `c1` and the other on `c2`.

```c++
class Solution {
public:
    int dis(int l, int r) {
        int x1 = l / 6, y1 = l % 6;
        int x2 = r / 6, y2 = r % 6;
        return abs(x1 - x2) + abs(y1 - y2);
    }
    int minimumDistance(string word) {
        int n = word.size();
        vector<vector<vector<int>>> dp(n + 1, 
            vector<vector<int>>(26, vector<int>(26, 0x3f3f3f3f)));
        // initially we can push one/both finger in the first character with zero cost.
        for (int i = 0; i < 26; i++) {
            dp[0][word[0] - 'A'][i] = 0;
            dp[0][i][word[0] - 'A'] = 0;
        }

        for (int i = 1; i < n; i++) {
            auto c = word[i] - 'A', prevc = word[i - 1] - 'A';
            for (int c1 = 0; c1 < 26; c1++)
                for (int c2 = 0; c2 < 26; c2++) {
                    if (c1 != prevc && c2 != prevc) continue;
                    int pcost = dp[i - 1][c1][c2];
                    dp[i][c1][c] = min(dp[i][c1][c], pcost + dis(c, c2));
                    dp[i][c][c2] = min(dp[i][c][c2], pcost + dis(c, c1));
                }
        }

        int res = INT_MAX;
        for (int i = 0; i < 26; i++) {
            res = min(res, dp[n - 1][i][word[n - 1] - 'A']);
            res = min(res, dp[n - 1][word[n - 1] - 'A'][i]);
        }
    
        return res;
    }
};
```