Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Note:

The input string length won't exceed 1000.

#### Solutions

1. ##### dynamic programming O(n2)

```c++
class Solution {
public:
    int countSubstrings(string s) {
        int res = 0;
        vector<bool> dp(s.size());
        for (int j = 0; j < s.size(); j++) {
            bool pre = true;
            for (int i = j; i >= 0; i--) {
                bool tmp = dp[i];
                res += dp[i] = s[i] == s[j] && (j - i < 2 || pre);
                pre = tmp;
            }
        }

        return res;
    }
};
```

2. ##### expanding O(n2)

```c++
class Solution {
public:
    int countSubstrings(string s) {
        auto count = [&s](int i, int j) {
            int num = 0;
            while (i >= 0 && j < s.size() && s[i] == s[j]) {
                num++; i--; j++;
            }
            return num;
        };
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            res += count(i, i + 1);
            res += count(i, i);
        }

        return res;
    }
};
```

3. ##### manarchar algorithm O(n)

```c++

```