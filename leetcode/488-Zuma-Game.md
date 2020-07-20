Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W). You also have several balls in your hand.

Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place). Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

 

```
Example 1:

Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW

Example 2:

Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

Example 3:

Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: G -> G[G] -> GG[G] -> empty 

Example 4:

Input: board = "RBYYBBRRB", hand = "YRBGB"
Output: 3
Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty 
```

 

#### Constraints:

-    You may assume that the initial row of balls on the table won’t have any 3 or more consecutive balls with the same color.
-    The number of balls on the table won't exceed 16, and the string represents these balls is called "board" in the input.
-    The number of balls in your hand won't exceed 5, and the string represents these balls is called "hand" in the input.
-    Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.


#### Solutions

- pruning:
    - Insert only if the insertion is meaningful.
    - For a continous substring(characters are the same), only try to insert at the front of this substring.

1. ##### dfs

```c++
class Solution {
public:
    string hand;
    int res = INT_MAX;

    void dfs(string b, string h) {
        if (!b.size()) {
            if (hand.size() - h.size() < res)
                res = hand.size() - h.size();
            return;
        }
            
        // only insert at the first position of `cc` or `c`
        for (int j, i = 0; i < b.size(); i = j) {
            j = i + 1;
            while (j < b.size() && b[j] == b[i]) j++;
            int len = j - i;
            if (len >= 3) {
                auto newb = b;
                newb.erase(i, len);
                return dfs(newb, h);
            }
            auto pos = h.find(b[i]);
            if (pos != string::npos) {
                auto newb = b, newh = h;
                newb.insert(newb.begin() + i, b[i]);
                newh.erase(pos, 1);
                dfs(newb, newh);
            }
        }
    }

    int findMinStep(string board, string hand) {
        this->hand = hand;
        dfs(board, hand);
        return res == INT_MAX ? -1 : res;
    }
};
```


2. ##### bfs

```c++
class Solution {
public:
    int findMinStep(string board, string hand) {
        queue<pair<string, string>> q;
        q.push({board, hand});
        int res = INT_MAX;

        while (!q.empty()) {
            auto b = q.front().first;
            auto h = q.front().second;
            q.pop();
            if (!b.size()) {
                if (hand.size() - h.size() < res)
                    res = hand.size() - h.size();
                continue;
            }
            // pruning: insert only at the front of a continuous substring
            for (int j, i = 0; i < b.size(); i = j) {
                j = i + 1;
                while (j < b.size() && b[j] == b[i]) j++;
                auto len = j - i;
                auto newb = b, newh = h;
                if (len >= 3)
                    newb.erase(i, len);
                else {
                    // pruning: insert only if the current character exists in hand
                    auto pos = h.find(b[i]);
                    if (pos != string::npos) {
                        newb.insert(newb.begin() + i, b[i]);
                        newh.erase(pos, 1);
                    }
                    else
                        continue;
                }
                q.push({newb, newh});
            } 
        }

        return res == INT_MAX ? -1 : res;
    }
};
```