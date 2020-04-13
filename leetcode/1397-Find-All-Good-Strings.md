Given the strings s1 and s2 of size n, and the string evil. Return the number of good strings.

A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 10^9 + 7.

 

```
Example 1:

Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
Output: 51 
Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da". 
Example 2:

Input: n = 8, s1 = "leetcode", s2 = "leetgoes", evil = "leet"
Output: 0 
Explanation: All strings greater than or equal to s1 and smaller than or equal to s2 start with the prefix "leet", therefore, there is not any good string.
Example 3:

Input: n = 2, s1 = "gx", s2 = "gz", evil = "x"
Output: 2
```
 

Constraints:

s1.length == n
s2.length == n
s1 <= s2
1 <= n <= 500
1 <= evil.length <= 50
All strings consist of lowercase English letters.

#### Soltuions

1. ##### digits dp

- reference: https://leetcode-cn.com/problems/find-all-good-strings/solution/shu-wei-dp-kmp-by-qodjf/
- `solve(s)` represents the number of good strings in the range of `[0-s]`, thus the answer equals to `solve(s2) - solve(s1 - 1)`
- `dp[pos][match_len][is_equal]` represents the number of strings with prefix lower than `s[:pos)` or equal to `s[:pos)` with `pattern[:match_len) == suffix of these prefixs`.

```c++
class Solution {
public:
    vector<int> next;
    string evil;
    // traditional build_next method in kmp algorithm
    void build_next(const string & s) {
        next = vector<int>(s.size());
        int j = next[0] = -1;
        int i = 0;
        while (i < s.size() - 1) {
            if (j < 0 || s[i] == s[j]) {
                ++i; ++j;
                next[i] = j;
            }
            else
                j = next[j];
        }
    }

    // based on the current character s[i] and the matched(prefix of pattern == suffix of s[:i]) length between pattern and s[:i)
    // we can use next_table to calculate the matched length between pattern and and s[:i]
    int next_state(int state, char c) {
        while (state >= 0 && evil[state] != c)
            state = next[state];
        return state + 1;
    }

    int solve(const string & s) {
        int dp[501][51][2] = {0};
        dp[0][0][1] = 1;
        for (int pos = 0; pos < s.size(); pos++) { // from the first position to the last position. ie: 0 -> s.size() - 1
            // dp[][evil.size()] means containing eval string, any string with this kind of prefix is not a good string
            for (int state = 0; state < evil.size(); state++) {
                // prefix is smaller than s[:pos), prefix + any char are still smaller than s[:pos]
                for (char c = 'a'; c <= 'z'; c++) {
                    int ns = next_state(state, c);
                    dp[pos + 1][ns][0] = (dp[pos + 1][ns][0] + dp[pos][state][0]) % 1000000007;
                }
                // prefix is equal to s[:pos), only prefix + (char < s[pos]) are smaller than s[:pos]
                for (char c = 'a'; c < s[pos]; c++) {
                    int ns = next_state(state, c);
                    dp[pos + 1][ns][0] = dp[pos + 1][ns][0] + dp[pos][state][1] % 1000000007;
                }
                // prefix is equal to s[:pos), prefix + s[pos] is equal to s[:pos]
                int ns = next_state(state, s[pos]);
                dp[pos + 1][ns][1] =  (dp[pos + 1][ns][1] + dp[pos][state][1]) % 1000000007;
            }
        }
        // summing up the number of solutions(must be good strings)
        int res = 0;
        for (int state = 0; state < evil.size(); state++) {
            res = (res + dp[s.size()][state][1]) % 1000000007;
            res = (res + dp[s.size()][state][0]) % 1000000007;
        }
        
        return res;
    }

    int findGoodStrings(int n, string s1, string s2, string evil) {
        this->evil = evil;
        build_next(evil);
        //  find s1 - 1 ie: the largest string smaller than s1 in lexicographical order.
        bool valid = false;
        for (int i = n - 1; i >= 0; i--) {
            if (s1[i] > 'a') {
                s1[i]--;
                valid = true;
                break;
            }
            else
                s1[i] = 'z';
        }
        if (!valid)
            return solve(s2);
        else
            return (solve(s2) - solve(s1) + 1000000007)  % 1000000007;
    }
};
```