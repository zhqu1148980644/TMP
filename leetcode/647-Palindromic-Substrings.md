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

or

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

3. ##### manarchar algorithm O(n)

```c++
class Solution {
public:
    int radius(const string & s, int i, int j) {
        while (i >= 0 && j < s.size() && s[i] == s[j]) {
            i--; j++;
        }
        
        return (j - i - 1) / 2;
    }
    int countSubstrings(string s) {
        string tmp;
        for (auto c : s) {
            tmp += '#'; tmp += c;
        }
        s = tmp + "#";

        int c = -1, r = -1, res = 0;
        vector<int> rv(s.size());
        for (int i = 0; i < s.size(); i++) {
            int baser = 0;
            // reuse former info
            if (c + r > i)
                baser = min(rv[c - (i - c)], c + r - i);
            int curr = radius(s, i - baser - 1, i + baser + 1);
            
            rv[i] = curr;
            res += (curr + 1) / 2;
            if (i + curr > c + r) {
                r = curr;
                c = i;
            }
        }

        return res;
 }
};
```