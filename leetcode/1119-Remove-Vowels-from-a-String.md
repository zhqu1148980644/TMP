
Given a string S, remove the vowels 'a', 'e', 'i', 'o', and 'u' from it, and return the new string.

 

Example 1:

Input: "leetcodeisacommunityforcoders"
Output: "ltcdscmmntyfrcdrs"
Example 2:

Input: "aeiou"
Output: ""
 

Note:

S consists of lowercase English letters only.
1 <= S.length <= 1000

#### Solutions

```c++
class Solution {
public:
    string removeVowels(string S) {
        vector<bool> isvowel(126);
        for (auto c : {'a', 'e', 'i', 'o', 'u'})
            isvowel[c] = true;
        string res;
        for (auto c : S)
            if (!isvowel[c])
                res += c;
        return res;
    }
};
```