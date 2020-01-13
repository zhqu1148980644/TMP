#### Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

```
Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
```

#### Solutions

1. ##### stack

- Reference: https://leetcode-cn.com/problems/decode-string/solution/decode-string-fu-zhu-zhan-fa-di-gui-fa-by-jyd/

```c++
class Solution {
public:
    string decodeString(string s) {
        stack<pair<string, int>> lasts;
        string cur_str = "";
        int num = 0;
        for (auto & c : s) {
            // number
            if (c < 'A')
                num = num * 10 + (c - '0');
            // characters
            else if (c > ']' || c < '[')
                cur_str.push_back(c);
            else if (c == '[') {
                lasts.push(make_pair(move(cur_str), num));
                num = 0;
                cur_str = "";
            }
            else {
                auto left = lasts.top(); lasts.pop();
                string & last_str = left.first;
                for (int i = 0; i < left.second; i++)
                    last_str += cur_str;
                cur_str = last_str;
                num = 0;
            }
        }
        return cur_str;
    }
};
```


2. ##### recursion

```c++
class Solution {
private:
    int end = 0;
public:
    string decode(string & s, int cur) {
        int num = 0;
        string cur_str = "";
        while (cur < s.size()) {
            if (s[cur] >= '0' && s[cur] <= '9')
                num = num * 10 + (s[cur] - '0');
            else if (s[cur] == '[') {
                string bracket_str = decode(s, cur + 1);
                while (num--)
                    cur_str += bracket_str;
                cur = this->end;
                num = 0;
            }
            else if (s[cur] == ']') {
                this->end = cur;
                break;
            }
            else
                cur_str.push_back(s[cur]);
            cur++;
        }
        return cur_str;
    }

    string decodeString(string s) {
        return decode(s, 0);  
    }
};
```