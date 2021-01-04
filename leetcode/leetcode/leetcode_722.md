---
title: Remove Comments
date: 2021-01-04
---
Given a C++ program, remove comments from it. The program source is an array where source[i] is the i-th line of the source code. This represents the result of splitting the original source code string by the newline character \n.

In C++, there are two types of comments, line comments, and block comments.

The string // denotes a line comment, which represents that it and rest of the characters to the right of it in the same line should be ignored.

The string /* denotes a block comment, which represents that all characters until the next (non-overlapping) occurrence of */ should be ignored. (Here, occurrences happen in reading order: line by line from left to right.) To be clear, the string /*/ does not yet end the block comment, as the ending would be overlapping the beginning.

The first effective comment takes precedence over others: if the string // occurs in a block comment, it is ignored. Similarly, if the string /* occurs in a line or block comment, it is also ignored.

If a certain line of code is empty after removing comments, you must not output that line: each string in the answer list will be non-empty.

There will be no control characters, single quote, or double quote characters. For example, source = "string s = "/* Not a comment. */";" will not be a test case. (Also, nothing else such as defines or macros will interfere with the comments.)

It is guaranteed that every open block comment will eventually be closed, so /* outside of a line or block comment always starts a new comment.

Finally, implicit newline characters can be deleted by block comments. Please see the examples below for details.

After removing the comments from the source code, return the source code in the same format.

Example 1:
Input: 
source = ["/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"]

The line by line code is visualized as below:
/*Test program */
int main()
{ 
  // variable declaration 
int a, b, c;
/* This is a test
   multiline  
   comment for 
   testing */
a = b + c;
}

Output: ["int main()","{ ","  ","int a, b, c;","a = b + c;","}"]

The line by line code is visualized as below:
int main()
{ 
  
int a, b, c;
a = b + c;
}

Explanation: 
The string /* denotes a block comment, including line 1 and lines 6-9. The string // denotes line 4 as comments.
Example 2:
Input: 
source = ["a/*comment", "line", "more_comment*/b"]
Output: ["ab"]
Explanation: The original source string is "a/*comment\nline\nmore_comment*/b", where we have bolded the newline characters.  After deletion, the implicit newline characters are deleted, leaving the string "ab", which when delimited by newline characters becomes ["ab"].
Note:

The length of source is in the range [1, 100].
The length of source[i] is in the range [0, 80].
Every open block comment is eventually closed.
There are no single-quote, double-quote, or control characters in the source code.

##### Solutions

1. ##### straight forward

- Be careful about the cases like: `[/*dasdasdasdas, asdasda*/asdasd]` or `[/*dasdasdasd, asdasdasd*/]`.

```cpp
class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        bool comment = false;
        const string sts = "/*", eds = "*/", ns = "//";
        vector<string> res;
        string newline;
        for (auto & line : source) {
            string::size_type pos = 0;
            if (comment) {
                auto ed = line.find(eds);
                if (ed == string::npos)
                    continue;
                pos = ed + 2; comment = false;
            }
            auto st = line.find(sts, pos), n = line.find(ns, pos);
            while (st < n) {
                newline += line.substr(pos, st - pos);
                auto ed = line.find(eds, st + 2);
                if (ed == string::npos) {
                    comment = true;
                    break;
                }
                pos = ed + 2;
                st = line.find(sts, pos);
                n = line.find(ns, pos);
            }
            if (!comment)
                newline += line.substr(pos, n == string::npos ? line.size() : n - pos);
            if (!comment && newline.size()) {
                // push_back(move(line)) would set newline's data pinter to nullptr.
                // or res.push_back(newline); newline = "";
                res.push_back(move(newline));
            }
        }
        return res;
    }
};
```


2. ##### state machine

- borrowed from https://leetcode-cn.com/problems/remove-comments/solution/c-0ms-zhuang-tai-ji-by-charon____/

```cpp
class Solution {
public:
    inline string nextc(string & s, int i) {
        if (i + 1 < s.size()) {
            string sub = s.substr(i, 2);
            if (sub == "*/" || sub == "/*" || sub == "//")
                return sub;
        }
        return string(1, s[i]);
    }
    vector<string> removeComments(vector<string>& source) {
        enum State {LINE, END, BLOCK};
        vector<string> res;
        string cur;
        State state = LINE;
        for (auto & line : source) {
            int i = 0;
            while (i < line.size()) {
                string curc = nextc(line, i++);
                if (state == LINE) {
                    if (curc == "//")
                        break;
                    else if (curc == "/*") {
                        state = BLOCK; i++;
                    }
                    else
                        cur.push_back(curc[0]);
                }
                else if (state == BLOCK) {
                    if (curc == "*/") {
                        state = LINE; i++;
                    }
                }
                else break;
            }
            if (state != BLOCK && cur.size()) {
                res.push_back(move(cur)); state = LINE;
            }
        }
        return res;
    }
};

```