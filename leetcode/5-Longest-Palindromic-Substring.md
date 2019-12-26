### Longest Palindromic Substring

### Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

### Example 1:

```
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
```

### Example 2:

```
Input: "cbbd"
Output: "bb"
```

### Solutions

1. #### Brute force O(n3)

```c
int ispalin(char * st, char * ed) {
    while (st < ed) if (*st++ != *--ed) return 0;
    return true;
}

char * longestPalindrome(char * s) {
    if (s[0] == '\0' || s[1] == '\0') return s;
    int max_len = 0;
    char * max_st;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len + 1; j++) {
            if (j - i < max_len) continue;
            if (ispalin(s + i, s + j)) {
                max_len = j - i;
                max_st = s + i;
            }
        }
    }
    max_st[max_len] = '\0';
    return max_st;
}
```

2. #### Linear scan and expand from the center O(n2)

```c
#define max(x, y) ((x > y) ? (x) : (y))
int expand(char * s, int left, int right) {
    while(left >= 0 && s[right] && s[left] == s[right]) {
        left--; right++;
    }
    return right - left - 1;
}

char * longestPalindrome(char * s) {
    if (!s || *s == '\0') return "";
    int st = 0, ed = 0;
    int i = 0;
    while (s[i]) {
        int len1 = expand(s, i, i);
        int len2 = expand(s, i, i + 1);
        int len = max(len1, len2);
        if (len > ed - st) {
            st = i - (len - 1) / 2;
            ed = i + len / 2 + 1;
        }
        ++i;
    }
    s[ed] = '\0';
    return s + st;
}
```

3. #### Dynamic programming O(n2) S(n2)

- Build a dp table `dp[n, n]`, `dp[i, j]` represents if `s[i:j]` is a palindromic substring.
- The relation: `dp[i, j] = true` only if `dp[i + 1, j - 1] == true` and `s[i] == s[j]`.


Row by row, from bottom to top.

```c++
char * longestPalindrome(char * s) {
    if (!s || !*s) return "";
    int len = strlen(s);
    int dp[len][len];
    int st =  0, ed = 0;
    for (int i = len - 1; i >= 0; i--) {
        for (int j = i; j < len; j++) {
            dp[i][j] = (s[i] == s[j]  && ( j - i < 2 || dp[i + 1][j - 1]));
            if (dp[i][j] && j - i > ed - st) {
                st = i; ed = j;
            }
        }
    }
    s[ed + 1] = '\0';
    return s + st;
}
```

Column by column, from left to right.

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        if (!s.size()) return "";
        bool dp[s.size()][s.size()];
        int st = 0, ed = 0;

        for (int j = 0; j < s.size(); j++) {
            for (int i = 0; i <= j; i++) {
                dp[i][j] = s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1]);
                if (dp[i][j] && j - i > ed - st) {
                    st = i;
                    ed = j;
                }
            }
        }
        return s.substr(st, ed - st + 1);
    }
};
```

4. #### Manacher's Algorithm O(n)
