---
title: Nqueens
date: 2021-01-04
---
#### The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

```
Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
```


#### Solutions

1. ##### dfs with stack

```cpp
typedef pair<int, int> pos;

class Solution {
private:
    vector<pos> s;
    
    bool contain(pos & p2) {
        for (auto & p1 : s) {
            if (p1 == p2) continue;
            if ((p1.second == p2.second) 
                || (p1.first + p1.second == p2.first + p2.second) 
                || (p1.first - p1.second == p2.first - p2.second))
                return true;
        }
        return false;
    }
    
public:
    vector<vector<string>> solveNQueens(int n) {
        s.push_back(pos(0, -1));
        vector<vector<pos>> res;
        
        while (!s.empty()) {
            auto & p = s.back();
            p.second++;
            // find the first one does not violate the rule
            while (p.second < n && contain(p))  
                p.second++;
            if (p.second == n) {
                // no other solutions, backtrace to the previous row
                s.pop_back();
            } else {
                if (s.size() == n)
                    res.push_back(s);
                else
                    // Next time we will start from the next row
                    s.push_back(pos(p.first + 1, -1));
            }
        }
        
        vector<vector<string>> strma;
        for (auto & solu : res) {
            vector<string> row(n, string(n, '.'));
            for (int i = 0; i < n; i++) {
                row[n - i - 1][solu[i].second] = 'Q';
            }
            strma.push_back(row);
        }
        
        return strma;
    }
};
```