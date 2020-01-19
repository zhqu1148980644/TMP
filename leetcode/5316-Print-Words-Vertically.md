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

```c++
class Solution {
public:
    vector<string> printVertically(string s) {
        vector<pair<string::iterator, string::iterator>> ranges;
        s.push_back(' ');
        int maxlen = 0;
        auto begin = s.begin();
        for (int i = 0, j = 0; j < s.size(); j++) {
            if (s[j] == ' ') {
                maxlen = max(maxlen, j - i);
                ranges.push_back(make_pair(begin + i, begin + j));
                i = j + 1;
            }
        }

        vector<string> res;
        for (int i = 0; i < maxlen; i++) {
            res.push_back("");
            string & cur = res.back();
            for (auto & range : ranges) {
                if (range.first != range.second)
                    cur.push_back(*(range.first++));
                else
                    cur.push_back(' ');
            }
            while (cur.back() == ' ')
                cur.pop_back();
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