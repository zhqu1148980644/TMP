---
title: Expressive Words
date: 2021-01-04
---
Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".

For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.

For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has size less than 3.  Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".  If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = S.

Given a list of query words, return the number of words that are stretchy. 

 

Example:
Input: 
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
 

Constraints:

0 <= len(S) <= 100.
0 <= len(words) <= 100.
0 <= len(words[i]) <= 100.
S and all words in words consist only of lowercase letters

#### Solutions

- In summary, For each character in the query word, it can be abbreviated(less number) only if the original size of the corresponding(Order of characters in query word and S should be matched) character in `S` >= 3.

1. ##### straight forward
    
```cpp
class Solution {
public:
    bool stretchy(string & w, const vector<pair<char, int>> & m) {
        int pos = 0, num = 0;
        char prevc = ' '; w.push_back('@');
        for (auto c : w) {
            if (c == prevc)
                num++;
            else {
                if (num) {
                    if (!(pos < m.size() && m[pos].first == prevc && m[pos].second >= num))
                        return false;
                    if (m[pos].second < 3 && num != m[pos].second)
                        return false;
                    pos++;
                }
                num = 1;
            }
            prevc = c;
        }
        return pos == m.size();
    }
    int expressiveWords(string S, vector<string>& words) {
        vector<pair<char, int>> s;
        char prevc = ' '; S.push_back('@');
        int num = 0;
        for (auto c : S) {
            if (c == prevc)
                num++;
            else {
                if (num) s.emplace_back(prevc, num);
                num = 1;
            }
            prevc = c;
        }

        int res = 0;
        for (auto & w : words)
            res += stretchy(w, s);

        return res;
    }
};
```