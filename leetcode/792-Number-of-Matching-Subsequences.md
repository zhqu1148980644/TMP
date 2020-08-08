Given string S and a dictionary of words words, find the number of words[i] that is a subsequence of S.

Example :
Input: 
S = "abcde"
words = ["a", "bb", "acd", "ace"]
Output: 3
Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
Note:

All words in words and S will only consists of lowercase letters.
The length of S will be in the range of [1, 50000].
The length of words will be in the range of [1, 5000].
The length of words[i] will be in the range of [1, 50].

#### Solutions

1. ##### straight forward O(len(words)len(S))

- Time limit exceed

```c++
class Solution {
public:
    bool isubseq(string & src, string & tgt) {
        int i = 0, j = 0;
        while (i < src.size() && j < tgt.size()) {
            if (src[i] == tgt[j++])
                i++;
        }
        return i == src.size();
    }
    int numMatchingSubseq(string S, vector<string>& words) {
        int res = 0;
        for (auto & w : words)
            res += isubseq(w, S);
        
        return res;
    }
};
```

- Q? why this code can beat 100%?

```c++
class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        int res = 0, j;
        for (int i = 0; i < words.size(); i ++) {
            int position = -1;
            for (j = 0; j < words[i].size(); j ++) {
                position = S.find_first_of(words[i][j], position + 1);
                if (position == -1) break;
            }
            if (j == words[i].length()) res ++;
        }
        return res;
    }
};

```


2. ##### binary search O(nlog(len(S))) n is sum length of words

```c++
class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        unordered_map<char, vector<int>> m;
        for (int i = 0; i < S.size(); i++)
            m[S[i]].push_back(i);

        auto isubseq = [&](const string & src) {
            int st = 0;
            for (auto c : src) {
                auto find = lower_bound(m[c].begin(), m[c].end(), st);
                if (find == m[c].end()) return false;
                else st = *find + 1;
            }
            return true;
        };

        int res = 0;
        for (auto & w : words)
            res += isubseq(w);
        
        return res;
    }
};
```

3. ##### buckets O(len(S)len(words))

```c++
class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<deque<pair<int, int>>> buckets(126);
        for (int i = 0; i < words.size(); i++)
                buckets[words[i][0]].emplace_back(i, 0);

        int res = 0;
        for (auto c : S) {
            int size = buckets[c].size();
            while (size--) {
                auto [wi, index] = buckets[c].front();
                buckets[c].pop_front();
                if (index + 1 == words[wi].size())
                    res++;
                else
                    buckets[words[wi][index + 1]].emplace_back(wi, index + 1);
            }
            if (res >= words.size()) break;
        }

        return res;
    }
};
```

or neat solution from stephan.

```c++
class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<const char *> buckets[126];
        for (auto & w : words)
            buckets[w[0]].push_back(w.c_str());
        
        for (auto c : S) {
            auto advance = buckets[c];
            buckets[c].clear();
            for (auto ps : advance)
                buckets[*++ps].push_back(ps);
        }

        return buckets[0].size();
    }
};
```