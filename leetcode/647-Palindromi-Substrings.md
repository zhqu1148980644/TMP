#### Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

```
Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

 

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
```

 

#### Note:

-    The input string length won't exceed 1000.

#### Solutions


1. ##### dynamic programming O(n2) S(n)

```c++
class Solution {
public:
    int countSubstrings(string s) {
        int len = s.size();
        vector<int> dp(s.size(), false);
        int res = 0;
        for (int i = len - 1; i >= 0; i--) {
            bool prel = dp[i] = true;
            res++;
            for (int j = i + 1; j < len; j++) {
                bool tmp = dp[j];
                res += (dp[j] = s[i] == s[j] && prel);
                prel = tmp;
            }
        }

        return res;
    }
};
```


2. ##### expansion O(n2) S(1)

```c++
class Solution {
public:
    int countSubstrings(string s) {
        int res = 0;
        int len = s.size();
        for (int i = 0; i < 2 * len - 1; i++) {
            // two ways.   aba    or      abba
            int l = i / 2;
            int r = l + i % 2;
            while (l >= 0 && r < len && s[l] == s[r]) {
                l--; r++;
                res++;
            }
        }
        return res;
    }
};
```


3. ##### Manacher's Algorithm O(n)


```c++

```