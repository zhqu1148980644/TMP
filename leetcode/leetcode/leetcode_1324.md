---
title: Print Words Vertically
date: 2021-01-04
---
#### Given a string s. Return all the words vertically in the same order in which they appear in s.
Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
Each word would be put on only one column and that in one column there will be only one word.

 

```
Example 1:

Input: s = "HOW ARE YOU"
Output: ["HAY","ORO","WEU"]
Explanation: Each word is printed vertically. 
 "HAY"
 "ORO"
 "WEU"

Example 2:

Input: s = "TO BE OR NOT TO BE"
Output: ["TBONTB","OEROOE","   T"]
Explanation: Trailing spaces is not allowed. 
"TBONTB"
"OEROOE"
"   T"

Example 3:

Input: s = "CONTEST IS COMING"
Output: ["CIC","OSO","N M","T I","E N","S G","T"]
```

 

#### Constraints:

-    1 <= s.length <= 200
-    s contains only upper case English letters.
-    It's guaranteed that there is only one space between 2 words.


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<string> printVertically(string s) {
        vector<pair<int, int>> ranges;
        s.push_back(' ');
        int maxlen = 0, st = 0;
        while (st < s.size() - 1) {
            auto find = s.find(' ', st);
            ranges.emplace_back(st, find);
            maxlen = max(maxlen, (int)find - st);
            st = ++find;
        }

        vector<string> res;
        for (int i = 0; i < maxlen; i++) {
            string w;
            for (auto & [st, ed] : ranges)
                w += st == ed ? ' ' : s[st++];
            while (w.size() && w.back() == ' ')
                w.pop_back();
            res.push_back(move(w));
        }

        return res;
    }
};
```

- Python version use `zip_longest`

```python
class Solution:
    def printVertically(self, s: str) -> List[str]:
        from itertools import zip_longest
        return [''.join(chars).rstrip() 
                for chars in zip_longest(*s.split(), fillvalue=" ")]
```