Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

 

Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
 

Constraints:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].

#### Solutions

1. ##### sliding window

```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> counter(26);
        for (auto c : s1)
            counter[c - 'a']++;
        
        int i = 0, match = 0;
        for (int j = 0; j < s2.size(); j++) {
            if (--counter[s2[j] - 'a'] < 0)
                // or while(++counter[s2[i++] - 'a'] != 0 && match--)
                while (++counter[s2[i++] - 'a'] != 0) match--;
            else
                match++;
            if (match == s1.size())
                return true;
        }

        return false;
    }
};
```

Since the window is always valid, we can discard the `match` variable.

```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> counter(26);
        for (auto c : s1)
            counter[c - 'a']++;
        
        int i = 0;
        for (int j = 0; j < s2.size(); j++) {
            if (--counter[s2[j] - 'a'] < 0)
                while (++counter[s2[i++] - 'a'] != 0);
            else if (j - i + 1 == s1.size())
                return true;
        }

        return false;
    }
};
```