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


```c++
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

```c++
class Solution {
private:
    string s1;
    string s2;
    string s3;
    set<pair<int, int>> forbid;

    bool dfs(int i, int j, int start) {

        if (start == s3.size()) return true;
        if (forbid.count(make_pair(i, j))) return false;

        bool sucess = false;

        if (i < s1.size() && s1[i] == s3[start])
            sucess = sucess || dfs(i + 1, j, start + 1);

        if (j < s2.size() && s2[j] == s3[start])
            sucess = sucess || dfs(i, j + 1, start + 1);

        if (!sucess) forbid.insert(make_pair(i, j));

        return sucess;
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;

        this->s1 = s1;
        this->s2 = s2;
        this->s3 = s3;
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
            if start == len3: return True
            sucess = False
            if i < len1 and s1[i] == s3[start]:
                sucess = sucess or traverse(i + 1, j, start + 1)
            if j < len2 and s2[j] == s3[start]:
                sucess = sucess or traverse(i, j + 1, start + 1)

            return sucess

        len1, len2, len3 = len(s1), len(s2), len(s3)

        return traverse(0, 0, 0) if len1 + len2 == len3 else False
```

3. ###### bfs with queue.

```c++
typedef pair<int, int> Pos;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        set<Pos> visited;
        queue<Pos> q;
        q.push(Pos(0, 0));

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int start = cur.first + cur.second;
            if (start == s3.size())
                return true;

            if (visited.count(cur))
                continue;
            visited.insert(cur);
            if (cur.first < s1.size() && s1[cur.first] == s3[start])
                q.push(Pos(cur.first + 1, cur.second));

            if (cur.second < s2.size() && s2[cur.second] == s3[start])
                q.push(Pos(cur.first, cur.second + 1));

        }
        return false;
    }
};
```

4. ##### dynamic programming

- This problem can be thought as the worst case when aligning two DNA/Protein sequence with not a single pair of bases aligned.
- So, it's a dynamic programming problem with no diagonal path in the 2d dp table.
- Since the path may be not unique and the problem doesn't require the full path, we can solve it in `O(n)` space.

```c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;
        vector<bool> dp(s2.size() + 1, false);
        dp[0] = true;
        for (int i = 0, j = 0; s2[i] == s3[j] && i <= s2.size(); i++, j++)
            dp[i + 1] = true;

        for (int i = 0; i < s1.size(); i++) {
            dp[0] = dp[0] && s1[i] == s3[i];
            for (int j = 0; j < s2.size(); j++) {
                bool sucess = false;
                // check the above position
                if (dp[j + 1])
                    sucess |= s1[i] == s3[i + j + 1];
                // check the left position
                if (dp[j])
                    sucess |= sucess || s2[j] == s3[i + j + 1];
                dp[j + 1] = sucess;
            }
        }

        return dp[s2.size()];
    }
};
```
