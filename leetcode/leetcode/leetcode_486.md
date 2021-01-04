---
title: Predict the Winner
date: 2021-01-04
---
Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

```
Example 1:

Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return False.

Example 2:

Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
```

#### Note:

-    1 <= length of the array <= 20.
-    Any scores in the given array are non-negative integers and will not exceed 10,000,000.
-    If the scores of both players are equal, then player 1 is still the winner.


#### Solutions

1. ##### straight forward O(2**n)

- Formulate the whole game process.
- `score(i, j)` represents the maximum score for the first(relative) player with `nums[i:j]`
- In each time, a player has two choice, after each choice, the number of spaces reduces 1. Thus the time complexity is `2**n`.

```cpp
class Solution {
public:
    int score(vector<int> & nums, int i, int j) {
        if (i == j)
            return nums[i];
        // two possibilities, return the maximum score
        // It is minus because the score returned belongs to another player.
        int score1 = nums[i] - score(nums, i + 1, j);
        int score2 = nums[j] - score(nums, i, j - 1);
        return max(score1, score2);
    }
    bool PredictTheWinner(vector<int>& nums) {
        return score(nums, 0, nums.size() - 1) >= 0;
    }
};
```

2. ##### dynamic programming

- `dp[i][j]` represents the difference between my(relative) score and the other one's score.

```cpp
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> dp(len, vector<int>(len));
        for (int j = 0; j < len; j++)
            for (int i = j; i >=0; i--) {
                if (i == j)
                    dp[i][j] = nums[i];
                else {
                    // my score deduce the other one's score.
                    int score1 = nums[i] - dp[i + 1][j];
                    int score2 = nums[j] - dp[i][j - 1];
                    dp[i][j] = max(score1, score2);
                }
            }
        return dp[0][len - 1] >= 0;
    }
};
```

- We can also choose to fill the dp table row by row and only utilize a single vector.
- If the number of items is even, the first player will always win.
- reference: https://leetcode-cn.com/problems/predict-the-winner/comments/78786

```cpp
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int len = nums.size();
        if (len % 2 == 0)
            return true;
        vector<int> dp(len);

        for (int i = len - 1; i >= 0; i--) {
            dp[i] = nums[i];
            for (int j = i + 1; j < len; j++)
                dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
        }

        return dp[len - 1] >= 0;
    }
};
```

or column by column

```cpp
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int len = nums.size();
        if (len % 2 == 0)
            return true;
        vector<int> dp(len);

        for (int j = 0; j < len; j++) {
            dp[j] = nums[j];
            for (int i = j - 1; i >= 0; i--) {
                dp[i] = max(nums[i] - dp[i + 1], nums[j] - dp[i]);
            }
        }
        return dp[0] >= 0;
    }
};
```
