Given two strings str1 and str2 of the same length, determine whether you can transform str1 into str2 by doing zero or more conversions.

In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.

Return true if and only if you can transform str1 into str2.

 

Example 1:

Input: str1 = "aabcc", str2 = "ccdee"
Output: true
Explanation: Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.
Example 2:

Input: str1 = "leetcode", str2 = "codeleet"
Output: false
Explanation: There is no way to transform str1 to str2.
 

Note:

1 <= str1.length == str2.length <= 10^4
Both str1 and str2 contain only lowercase English letters.

#### Solutions

1. ##### hash map

- build a hash map records conversions from characters in str1 into characters in str2. return true if there are no disagreement for all characters.
- On special case is when strs constains all 26 characters.

```
In such case, since replacements are applied for all `a`, there is no way to replace `a` into `c` along.
abc...za
cbc...za
```

```c++
class Solution {
public:
    bool canConvert(string str1, string str2) {
        if (str1 == str2) return false;
        vector<int> convert(126), count(126);
        int unique = 0;
        for (int i = 0; i < str1.size(); i++) {
            auto c1 = str1[i], c2 = str2[i];
            if (++count[str2[i]] == 1) ++unique;
            if (convert[c1] && convert[c1] != c2)
                return false;
            else
                convert[c1] = c2;
        }

        return unique < 26;
    }
};
```