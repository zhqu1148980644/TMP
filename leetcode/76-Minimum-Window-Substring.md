#### Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

```
Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
```

#### Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.


#### Solutions

- Caution: If the T string is `"AABC"`, the window needs to contain `2 A, 1 B and 1 C`.

1. ##### sliding window with hashmap O(len(s) + len(t))

- Maitain two pointers `left/i` and `right/j` to represent the current window in S.
- Find the first window in S which covers all characters in T by iteratively `extending the right pointer`, and `shrink left pointe`r when the requirements are satisfied util the window doesn't cover all characters again. Record the valid window with the minimum length during this process.
- When the window doesn't cover all characters in T again, return to the second step by extending the right pointer.
    - A hashmap is used to represent the requirements with each character in T and their corresponding occurence frequency.
    - A nother hashmap is used to represent the the characters counts in the current window. 
    - Move right pointer forward when the window is no valid, and then make the window invalid again by shrinking the left pointer.
    - Invariant: the window during the shrinking process is always valid.
- Time comlexity: `j` start at `0` ends with `len(s)`, though for each `j`, `i` may step forward several time, but `i` can only go forward till the end `len(s)`, thus the worst case is `O(2len(s))`;

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> count;
        for (auto  & c : t) count[c]++;
        string res;
        unordered_map<char, int> curcount;
        // formed is to mark How many unique characters in S are satisfied now.
        int i = 0, j = 0, formed = 0, minlen = INT_MAX;
        while (j < s.size()) {
            char c = s[j];
            curcount[c]++;
            // only increase when the frequency equals to the requrement.
            if (count.count(c) && curcount[c] == count[c])
                formed++;
            if (formed == count.size())
                while (i <= j) {
                    char c = s[i++];
                    curcount[c]--;
                    // Stop shrinking when the invariant breaks.
                    if (count.count(c) && curcount[c] < count[c]) {
                        formed--;
                        if (j - i + 2 < minlen) {
                            minlen = j - i + 2;
                            res = s.substr(i - 1, minlen);
                        }
                        break;
                    }
                }
            j++;
        }
        return res;
    }
};
```

or simplified version

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";
        vector<int> need(128), cur(128);
        for (auto c : t) need[c]++;
        
        int i = 0, j = 0, cnt = 0;
        int mini = 0, minlen = INT_MAX;
        while (j < s.size()) {
            int c = s[j++];
            if (++cur[c] <= need[c] && ++cnt == t.size()) {
                while (cnt == t.size()) {
                    int c = s[i++];
                    if (--cur[c] < need[c]) --cnt;
                }
                if (j - i + 1 < minlen) {
                    minlen = j - i + 1;
                    mini = i - 1;
                }
            }
        }
        
        return minlen == INT_MAX ? "" : s.substr(mini, minlen);
    }
};
```

2. ##### optimized version

- One hash map is sufficient to represent both the requirements in T and the character counts in the current window. i.e: deduce their counts when they appeared and increase their counts when they dispeared when shrinking the left pinters.


```c++
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128);
        for (auto c : t) count[c]++;

        int i = 0, j = 0, formed = 0, min_len = s.size() + 1, st = s.size();
        while (j < s.size()) {
            if (--count[s[j]] >= 0)
                formed++;
            while (formed == t.size()) {
                if (j - i + 1 < min_len) {
                    min_len = j - i + 1;
                    st = i;
                }
                if (++count[s[i++]] > 0) formed--;
            }
            j++;
        }

        return st == s.size() ? "" : s.substr(st, min_len);
    }
};
```

OR

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128);
        for (auto & c : t) count[c]++;
        int i = 0, j = 0, formed = 0;
        int start = s.size(), minlen = s.size();
        while (j < s.size()) {
            if (--count[s[j]] >= 0) formed++;
            if (formed == t.size()) {
                while (formed == t.size())
                    if (++count[s[i++]] > 0) formed--;
                if (j - i + 2 <= minlen) {
                    minlen = j - i + 2;
                    start = i - 1;
                }
            }
            j++;
        }
        return start == s.size() ? "" : s.substr(start, minlen);
    }
};
```

check `problem 3` for detailed solution for this kind of problem.

3. ##### optimized version

- For case when `O(2n) >> O(n)`.
- We can use a vector to record the the position of characters in S that is appeared in T.
- Then use the same method above to loop through this sequence.

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128);
        for (auto c : t) count[c]++;

        vector<pair<char, int>> strpos;
        for (int i = 0; i < s.size(); i++)
            if (count[s[i]])
                strpos.push_back({s[i], i});
        
        int i = 0, formed = 0, min_len = s.size() + 1, st = s.size();
        
        for (auto & [c, end] : strpos) {
            if (--count[c] >= 0)
                formed++;
            if (formed == t.size()) {
                while (formed == t.size())
                    if (++count[strpos[i++].first] > 0)
                        formed--;
                int len = end - strpos[i - 1].second + 1;
                if (len < min_len) {
                    min_len = len;
                    st = strpos[i - 1].second;
                }
            }
        }

        return st == s.size() ? "" : s.substr(st, min_len);
    }
};
```