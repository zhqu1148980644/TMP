Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.


#### Solutions


1. ##### dynamic programming O(n^1.5)


```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> squares;
        for (int i = 1; i * i <= n; i++)
            squares.push_back(i * i);

        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
            for (auto sq : squares) {
                if (sq > i) break;
                dp[i] = min(dp[i], dp[i - sq] + 1);
            }
        
        return dp[n];
        
    }
};
```


2. ##### dfs

```c++
class Solution {
public:
    bool solve(unordered_set<int> & squares, int n, int num) {
        if (num == 1)
            return squares.count(n);
        // the ordering of sqs is not the same as the insertion order.
        for (auto sq : squares) {
            if (sq > n) continue;
            if (solve(squares, n - sq, num - 1))
                return true;
        }
        return false;
    }
    int numSquares(int n) {
        unordered_set<int> squares;
        for (int i = 1; i * i <= n; i++)
            squares.insert(i * i);
        
        for (int num = 1; num <= n; num++)
            if (solve(squares, n, num)) return num;
        return n;
    }
};
```


3. ##### bfs

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> squares(floor(sqrt(n)));
        for (int i = 1; i <= squares.size(); i++)
            squares[i - 1] = i * i;
        
        queue<int> q; q.push(n);
        
        int level = 0;
        while (!q.empty()) {
            level++;
            int size = q.size();
            while (size--) {
                n = q.front(); q.pop();
                for (auto sq : squares) {
                    if (sq > n) break;
                    if (n == sq) return level;
                    q.push(n - sq);
                }
            }
        }
        return 0;
    }
};
```

4. ##### math

- four-square and three-square theorems
- f `n == 4^a(8b + 7)`, then n can be represented as the sum of `four` squares


```c++
class Solution {
public:
    bool issquaire(int n) {
        int r = n;
        // newton method
        while (r * r > n)
            r = (r + n / r) / 2;
        return r * r == n;
    }
    int numSquares(int n) {
        int tmp = n;
        while (tmp % 4 == 0)
            tmp /= 4;
        if (tmp % 8 == 7)
            return 4;

        if (issquaire(n))
            return 1;

        for (int i = 1; i * i <= n; i++) {
            if (issquaire(n - i * i))
                return 2;
        }
        return 3;
    }
};
```