A password is considered strong if below conditions are all met:

-    It has at least 6 characters and at most 20 characters.
-    It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
-    It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are met).

Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change required to make s a strong password. If s is already strong, return 0.

Insertion, deletion or replace of any one character are all considered as one change.


#### Solutions

1. ##### straight forward

- reference: https://leetcode.com/problems/strong-password-checker/discuss/91008/Simple-Python-solution
- There are three cases:
    - `len(s) < 6`:
        - replacement is useless,
    - `len(s) <= 20`
        - Since deletion is less efficient for eliminating repeating sequences(len >= 3), we prefer the replacement operation.
        - If there are any missing chars, replacement and insertion can be merged. ie: choose the larger one.
    - `len(s) > 20`
        - Since the deletion is compulsory(reduce size to <=20), we can reuse deletion to remove repeating sequences.
            - Basically, we can always remove one repeating sequence with `len / 3` replacement. ie: `aaaaaaa` -> `aabaaba`.
            - For any repeating sequence with `len % 3 == 0`, we can use `1` deletion to represent one replacement. ie:  `aaa aaa`  -> `aa aaa`, this remaining repeat sequence will be removed in the third case.
            - For any repeating sequence with `len % 3 == 1`, we can use `2` deletions to represent one replacement. ie: `aaa aaa a` -> `aa aaa`, this remaining repeat sequence will be removed in the third case.
            - For any repeating sequence other than the aforementioned two cases and remaining repeats of those two cases, we can use `3` deletions to represent one replacement.


```c++
class Solution {
public:
    int strongPasswordChecker(string s) {
        bool mislchar, misdigit, misuchar;
        mislchar = misdigit = misuchar = true;
        for (auto & c : s) {
            if (isdigit(c))
                misdigit = false;
            else if (islower(c))
                mislchar = false;
            else if (isupper(c))
                misuchar = false;
        }
        int missnum = mislchar + misuchar + misdigit;

        int done = 0, dtwo = 0, replace = 0;
        for (int i = 2; i < s.size(); i++) {
            if (s[i] == s[i - 1] && s[i - 1] == s[i - 2]) {
                int len = 3;
                while (i + 1 < s.size() && s[i + 1] == s[i]) {
                    i++; len++;
                }
                if (len % 3 == 0)
                    done++;
                else if (len % 3 == 1)
                    dtwo++;
                replace += len / 3;
            }
        }

        if (s.size() < 6)
            return max(6 - (int)s.size(), missnum);
        else if (s.size() <= 20)
            return max(replace, missnum);
        else {
            int del = s.size() - 20;
            // Each deletion can represent one replacement. xxx
            replace -= min(del, done);
            // Two deletion can represent one replacement.  xxxx
            if (del - done > 0)
                replace -= min((del - done) / 2, dtwo);
            // Three deletion can represent one replacement.xxxxx*
            if (del - done - 2 * dtwo > 0)
                replace -= (del - done - 2 * dtwo) / 3;
            return del + max(replace, missnum);
        }
    }
};
```