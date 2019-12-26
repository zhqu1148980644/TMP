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


1. ##### backtracking with dfs

- Iterativey find the next split point to generate valid palindrome, store partitions that can partition the original string into non-overlapping palindrome chunks.
- Backtrack to the last split point if the remaining string can not be patitioned further.
- Use method in `problem 5` to check if a substring is a valid palindrome for every substring and store the result in a dp table.

```c++
class Solution {
private:
    vector<string> path;
    vector<vector<string>> res;
    vector<vector<bool>> isPalin;

    void dfs(string & s, int start) {
        if (start == s.size()) {
            this->res.push_back(path);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            // find the next split point that could generate palindrome
            if (!this->isPalin[start][i]) continue;
            path.push_back(s.substr(start, i - start + 1));
            dfs(s, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        this->isPalin = move(dp);
        // fill dp table
        for (int j = 0; j < s.size(); j++)
            for (int i = 0; i <= j; i++)
                isPalin[i][j] = s[i] == s[j]
                && (j - i < 2 || isPalin[i + 1][j - 1]);

        dfs(s, 0);
        return res;
    }

};
```


- borrowed from others.
- python version

```c++
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        return [[s[:i]] + parts
                for i in range(1, len(s) + 1)
                if s[:i] == s[:i][::-1]
                for parts in self.partition(s[i:])] or [[]]

```


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

- borrowed from others.
- fill the dp table when backtracking
- fill the dp table from bottom to top

```c++
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

2. dynamic programming

- borrowed from others.
- bottom to up. This can be seen as the revered version of the first python solution above.
- Solve the problem based on subproblem when filling the dp table.

- `res[pos]`. represents all solutions that end with the pos character(`right closed`).
- Whenever we find a new `palindrome[l:r]`, then `res[r + 1]`(solutions ends with r + 1) can be calculated by extending every solution in `res[l]` with this new palindrome.

```c++
typedef vector<string> Path;
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        // `res[pos]`. represents all solutions that end with the pos character(`right closed`).
        vector<vector<Path>> res(s.size() + 1, vector<Path>());
        res[0].push_back(Path());

        for (int r = 0; r < s.size(); r++)
            for (int l = 0; l <= r; l++)
                if (s[l] == s[r] && (r - l < 2 || dp[l + 1][r - 1])) {
                    dp[l][r] = true;
                    string palin = s.substr(l, r - l + 1);
                    // Whenever we find a new `palindrome[l:r]`, `res[r + 1]`(solutions ends with r + 1) can be calculated by extending every solution in `res[l]` with this new palindrome.
                    for (auto path : res[l]) {
                        path.push_back(palin);
                        res[r + 1].push_back(path);
                    }
                }
        return res[s.size()];
    }
};
```

python version

- This version finds the palindrome from the end to the start.
- `dp[i]` represents solutions of `string[i:]`
- Whenever meets a new palindrome `s[i:j)`, then `dp[i]` can be calculated by prepending every solutions in `dp[j]` with this new palindrome prefix.

```python
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        dp = [[] for _ in range(len(s) + 1)]
        dp[-1] = [[]]
        for i in range(len(s) - 1, -1, -1):
            for j in range(i + 1, len(s) + 1):
                if s[i:j] == s[i:j][::-1]:
                    for each in dp[j]:
                        dp[i].append([s[i:j]] + each)
        return dp[0]
```