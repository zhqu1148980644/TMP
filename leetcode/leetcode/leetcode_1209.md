---
title: Remove All Adjacent Duplicates in String II
date: 2021-01-04
---
Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.

It is guaranteed that the answer is unique.

 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 

Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.

#### Solutions

1. ##### recursion

```cpp
class Solution {
public:
    string removeDuplicates(string s, int k) {
        int len = 1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != s[i - 1])
                len = 0;
            if (++len == k)
                return removeDuplicates(s.substr(0, i - k + 1) + s.substr(i + 1), k);
        }
        return s;
    }
};
```

2. ##### stack

- from lee215
- `cnts.top()` is the top of stack used for recording the count of the previous character.

```cpp
class Solution {
public:
    string removeDuplicates(string s, int k) {
        string res(s);
        vector<int> cnts;
        int w = 0;
        for (int r = 0; r < s.size(); r++, w++) {
            res[w] = s[r];
            if (cnts.empty() || s[r] != res[w - 1])
                cnts.push_back(1);
            else {
                if (cnts.back() == k - 1) {
                    w -= k;
                    cnts.pop_back();
                }
                else
                    cnts.back()++;
            }
        }
        return res.substr(0, w);
    }
};
```