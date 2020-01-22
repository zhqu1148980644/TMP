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

```c++
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