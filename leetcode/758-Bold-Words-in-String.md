Given a set of keywords words and a string S, make all appearances of all keywords in S bold. Any letters between <b> and </b> tags become bold.

The returned string should use the least number of tags possible, and of course the tags should form a valid combination.

For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d". Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.

#### Note:

-    words has length in range [0, 50].
-    words[i] has length in range [1, 10].
-    S has length in range [0, 500].
-    All characters in words[i] and S are lowercase letters.


#### Solutions

1. ##### hash map O(numwords * n2)

```c++
class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        unordered_set<string> seen(words.begin(), words.end());
        int n = S.size();
        vector<bool> isbold(n, false);
        auto begin = isbold.begin();
        for (auto & word : seen) {
            int st = 0, wsize = word.size();
            while ((st = S.find(word, st)) != string::npos) {
                std::fill(begin + st, begin + st + wsize, true);
                st++;
            }
        }

    
        string res;
        int i = 0;
        while (i < n) {
            if (!isbold[i])
                res += S[i++];
            else {
                res += "<b>";
                while (isbold[i]) res += S[i++];
                res += "</b>";
            }
        }

        return res;
    }
};
```