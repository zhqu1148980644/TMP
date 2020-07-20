Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  Return a list of all possible strings we could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length between 1 and 12.
S will consist only of letters or digits.

#### Solutions

- Full permutaions

1. ##### backtrack

```c++
class Solution {
public:
    vector<string> res;
    void dfs(string & s, int st) {
        while (st < s.size() && !isalpha(s[st]))
            st++;
        if (st >= s.size())
            res.push_back(s);
        else {
            // or if (s[st] < 'a') s[st] ^= (1 << 5);
            s[st] = tolower(s[st]);
            dfs(s, st + 1);
            // or if (s[t] > 'Z') s[st] ^= (1 << 5);
            s[st] = toupper(s[st]);
            dfs(s, st + 1);
        }
    }
    vector<string> letterCasePermutation(string S) {
        dfs(S, 0);
        return res;
    }
};
```

or

```c++
class Solution {
public:
    vector<string> res;
    void dfs(string & s, int st) {
        if (st >= s.size())
            res.push_back(s);
        else {
            dfs(s, st + 1);
            // as long the each step has no duplicates, all path are unique even though S has been changed
            if (isalpha(s[st])) {
                s[st] ^= 32;
                dfs(s, st + 1);
            }
        }
    }
    vector<string> letterCasePermutation(string S) {
        dfs(S, 0);
        return res;
    }
};
```