---
title: Interleaving String
date: 2021-01-04
---
#### Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

```
Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
```

#### Solutions

1. ##### straight forward with dfs

- Time limit exceed
- Too many duplicate paths.


```cpp
class Solution {
private:

    bool dfs(string & s1, string & s2, string & s3, int start) {
        if (start == s3.size()) return true;
        bool sucess = false;
        if (!s1.empty() && s1.back() == s3[start]) {
            s1.pop_back();
            sucess |= dfs(s1, s2, s3, start + 1);
            s1.push_back(s3[start]);
        }
        if (sucess) return sucess;
        if (!s2.empty() && s2.back() == s3[start]) {
            s2.pop_back();
            sucess |= dfs(s1, s2, s3, start + 1);
            s2.push_back(s3[start]);
        }
        return sucess;
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;

        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        return dfs(s1, s2, s3, 0);
    }
};
```

2. ##### dfs with memoization

- Use a hashmap or table to record inpassible paths which can be represented as unique `i j` pairs.
- reference: https://leetcode-cn.com/problems/interleaving-string/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-2-9/

```cpp
#define node(i, j) ((i) * ncol + (j))
class Solution {
public:
    string s1, s2, s3;
    int ncol;
    // Or use set with pair<int, int> key. hash_map/set requires the key to be hashable within std
    // while the tree map/set only requires to be comparable std::less<T>
    unordered_set<int> forbid;

    bool dfs(int i, int j, int start) {
        if (start == s3.size())
            return true;
        if (forbid.count(node(i, j)))
            return false;
        bool sucess = false;
        if (i < s1.size() && s1[i] == s3[start])
            sucess = sucess || dfs(i + 1, j, start + 1);
        if (j < s2.size() && s2[j] == s3[start])
            sucess = sucess || dfs(i, j + 1, start + 1);
        if (!sucess) forbid.insert(node(i, j));
        return sucess;
    }
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        this->s1 = s1, this->s2 = s2, this->s3 = s3;
        this->ncol = 2 * s3.size();
        return dfs(0, 0, 0);
    }
};
```

- A python version with lru cache.
- Reference: https://leetcode-cn.com/problems/interleaving-string/solution/dong-tai-gui-hua-he-bfs-by-powcai/

```python
class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        from functools import lru_cache

        @lru_cache(None)
        def traverse(i, j, start):
            if start == len3:
                return True
            sucess = False
            if i < len1 and s1[i] == s3[start]:
                sucess = sucess or traverse(i + 1, j, start + 1)
            if j < len2 and s2[j] == s3[start]:
                sucess = sucess or traverse(i, j + 1, start + 1)
            return sucess
        
        len1, len2, len3 = map(len, (s1, s2, s3))
        return len1 + len2 == len3 and traverse(0, 0, 0)
```

3. ###### bfs with queue.

```cpp
#define node(i, j) (((i) * ncol + (j)))
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        int ncol = 2 * s3.size();
        unordered_set<int> visited;
        queue<pair<int, int>> q;
        q.push({0, 0});

        while (!q.empty()) {
            auto [i, j] = q.front(); q.pop();
            int st = i + j;
            if (st == s3.size())
                return true;
            if (visited.count(node(i, j)))
                continue;
            visited.insert(node(i, j));
            if (i < s1.size() && s1[i] == s3[st])
                q.push({i + 1, j});
            if (j < s2.size() && s2[j] == s3[st])
                q.push({i, j + 1});
        }

        return false;
    }
};
```

4. ##### dynamic programming

- This problem can be thought as the worst case when aligning two DNA/Protein sequence with not a single pair of bases aligned.
- So, it's a dynamic programming problem with no diagonal path in the 2d dp table.
- Since the problem doesn't require the full path, we can solve it in `O(n)` space.

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        vector<bool> dp(s2.size() + 1, false);
        dp[0] = true;
        for (int i = 0; s2[i] == s3[i] && i <= s2.size(); i++)
            dp[i + 1] = true;

        for (int i = 0; i < s1.size(); i++) {
            dp[0] = dp[0] && s1[i] == s3[i];
            for (int j = 0; j < s2.size(); j++) {
                bool sucess = false;
                // s1[:i] and s2[:j - 1] matched, len is i + j + 1, thus the next charactor should
                // be compared is s3[i + j + 1]
                sucess = sucess || (dp[j] && s2[j] == s3[i + j + 1]);
                sucess = sucess || (dp[j + 1] && s1[i] == s3[i + j + 1]);
                dp[j + 1] = sucess;
            }
        }

        return dp.back();
    }
};
```
