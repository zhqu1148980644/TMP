#### Given a string s, return the maximum number of ocurrences of any substring under the following rules:

The number of unique characters in the substring must be less than or equal to maxLetters.
The substring size must be between minSize and maxSize inclusive.
 

```
Example 1:

Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2
Explanation: Substring "aab" has 2 ocurrences in the original string.
It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
Example 2:

Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
Output: 2
Explanation: Substring "aaa" occur 2 times in the string. It can overlap.
Example 3:

Input: s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
Output: 3
Example 4:

Input: s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
Output: 0
```
 

#### Constraints:

- 1 <= s.length <= 10^5
- 1 <= maxLetters <= 26
- 1 <= minSize <= maxSize <= min(26, s.length)
- s only contains lowercase English letters.

#### Solutions

1. ##### greedy O(n)

- Suppose the length of the target string is larger than minSize, then the occurrence of every substring with length minSize within this string must be `>= `to the occurrence of this string, then the substring would be the answer which is contadictary to our assumption.
- Thus, the maxinum number of occurrence of subtring with length `minSize` must be the answer.
- Scan every substring with length `minSize` and count(use hash map) their occurrence.
- Use a character array to count the number of unique characters within a substring.

```c++
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        string_view S(s);
        unordered_map<string_view, int> count;
        vector<int> uniqc(128);
        int uniq = 0, res = 0;
        for (int i = 0; i < minSize; i++)
            if (++uniqc[S[i]] == 1) uniq++;
        if (uniq <= maxLetters)
            res = ++count[S.substr(0, minSize)];
        
        for (int i = minSize; i < s.size(); i++) {
            if (++uniqc[S[i]] == 1) uniq++;
            if (--uniqc[S[i - minSize]] == 0) uniq--;
            auto wv = S.substr(i - minSize + 1, minSize);
            if (uniq <= maxLetters && ++count[wv] > res)
                res = count[wv];
        }

        return res;
    }
};
```