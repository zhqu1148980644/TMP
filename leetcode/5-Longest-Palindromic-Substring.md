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

```c++
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

2. #### Dynamic programming O(n2) S(n2)

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

3. #### Linear scan and expand from the center O(n2)

```c++
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

4. #### Manacher's Algorithm O(n)

- reference: https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode-solution/
- This method is based on the expading method, instead of restart expading for all positions, when the current position is within the range of former palindrome, we can speed up the expanding process based on the facts that a palinedrom is symmetric.
- Basically, we need to matain a `radius` table which records the longest palindrome's radius centered in the current position.
- To get rid of the difference between odd palindrome and even palindrome, we insert an unseen character between all ajacent characters in the string and also add onto the front and the back, after this process, all palindrome's length are `odd`.
- Time complexity: O(n) how to prove?

```
index       0 1 2 3 4 5 6 7 8 9 10
radius      0 1 0 3 0 5 0      
            # c # b # c # b # c # c
                  m   c  cur    R

when we are checking the current character b with index 7
the mirror index of 7 based on center 5 is 3
since radius(b) = 3, `R - cur` = 3, we can ensure that the radius of 7 is at least `3` too.
after this, we need to check if this radius can be further expanded using the naive expanding approach.

Note that when `R - cur` < `radius(mirror)`, since some parts are outside the palindrom's radius, we can only ensure the radius of the current character is at least `min(radius(mirror), R - cur)`.

```

```c++
class Solution {
public:
    int expand(const string & s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--; r++;
        }
        return (r - l - 2) / 2;
    }
    string longestPalindrome(string s) {
        // preprocessing
        string t = "#";
        for (auto c : s) {
            t += c; t += '#';
        }
        s = t;
        // c is the center of the palindrom with rightmost boundary, r is it's radius
        int c = -1, r = -1, st = 0, ed = 0;
        vector<int> radius(s.size());
        for (int i = 0; i < s.size(); i++) {
            int minr = 0;
            // within the range of former(with rightmost bound) palindrome
            if (i < c + r) {
                int symi = c - (i - c);
                minr = min(c + r - i, radius[symi]);
            }
            // or  int minr = i < c + r ? min(c + r - i, radius[c - (i - c)]) : 0;
            int curr = expand(s, i - minr - 1, i + minr + 1);
            radius[i] = curr;
            // update the right palindrome boundary to self
            if (i + curr > c + r) {
                c = i;
                r = curr;
            }
            if (curr * 2 + 1 > ed - st) {
                st = i - curr; ed = i + curr;
            }
        }

        string res;
        while (st <= ed)
            if (s[st++] != '#') res += s[st - 1];
        
        return res;
    }
};
```