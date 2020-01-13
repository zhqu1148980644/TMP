#### Given a string, determine if a permutation of the string could form a palindrome.

```
Example 1:

Input: "code"
Output: false

Example 2:

Input: "aab"
Output: true

Example 3:

Input: "carerac"
Output: true
```

#### Solutions

1. ##### hasmap

- The number of each character should be even to make the string a palindrome except for the center character.

```c++
class Solution {
public:
    bool canPermutePalindrome(string s) {
        vector<int> m(126, 0);
        int count = 0;
        for (auto & c : s)
            if (m[c] == 0) {
                m[c]++; count++;
            }
            else {
                m[c]--; count--;
            }

        return (s.size() % 2) ? (count == 1) : (count == 0);
    }
};
```