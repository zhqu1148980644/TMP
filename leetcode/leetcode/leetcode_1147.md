---
title: Longest Chunked Palindrome Decomposition
date: 2021-01-04
---
Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:

-    Each a_i is a non-empty string;
-    Their concatenation a_1 + a_2 + ... + a_k is equal to text;
-    For all 1 <= i <= k,  a_i = a_{k+1 - i}.

 

```
Example 1:

Input: text = "ghiabcdefhelloadamhelloabcdefghi"
Output: 7
Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".

Example 2:

Input: text = "merchant"
Output: 1
Explanation: We can split the string on "(merchant)".

Example 3:

Input: text = "antaprezatepzapreanta"
Output: 11
Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".

Example 4:

Input: text = "aaa"
Output: 3
Explanation: We can split the string on "(a)(a)(a)".
```
 

#### Constraints:

-    text consists only of lowercase English characters.
-    1 <= text.length <= 1000


#### Solutions

1. ##### dynamic programming

```cpp

```


2. ##### greedy strategy O(n2)

- reference: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350560/JavaC%2B%2BPython-Easy-Greedy-with-Prove
- Firstly, this problem must has at least one solution, ie: 1, the whole string
- How to get the solution with the largest number of substrings?
    - Suppose there exists two substrings that can be matched from the start and the back, `s1` and `s2` with `len(s1) < len(s2)`.
    - We can prove that choosing the shorter one eagerly can also leads to valid solution, and number of substrings is larger than that of the longer one.
    - Since `s1` and `s3` are matched in two ends, substrings `s3` and `s4` are also matched, thus the solutiong consisting of `s1` and `s3/s4` is a better solution than `s2`.

```
    **********************************
    |-----s1                  |------s1
    |-----------s2       |-----------s2
            |---s3       |----s4
```

```cpp
class Solution {
public:
    int longestDecomposition(string text) {
        int i, res = 0, n = text.size();
        string l, r;
        for (i = 0; i <= n / 2 - 1; i++) {
            l = l + text[i];
            r = text[n - i - 1] + r;
            if (l == r) {
                res += 2;
                l = r = "";
            }
        }
        if (l != "" || n % 2)
            res++;

        return res;
    }
};
```

- recursive version

```cpp
class Solution {
public:
    int longestDecomposition(string text) {
        int n = text.size();
        if (!n) return 0;
        for (int i = 1; i <= n / 2; i++) {
            if (text.substr(0, i) == text.substr(n - i, i))
                return longestDecomposition(text.substr(i, n - 2 * i)) + 2;
        }
        return 1;
    }
};
```

3. rabin-karp

- In the greedy approach, as strings are allocated in comtinous memory, adding characters at the front of string and comparing them is time-consuming.
- The idea is to use rolling hash to compare two growing head/tail substrings that can leads to O(n) time complexity.(without collisions)

```cpp
#define num(x) ((x) - 'a')
class Solution {
public:
    int longestDecomposition(string text) {
        long m = pow(2, 32), R = 26;
        int n = text.size();

        int res = 0;
        long h1 = 0, h2 = 0, ML = 1;
        for (int i = 0; i <= n / 2 - 1; i++) {
            h1 = (h1 * R + num(text[i])) % m;
            h2 = (num(text[n - i - 1]) * ML + h2) % m;
            ML = (ML * R) % m;
            if (h1 == h2) {
                res += 2;
                h1 = h2 = 0;
                ML = 1;
            }
        }

        if (ML != 1 || n % 2)
            res++;
        
        return res;
    }
};
```