---
title: Nqueens
date: 2021-01-04
---
#### The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

```
Example:

Input: 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
```

##### Solutions


1. ##### dfs with stack

- Since all path traversed by depth first search is unique, this problem is the simplified version of `problem 51`

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
    int totalNQueens(int n) {
        vector<bool> col(n, false);
        s.push_back(pos(0, -1));
        int count = 0;

        while (!s.empty()) {
            auto & p = s.back();
            p.second++;
            while (p.second < n && contain(p))  
                p.second++;
            if (p.second == n) {
                s.pop_back();
            } else {
                if (s.size() == n)
                    count++;
                else
                    s.push_back(pos(p.first + 1, -1));
            }
        }
        return count;
    }
};
```


2. ##### backtrack with recursion


```cpp
class Solution {
public:
    using pos = pair<int, int>;
    vector<pos> qs;
    int res = 0;

    void solve(int n, int currow) {
        if (currow >= n) {
            res++; return;
        }
        qs.push_back({currow, 0});
        for (int j = 0; j < n; j++) {
            auto & cur = qs.back();
            cur.second = j;
            if (contain(cur)) continue;
            solve(n, currow + 1);
        }
        qs.pop_back();
    }
    bool contain(const pos & p2) {
        for (auto & p1 : qs) {
            if (p1 == p2) continue;
            if ((p1.second == p2.second)
                    || (p1.first + p1.second == p2.first + p2.second)
                    || (p1.first - p1.second == p2.first - p2.second))
                return true;
        }
        return false;
    }
    int totalNQueens(int n) {
        solve(n, 0);
        return res;
    }
};
```


3. ##### iteration

- Use the code pattern in `problem 77`.

```cpp
class Solution {
public:
    bool valid(vector<int> & com, int curr) {
        int curc = com[curr];
        for (int r = 0; r < curr; r++) {
            int c = com[r];
            // three cross cases, same column, same diagonal, same anti-diagonal
            if (c == curc 
            || curc - c == curr - r 
            || curc - c == r - curr)
                return false;
        }
        return true;
    }
    int totalNQueens(int n) {
        // com[r] represents the point grid[r][com[r]]
        vector<int> com(n + 1, -1);
        int res = 0, pos = 0;

        while (pos >= 0) {
            com[pos]++;
            if (pos >= n) { // record results, go back to the top row
                res++;
                pos--;
            }
            else if (com[pos] >= n) // No valid point, go back to the lower row
                pos--;
            else if (valid(com, pos)) // find valid pint, go to upper row
                com[++pos] = -1;      // must set to -1
        }

        return res;
    }
};
```
