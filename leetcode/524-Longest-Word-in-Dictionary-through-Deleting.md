Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output: 
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]

Output: 
"a"
Note:
All the strings in the input will only contain lower-case letters.
The size of the dictionary won't exceed 1,000.
The length of all the strings in the input won't exceed 1,000.

#### Solutions

1. ##### two pointers O(nlen(s)) n is the size of d

- Use sort to start the scanning from the longest string may be more efficient in some cases.

```c++
class Solution {
public:
    bool issub(string & s1, string & s2) {
        int i = 0;
        for (int j = 0; i < s1.size() && j < s2.size(); j++)
            if (s1[i] == s2[j])
                i++;
        return i == s1.size();
    }
    string findLongestWord(string s, vector<string>& d) {
        string res;
        for (auto & w : d) {
            if (w.size() < res.size() 
            || (w.size() == res.size() && w >= res))
                continue;
            if (issub(w, s))
                res = w;
        }
        return res;
    }
};
```

or python version borrowed from stephan

```python
class Solution:
    def findLongestWord(self, s: str, d: List[str]) -> str:
        def isubs(x):
            gen = iter(s)
            return all(c in gen for c in x)
        return min(list(filter(isubs, d)) + [''], key = lambda x : (-len(x), x))
```

2. ##### binary search O(n*len(x)*log(len(s))) lenx is the mean size of strings in d

```c++
class Solution {
public:

    string findLongestWord(string s, vector<string>& d) {
        unordered_map<char, vector<int>> m;
        for (int i = 0; i < s.size(); i++)
            m[s[i]].push_back(i);

        string res = "";
        for (auto & w : d) {
            if (w.size() < res.size() 
            || (w.size() == res.size() && w >= res))
                continue;
            int st = 0;
            bool isub = true;
            for (auto c : w) {
                auto & v = m[c];
                auto find = lower_bound(v.begin(), v.end(), st);
                if (find == v.end()) {
                    isub = false; break;
                }
                st = *find + 1;
            }
            if (isub)
                res = w;
        }
        return res;
    }
};
```