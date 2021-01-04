---
title: Freedom Trail
date: 2021-01-04
---
In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", and use the dial to spell a specific keyword in order to open the door.

Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at 12:00 direction. You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character key[i]:

You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step. The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction, where this character must equal to the character key[i].
If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step. After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
Example:


 
Input: ring = "godding", key = "gd"
Output: 4
Explanation:
For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
Also, we need 1 more step for spelling.
So the final output is 4.
Note:

Length of both ring and key will be in range 1 to 100.
There are only lowercase letters in both strings and might be some duplcate characters in both strings.
It's guaranteed that string key could always be spelled by rotating the string ring.


#### Solutions

1. ##### greedy approach

- For each character in the key, simply move to the nearest position around the current position.
- The example below shows that this greedy approach will fail in cases when later decisions require non-optimal decisions before.

```
"xaxxxxxbax"
"ab"

For the first character, the nearest position is clearly the left a, the final cost is `1 + 4 + 2 = 7`

However the best solution requires to firstly move to the right a, then move left, thus the final cost is `2 + 1 + 2 = 5`
```

```cpp
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<vector<int>> pos(26);
        for (int i = 0; i < ring.size(); i++)
            pos[ring[i] - 'a'].push_back(i);
        // find the nearest position with the same character
        auto nextpos = [&](int cur, char c){
            int mindis = INT_MAX, next = cur;
            for (auto p : pos[c - 'a']) {
                if (p == cur) return cur;
                int d = abs(cur - p); 
                int curd = min(d, (int)ring.size() - d);
                if (curd < mindis) {
                    mindis = curd;
                    next = p;
                }
            }
            return next;
        };

        int cur = 0, res = 0;
        for (auto c : key) {
            int next = nextpos(cur, c);
            int d = abs(next - cur);
            res += min(d, (int)ring.size() - d) + 1;
            cur = next;
        }

        return res;
    }
};
```

2. ##### recursion O(n ^ k) or O(nk)

- As every decision in the current step may leads to the final optimal solution, in each step, we traverse all solutions and choose the best among them by using recursion.

```cpp
class Solution {
public:
    
    int findRotateSteps(string ring, string key) {
        vector<vector<int>> pos(26);
        for (int i = 0; i < ring.size(); i++)
            pos[ring[i] - 'a'].push_back(i);

        function<int(int, int)> solve = [&](int cur, int i) {
            if (i >= key.size()) return 0;
            int res = INT_MAX;
            for (auto p : pos[key[i] - 'a']) {
                int d = abs(cur - p);
                int curd = min(d, (int)ring.size() - d);
                res = min(res, curd + 1 + solve(p, i + 1));
            }

            return res;
        };

        return solve(0, 0);
    }
};
```

- Use hashmap to cache the results of overlapping subprograms, i.e the same `(cur, i)`


```cpp
class Solution {
public:
    
    int findRotateSteps(string ring, string key) {
        vector<vector<int>> pos(26);
        for (int i = 0; i < ring.size(); i++)
            pos[ring[i] - 'a'].push_back(i);

        vector<vector<int>> memo(ring.size(), vector<int>(key.size(), -1));

        function<int(int, int)> solve = [&](int cur, int i) {
            if (i >= key.size()) return 0;
            if (memo[cur][i] != -1)
                return memo[cur][i];
            int res = INT_MAX;
            for (auto p : pos[key[i] - 'a']) {
                int d = abs(cur - p);
                int curd = min(d, (int)ring.size() - d);
                res = min(res, curd + 1 + solve(p, i + 1));
            }

            return memo[cur][i] = res;
        };

        return solve(0, 0);
    }
};
```


3. ##### dynamic programming O(nk)

```cpp
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<vector<int>> pos(26);
        for (int i = 0; i < ring.size(); i++)
            pos[ring[i] - 'a'].push_back(i);

        int n = ring.size();
        vector<int> dp(n, INT_MAX / 2);
        dp[0] = 0;
        for (auto c : key) {
            vector<int> dp1(n, INT_MAX / 2);
            for (auto cur : pos[c - 'a'])
                for (int prev = 0; prev < n; prev++) {
                    int d = abs(cur - prev);
                    dp1[cur] = min(dp1[cur], dp[prev] + min(d, n - d) + 1);
                }
            dp = move(dp1);
        }

        return *min_element(dp.begin(), dp.end());
    }
};
```