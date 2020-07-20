We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to the rightmost position. For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false
Note:

A and B will have length at most 100.

#### Solutions

1. ##### straight forward O(nm)

```c++
class Solution {
public:
    bool rotateString(string A, string B) {
        return A.size() == B.size() && (A + A).find(B) != string::npos;
    }
};
```

2. ##### kmp O(n + m)

```c++
class Solution {
public:
    vector<int> build_next(const string & s) {
        vector<int> next(s.size());
        int t = next[0] = -1, j = 0;
        while (j < s.size() - 1) {
            if (t < 0 || s[t] == s[j]) {
                t++; j++;
                next[j] = s[t] == s[j] ? next[t] : t;
            }
            else t = next[t];
        }
        return next;
    }
    int strstr(const string & s, const string & p) {
        if (!p.size()) return 1;
        auto next = build_next(p);
        // Caution: -1 < p.size() is true, because -1 will be converted to size_t
        int j = 0, i = 0, m = p.size(), n = s.size();
        while (i < m && j < n) {
            if (i < 0 || p[i] == s[j]) {
                i++; j++;
            }
            else i = next[i];
        }
        return i == p.size() ? j - i : -1;
    }
    bool rotateString(string A, string B) {
        return A.size() == B.size() && strstr(A + A, B) != -1;
    }
};
```

3. ##### rabin-karp O(n + m)

```c++
class Solution {
public:
    int search(const string & s, const string & p) {
        if (s.size() < p.size()) return -1;
        if (!p.size()) return 0;
        long MOD = 1e9 + 7, R = 27, ML = 1;
        int k = p.size();
        for (int i = 1; i < k; i++)
            ML = (ML * R) % MOD;
        // build pattern key
        long h1 = 0;
        for (int i = 0; i < k; i++)
            h1 = (h1 * R + (p[i] - 'a')) % MOD;
        // comput keys of all k windows
        long h = 0, len = s.size();
        for (int i = 0; i < k; i++)
            h = (h * R + (s[i] - 'a')) % MOD;
        if (h == h1) return 0;
        for (int i = k; i < len; i++) {
            h = (h - (s[i - k] - 'a') * ML) % MOD;
            h = (h * R + (s[i] - 'a')) % MOD;
            if (h < 0) h += MOD;
            if (h == h1) return i - k + 1;
        }
        return -1;
    }
    bool rotateString(string A, string B) {
        return A.size() == B.size() && search(A + A, B) != -1;
    }
};
```