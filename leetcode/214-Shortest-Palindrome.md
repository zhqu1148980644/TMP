Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

```
Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"

Example 2:

Input: "abcd"
Output: "dcbabcd"
```
#### Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

```
Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"

Example 2:

Input: "abcd"
Output: "dcbabcd"
```

#### Solutions

- Find the longest palindrome prefix in `s`.
- For `aacecaaa`, the longest palindrome prefix is `aacecaa`, then concatenate the reversed string of the remaining characters `a` with `s` will be `a + aacecaa + a`.
- In another view: denote `rev` as the reversed string of `s`, find the longest palindrome prefix equals to find the longest identical `prefix` in `s` and `suffix` of `rev`.

1. ##### brute force  O(n2) S(n)/S(1)

- Time limit exceed and Memory limit exceed.

```c++
class Solution {
public:
    string shortestPalindrome(string s) {
        string rs(s); reverse(rs.begin(), rs.end());
        int len = s.size();
        for (int end = len; end > 0; end--) {
            // check is palindrome.
            if (s.substr(0, end) == rs.substr(len - end)) {
                return rs.substr(0, len - end) + s;
            }
        }
        return "";
    }
};
```

```python
class Solution:
    def shortestPalindrome(self, s: str) -> str:
        rs = s[::-1]
        for i in range(len(s) + 1):
            if (s.startswith(rs[i:])):
                return rs[:i] + s
```


2. ##### kmp O(n)

- What's the purpose of buiding a `next` table in kmp algorithm ?
    - When we failed to match `p[i]` with the target string `s[j]` after characters before are matched successfully, there is no need to restart the matching with the next characters in `s` and `p[0]`. ie. we can reuse the matching history.
    - For a given pattern string `p`, `next[i]` represents the position of the longest prefix identical to suffix of `p[:i)`.
    - As long as we start matching with `p[0]` compares to characters before `s[j]`, the matching process will be equivalent to mach the prefix of `p[:i)` and the suffix of `p[:)` which is independent of the target string `s`.
    - Filtered all impossible match, we can start matching with `p[next[i]]` compares to `s[j]`.
- Example:

```
    When fails to match x with y
    s: ******---abcde---x******
    p:       ---abcde---y**

    The next match will be:
    s: ******---****---x******
    p:              ---a
```

- Summary: the `next` table rercods the length of the longest identical prefix and suffix ending with each character(right-open).
- Here `next[i]` represents the longest prefix equals to `p[:i)`'s suffix is `p[:next[i])`
- Insert a `#` between s and rev to prevent prefix longer than `len(s)`.

```c++
class Solution {
public:
    string shortestPalindrome(string s) {
        string rs(s); reverse(rs.begin(), rs.end());
        int len = s.size(); if (len <= 1) return s;
        string pattern = s + "#" + rs + "#";

        int t, j = 0;
        vector<int> next(len * 2 + 2, 0);
        next[0] = t = -1;
        while (j != 2 * len + 1) {
            if (t < 0 || pattern[j] == pattern[t]) {
                j++; t++;
                next[j] = t;
            } else
                t = next[t];
        }
        int end = next[len * 2 + 1];
        return rs.substr(0, len - end) + s;
    }

};
```

The kmp template I used is borrowed from https://dsa.cs.tsinghua.edu.cn/~deng/ds/index.htm

```c++
// build next
int * build_next(char * P) {
    int n = strlen(P);
    int * N = new int[n];
    int j = 0; t = N[0] = -1;
    while (j != (n - 1)) {
        if ((t < 0) || (P[j] == P[t])) {
            ++j; ++t;
            N[j] = (P[j] != P[t]) ? t : N[t];
        } else
            t = N[t];
    }
    return N;
}
// search pattern in string
int kmp(char * P, char * T) {
    int m = strlen(T), n = strlen(P);
    int * next = build_next(P);
    int i = 0, j = 0;
    while ((i != m) && (j != n)) {
        if ((j < 0) || (T[i] == P[i])) {
            ++i; ++j;
        } else
            j = next[i];
    }
    return i - j;
}
```

3. #### divide and conquer Worst case O(n2)

- The idea is to shorten the searching space for longest palindrome prefix at each iteration.
- The correctness is hard to understand, however if you assume that the `s[:i)` prefix at the end of each iteration must contain the target palindrome, the code below makes sense.

```c++
class Solution {
public:
    string shortestPalindrome(string s) {
        int i = 0;
        for (int j = s.size() - 1; j >= 0; j--)
            if (s[i] == s[j])
                i++;
        if (i == s.size())
            return s;
        string rtail = s.substr(i);
        reverse(rtail.begin(), rtail.end());
        return rtail + shortestPalindrome(s.substr(0, i)) + s.substr(i);
    }
};
```