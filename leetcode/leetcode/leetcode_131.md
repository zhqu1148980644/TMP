---
title: Palindrome Partitioning
date: 2021-01-04
---
#### Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

```
Example:

Input: "aab"
Output:
[
  ["aa","b"],
 
 ["a","a","b"]
]
```

#### Solutions



1. ##### straight forward O(2^n)

- All positions can be a partion points, thus the time complexity = (pos 0 issplit or not) * () * () .... = 2^n
- Iterativey find the next split point to generate valid palindrome, store partitions that can partition the original string into non-overlapping palindrome chunks.
- Backtrack to the last split point if the remaining string can not be patitioned further.

```cpp
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        return [[s[:i]] + parts
                for i in range(1, len(s) + 1)
                if s[:i] == s[:i][::-1]
                for parts in self.partition(s[i:])] or [[]]

```

dfs

```python
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        def part(path, s):
            if not s:
                res.append(path)
            for i in range(1, len(s) + 1):
                if s[:i] == s[:i][::-1]:
                    part(path + [s[:i]], s[i:])
        res = []
        part([], s)
        return res
```

2. ##### dfs with palindrome dp table O(2^n)

- Use method in `problem 5` to check if a substring is a valid palindrome for every substring and store the result in a dp table.

```cpp
class Solution {
public:
    vector<vector<bool>> ispalin;
    vector<vector<string>> res;
    vector<string> path;

    void dfs(string & s, int st) {
        if (st == s.size()) {
            res.push_back(path);
            return;
        }
        for (int i = st; i < s.size(); i++) {
            // find the next split point
            if (!ispalin[st][i]) continue;
            path.push_back(s.substr(st, i - st + 1));
            dfs(s, i + 1);
            path.pop_back();
        }
    }

    vector<vector<string>> partition(string s) {
        ispalin = vector<vector<bool>>(s.size(), vector<bool>(s.size()));
        // fill ispalindrome dp table
        for (int j = 0; j < s.size(); j++)
            for(int i = 0; i <= j; i++)
                ispalin[i][j] = s[i] == s[j] && (j - i < 2 || ispalin[i + 1][j - 1]);
        dfs(s, 0);
        return res;
    }
};
```

- borrowed from others.
- fill the dp table when backtracking, the filling order lools  like
```
...
 .
  ....
   .
    .
     .....
```


```cpp
class Solution {
private:
    vector<string> path;
    vector<vector<string>> res;
    vector<vector<bool>> isPalin;

    void dfs(string & s, int start) {
        if (start == s.size()) {
            this->res.push_back(path); return;
        }
        for (int i = start; i < s.size(); i++) {
            if (s[start] != s[i] || !(i - start < 2 || isPalin[start + 1][i - 1]))
                continue;
            isPalin[start][i] = true;
            path.push_back(s.substr(start, i - start + 1));
            dfs(s, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        this->isPalin = move(dp);
        dfs(s, 0);
        return res;
    }

};
```

3. ##### dynamic programming O(n2)

- borrowed from others.
- Former solutions could cause duplicate sub partitions when backtracking while this solution uses another dp table to cache all combination of palindromes for strings ends at different position.
- Cutting palindromes when filling the dp table column by column.
- Bulding results from bottom to up.

- `res[pos]`. represents all solutions that end with the pos character(`right closed`).
- Whenever we find a new `palindrome[l:r]`, then `res[r + 1]`(solutions ends with r + 1) can be calculated by extending every solution in `res[l]` with this new palindrome.

```cpp
class Solution {
public:
    using Path = vector<string>;
    vector<vector<string>> partition(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size()));
        vector<vector<Path>> res(s.size() + 1);
        res[0].push_back({});

        for (int j = 0; j < s.size(); j++)
            for (int i = 0; i <= j; i++)
                if (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    string palin = s.substr(i, j - i + 1);
                    for (auto path : res[i]) {
                        path.push_back(palin);
                        res[j + 1].push_back(path);
                    }
                }
        
        return res[s.size()];
    }
};
```

python version

- This version finds the palindrome from the end to the start.
- `dp[i]` represents solutions of `string[i:]`
- Whenever meets a new palindrome `s[i:j]`, then `dp[i]` can be calculated by prepending every solutions in `dp[j + 1]` with this new palindrome prefix.

```python
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        dp = [[] for _ in range(len(s) + 1)]
        dp[-1].append([])

        for i in range(len(s) - 1, -1, -1):
            # or for i in range(i, len(s)):
            for j in range(len(s) - 1, i - 1, -1):
                if s[i:j + 1] == s[i: j + 1][::-1]:
                    for each in dp[j + 1]:
                        dp[i].append([s[i: j + 1]] + each)
        return dp[0]
```