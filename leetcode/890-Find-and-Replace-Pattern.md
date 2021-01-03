You have a list of words and a pattern, and you want to know which words in words matches the pattern.

A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.

(Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.)

Return a list of the words in words that match the given pattern. 

You may return the answer in any order.

 

Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
since a and b map to the same letter.
 

Note:

1 <= words.length <= 50
1 <= pattern.length = words[i].length <= 20

#### Solutions

1. ##### map character to index(position)

- The same as `problem 205`.

```cpp
class Solution {
public:
    bool match(const string & s, const string & p) {
        vector<int> index1(126, -1), index2(126, -1);
        for (int i = 0; i < s.size(); i++) {
            if (index1[s[i]] != index2[p[i]])
                return false;
            index1[s[i]] = index2[p[i]] = i;
        }
        return true;
    }
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for (auto & w : words)
            if (match(w, pattern))
                res.push_back(w);
        return res;
    }
};
```