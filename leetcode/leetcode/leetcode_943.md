---
title: Find the Shortest Superstring
date: 2021-01-04
---
Given an array A of strings, find any smallest string that contains each string in A as a substring.

We may assume that no string in A is substring of another string in A.
 

```
Example 1:

Input: ["alex","loves","leetcode"]
Output: "alexlovesleetcode"
Explanation: All permutations of "alex","loves","leetcode" would also be accepted.

Example 2:

Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
Output: "gctaagttcatgcatc"
```

 

#### Note:

-    1 <= A.length <= 12
-    1 <= A[i].length <= 20


#### Solutions


1. ##### dfs O(n!) S(n2)

- `com` is an integer representing strings have been used in the current path.

```cpp
class Solution {
public:
    vector<vector<int>> overlap;
    vector<int> minpath;
    int minlen = INT_MAX;

    void dfs(vector<string> & A, vector<int> & path, int len, int num, int com) {
        if (len >= minlen)
            return;
        if (num == path.size()) {
            if (len < minlen) {
                minlen = len;
                minpath = path;
            }
            return;
        }
        for (int i = 0; i < path.size(); i++) {
            if (com & (1 << i)) continue;
            path[num] = i;
            int newlen =  num == 0 ? A[i].size() : len + A[i].size() - overlap[path[num - 1]][i];
            dfs(A, path, newlen, num + 1, com | (1 << i));
        }
    }

    string shortestSuperstring(vector<string>& A) {
        int n = A.size();
        
        overlap = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                for (int k = min(A[i].size(), A[j].size()); k > 0 ; k--)
                    if (A[i].substr(A[i].size() - k) == A[j].substr(0, k)) {
                        overlap[i][j] = k;
                        break;
                    }
            }
        
        vector<int> path(n);
        dfs(A, path, 0, 0, 0);

        path = move(minpath);
        string res = A[path[0]];
        for (int i = 1; i < path.size(); i++)
            res += A[path[i]].substr(overlap[path[i - 1]][path[i]]);
        

        return res;
    }
};
```


2. ##### dynamic programming O(2^n * n2) S(n2)

- reference: https://leetcode.com/problems/find-the-shortest-superstring/discuss/194932/Travelling-Salesman-Problem
- `dp[set][i]` represents the maximum overlap with strings in `set` and the last string is `s[i]`.
- It's a `Travelling Salesman Problem`. ie: Find the shortest path which visits every node extractly once.
- Codes below find the permutation with the maximum length of overlaps which is similar to the official answer.
    - These two criterias are basically the same.

```cpp
class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        if (A.size() == 1) return A[0];
        int n = A.size();
        vector<vector<int>> overlap(n, vector<int>(n));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = min(A[i].size(), A[j].size()); k > 0; k--)
                    if (A[i].substr(A[i].size() - k) == A[j].substr(0, k)) {
                        overlap[i][j] = k;
                        break;
                    }

        vector<vector<int>> dp(1 << n, vector<int>(n, -1));
        vector<vector<int>> path(1 << n, vector<int>(n));

        // iterate over all possible sets. from empty to whole
        for (int s = 1; s < (1 << n); s++) {
            // adding items to set.
            for (int cur = 0; cur < n; cur++) {
                if ((s & (1 << cur)) > 0) {
                    int prevs = s - (1 << cur);
                    if (prevs == 0) { dp[s][cur] = 0; continue; }
                    // the last item of previous set
                    for (int prev = 0; prev < n; prev++) {
                        int newov = dp[prevs][prev] + overlap[prev][cur];
                        if ((prevs & (1 << prev)) && newov > dp[s][cur]) {
                            dp[s][cur] = newov;
                            path[s][cur] = prev;
                        }
                    }
                }
            }
        }
        // build result string reversely.
        string res;
        int curs = (1 << n) - 1, next;
        int cur = max_element(dp[curs].begin(), dp[curs].end()) - dp[curs].begin();
        while (curs > 0) {
            int len = A[cur].size() - (res.size() ? overlap[cur][next] : 0);
            res = A[cur].substr(0, len) + res;
            next = cur;
            cur = path[curs][cur];
            curs -= (1 << next);
        }

        return res;
    }
};
```


2. ###### dynamic programming with memoization O(2^n * n2) S(2^n + n2)

- Got TLE.

```cpp
class Solution {
public:
    vector<vector<int>> dp;
    vector<vector<int>> path;
    vector<vector<int>> overlap;
    int n;

    int solve(int mask, int i) {
        if (dp[mask][i] >= 0)
            return dp[mask][i];
        mask -= (1 << i);
        for (int prev = 0; prev < n; prev++) {
            if (mask & (1 << prev)) {
                int newov = solve(mask, prev) + overlap[prev][i];
                if (newov > dp[mask][i]) {
                    dp[mask][i] = newov;
                    path[mask + (1 << i)][i] = prev;
                }
            }
        }
        return dp[mask][i];
    }

    string shortestSuperstring(vector<string>& A) {
        if (A.size() == 1) return A[0];
        n = A.size();
        overlap = vector<vector<int>>(n, vector<int>(n));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int m = min(A[i].size(), A[j].size());
                for (int k = m; k > 0; k--)
                    if (A[i].substr(A[i].size() - k) == A[j].substr(0, k)) {
                        overlap[i][j] = k;
                        break;
                    }
            }

        dp = vector<vector<int>>(1 << n, vector<int>(n, -1));
        path = vector<vector<int>>(1 << n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[1 << i][i] = 0;
        int maxov = -1, last = 0;
        for (int i = 0; i < n; i++) {
            int tmp = solve((1 << n) - 1, i);
            if (tmp > maxov) {
                maxov = tmp;
                last = i;
            }
        }

        vector<int> pathv(n);
        int curs = (1 << n) - 1, index = n - 1;
        while (curs > 0) {
            pathv[index--] = last;
            int cur = last;
            last = path[curs][last];
            curs -= (1 << cur);
        }

        string res = A[pathv[0]];
        for (int i = 1; i < n; i++)
            res += A[pathv[i]].substr(overlap[pathv[i - 1]][pathv[i]]);

        return res;
    }
};
```