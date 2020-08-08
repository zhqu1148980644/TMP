Let's define a function f(s) over a non-empty string s, which calculates the frequency of the smallest character in s. For example, if s = "dcce" then f(s) = 2 because the smallest character is "c" and its frequency is 2.

Now, given string arrays queries and words, return an integer array answer, where each answer[i] is the number of words such that f(queries[i]) < f(W), where W is a word in words.

 

Example 1:

Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").
Example 2:

Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]
Explanation: On the first query only f("bbb") < f("aaaa"). On the second query both f("aaa") and f("aaaa") are both > f("cc").
 

Constraints:

1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10
queries[i][j], words[i][j] are English lowercase letters.

#### Solutions

1. ##### binary search

```c++
class Solution {
public:
    int f(string & s) {
        vector<int> count(26);
        for (auto c : s) count[c - 'a']++;
        for (auto cnt : count) if (cnt) return cnt;
        return 0;
    }
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> fv;
        for (auto & w : words)
            fv.push_back(f(w));
        // use bucket sort is more proper since the maximum length of word is at most 10
        sort(fv.begin(), fv.end());
        // simply loop through all f() may be more efficient.
        vector<int> res;
        for (auto & qs : queries) {
            int curf = f(qs);
            auto find = upper_bound(fv.begin(), fv.end(), curf) - fv.begin();
            res.push_back(fv.size() - find);
        }

        return res;
    }
};
```