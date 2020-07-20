#### Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

 

```
Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.

Example 2:

Input: "aba"
Output: False

Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
```

#### Solutions

1. ##### straight forward O(n2)

- Check every possible prefix that may be the repeated substring.

```c++

```

2. ##### math O(n)

- reference: https://leetcode-cn.com/problems/repeated-substring-pattern/solution/guan-yu-gou-zao-ssjin-xing-pan-duan-de-zheng-ming-/
- Suppose `s` equals to `n * x`, `x` is a substring of s, denote `t` is `2 * s` containing  `2n` number of `x`.
- Removing the first and the last characters, then `t` contains `2n - 2` number of `x`.
    - if `s` can be found in double stripped `t`, we have `2n - 2 >= n  ==  n >= 2` and s is constructed from `n > 2` substrings. 
    - else: `n = 1`, `s` is made of itself.

```c++
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string doubles = s + s;

        return doubles.substr(1, doubles.size() - 2).find(s) != -1;
    }
};
```

3. ##### kmp

- reference: https://blog.csdn.net/mistakk/article/details/83180658
- In kmp algorithm's `next` table, the length of the longest prefix-suffix pair are recorded for each position of `s`.
    - Necessary condition: For a certain string denoted as `s` composed of `n` repeated subtring with length `k (k > 1)`. it's trivial to find out that the prefix `s[: (n - 1) k]` is equivalent to suffix `s[k:]`.
    - Sufficient condition: How to prove the existence of the longest prefix-suffix pair with length `(n - 1)k  (k > 1)` is sufficient to make the string made of repeated substrings.
- For example: the string `s`'s longest prefix-suffix pair has length `n - k`

```
        0  k           n
prefix |*************   |
suffix |   *************|
       |****************----------------|  2 * s
```

- In next table, as the prefix equals to the suffix, the `first k` characters in prefix equals to the `first k` characters in suffix.
    - which is: `prefix[:k] == suffix[: k]`, and because `suffix[: k]` is `s[k:2k]`, we have `s[:k] == s[k:2k]`
    - Follow the same perspective, the equation `s[xk:(x+1)k] == s[(x+1)k, xk:(x+2)k]` applies to the whole string as long as `k` is a devisor of `len(s)`.
    - Thus we can prove that `s` is made of `n/k` numbers of `k`.
- The example above also demonstrated how the second solution works.
    - This is a general approach to seach for the repeated pattern in a string. ie: `(s + s).find(s, 1)`.

```c++
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int len = s.size();
        // next[i] = k represents s[:k) == s[i - k, i)
        int next[len + 1] = {-1};
        int i = 0, t = -1;
        while (i < len) {
            if (t == -1 || s[i] == s[t])
                next[++i] = ++t;
            else
                t = next[t];
        }

        return next[len] && !(len % (len - next[len]));
    }
};
```