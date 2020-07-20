Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16 
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4 
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0 
Explanation: No such pair of words.

#### Solutions

1. ##### bit hashmap O(n2)

```c++
class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> ws(words.size());
        for (int i =  0; i < words.size(); i++) {
            auto & w = words[i];
            for (auto c : w)
                ws[i] |= 1 << (c - 'a');
        }
        int res = 0;
        for (int i = 0; i < ws.size(); i++)
            for (int j = i + 1; j < ws.size(); j++)
                if (!(ws[i] & ws[j])) {
                    int len = words[i].size() * words[j].size();
                    if (len > res) res = len;
                }

        return res;
    }
};
```