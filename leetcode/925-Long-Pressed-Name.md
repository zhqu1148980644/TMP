Your friend is typing his name into a keyboard.  Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.

You examine the typed characters of the keyboard.  Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.

 

Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.
Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed output.
Example 3:

Input: name = "leelee", typed = "lleeelee"
Output: true
Example 4:

Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.
 

Constraints:

1 <= name.length <= 1000
1 <= typed.length <= 1000
The characters of name and typed are lowercase letters.

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    auto abbreviate(string & s) {
        s.push_back(' ');
        vector<pair<char, int>> res;
        int i = 0, j = 0;
        while (j < s.size()) {
            if (j && s[j] != s[j - 1]) {
                res.emplace_back(s[i], j - i);
                i = j;
            }
            j++;
        }
        return res;
    }
    bool isLongPressedName(string name, string typed) {
        auto v1 = abbreviate(name);
        auto v2 = abbreviate(typed);
        if (v1.size() != v2.size())
            return false;
        for (int i = 0; i < v1.size(); i++) {
            auto [c1, n1] = v1[i];
            auto [c2, n2] = v2[i];
            if (c1 != c2 || n2 < n1) return false;
        }

        return true;
    }
};
```

2. ##### two pointers

```c++
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int len1 = name.size(), len2 = typed.size();
        int i = 0, j = 0;

        while (i < len1) {
            if (name[i] != typed[j]) return false;
            auto c = name[i];
            int ni = 1, nj = 1;
            while (++i < len1 &&  name[i] == c) ni++;
            while (++j < len2 && typed[j] == c) nj++;
            if (nj < ni) return false;
        }

        return j == len2;
    }
};
```