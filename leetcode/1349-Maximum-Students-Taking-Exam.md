Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.

Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible..

Students must be placed in seats in good condition.

 
```
Example 1:

Input: seats = [["#",".","#","#",".","#"],
                [".","#","#","#","#","."],
                ["#",".","#","#",".","#"]]
Output: 4
Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam. 

Example 2:

Input: seats = [[".","#"],
                ["#","#"],
                ["#","."],
                ["#","#"],
                [".","#"]]
Output: 3
Explanation: Place all students in available seats. 

Example 3:

Input: seats = [["#",".",".",".","#"],
                [".","#",".","#","."],
                [".",".","#",".","."],
                [".","#",".","#","."],
                ["#",".",".",".","#"]]
Output: 10
Explanation: Place students in available seats in column 1, 3 and 5.
```

 

#### Constraints:

-    seats contains only characters '.' and'#'.
-    m == seats.length
-    n == seats[i].length
-    1 <= m <= 8
-    1 <= n <= 8


#### Solutions

1. ##### dynamic programming with iteration O(m * 2^2n)

- Since each row only depends on the previous row, we can solve this problem by dynamic programming.
- `dp[i][state]` represents the total number of students that can take the exam without any cheating in first `i` rows and the arrangement of the `i'th` row is `state`.
    - An arrangement can be represented by an `integer` as the number of columns is smaller than `8`.
    - For example, `##0##1#10` can be represented as `2^5 + 2^7`.

```c++
class Solution {
public:
    inline int countone(int n) {
        int res = 0;
        while (n) {
            res++; n &= (n - 1);
        }
        return res;
    }

    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size(), n = seats[0].size();
        int mstate = 1 << n;
        vector<int> dp(mstate);
        
        for (int i = 1; i <= m; i++) {
            vector<int> dp1(mstate);
            for (int prev = 0; prev < mstate; prev++) {
                for (int cur = 0; cur < mstate; cur++) {
                    bool valid = true;
                    for (int j = 0; j < n; j++) {
                        int bit = 1 << j;
                        // only check seat positions in the current arrangement.
                        if (!(cur & (1 << j))) continue;
                        if (seats[i - 1][j] == '#' // broken seat
                        || ((bit << 1) & cur)      // left cheating
                        || ((bit >> 1) & cur)      // right cheating
                        || (1 & (prev >> (j + 1))) // left-up and right-up cheatings
                        || (j && (1 & (prev >> (j - 1))))) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid)
                        dp1[cur] = max(dp1[cur], dp[prev] + countone(cur));
                }
            }
            swap(dp1, dp);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

2. ##### recursion with memoization

- In the first version, the calculation of all states is unnecessary, a top-down strategy can save a huge amount of running time though the time complexity is the same.

```c++

```

3. ##### graph

- reference: https://leetcode-cn.com/problems/maximum-students-taking-exam/solution/er-fen-tu-zui-da-du-li-ji-by-lightcml/