#### Given a string s formed by digits ('0' - '9') and '#' . We want to map s to English lowercase characters as follows:

-    Characters ('a' to 'i') are represented by ('1' to '9') respectively.
-    Characters ('j' to 'z') are represented by ('10#' to '26#') respectively. 

Return the string formed after mapping.

It's guaranteed that a unique mapping will always exist.

 

```
Example 1:

Input: s = "10#11#12"
Output: "jkab"
Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".

Example 2:

Input: s = "1326#"
Output: "acz"

Example 3:

Input: s = "25#"
Output: "y"

Example 4:

Input: s = "12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#"
Output: "abcdefghijklmnopqrstuvwxyz"
```

 

#### Constraints:

-    1 <= s.length <= 1000
-    s[i] only contains digits letters ('0'-'9') and '#' letter.
-    s will be valid string such that mapping is always possible.

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    string freqAlphabets(string s) {
        string res;
        int i = 0;
        while (i < s.size()) {
            if (i + 2 < s.size() && s[i + 2] == '#') {
                int inc = (s[i] - '1') * 10 + (s[i + 1] - '1');
                res.push_back('j' + inc + 1);
                i += 3;
            }
            else
                res.push_back('a' + (s[i++] - '1'));
        }
        return res;
    }
};
```

or

```c++
class Solution {
public:
    string freqAlphabets(string s) {
        string res;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '#') {
                res += 'a' + stoi(s.substr(i - 2, 2)) - 1;
                i -= 2;
            }
            else
                res += s[i] - '1' + 'a';
        }

        return {res.rbegin(), res.rend()};
    }
};
```