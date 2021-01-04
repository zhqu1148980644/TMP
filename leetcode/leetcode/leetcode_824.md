---
title: Goat Latin
date: 2021-01-04
---
A sentence S is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
For example, the word 'apple' becomes 'applema'.
 
If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
 
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
Return the final sentence representing the conversion from S to Goat Latin. 

 

Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each word.
1 <= S.length <= 150.

#### Solutions

1. ##### straight forward


```cpp
class Solution {
public:
    string toGoatLatin(string S) {
        string res; S.push_back(' ');
        int index = 1;
        for (int i = 0, j = 0; j < S.size(); j++) {
            if (S[j] == ' ') {
                if (!j || S[j - 1] != ' ') {
                    int c = tolower(S[i]);
                    bool vowel = c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
                    if (vowel)
                        res += S.substr(i, j - i);
                    else
                        res += S.substr(i + 1, j - i - 1) + S[i];
                    res += "ma" + string(index++, 'a');
                    res.push_back(' ');
                }
                i = j + 1;
            }
        }
        res.pop_back();
        return res;
    }
};
```