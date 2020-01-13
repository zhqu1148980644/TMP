#### Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

#### Note:
Assume the length of given string will not exceed 1,010.

```
Example:

Input:
"abccccdd"

Output:
7
```

#### Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.


#### Solution

1. ##### hash map

- Count how many pairs of characters are the same.

```c++
class Solution {
public:
    int longestPalindrome(string s) {
        int counter[126] = {0};
        for (auto & c : s)
            counter[c]++;
        int num_even = 0;
        for (int i = 0; i < 126; i++)
            if (counter[i])
                num_even += counter[i] / 2;

        num_even = 2 * num_even;

        return num_even < s.size() ? num_even + 1 : num_even;

    }
};
```

Or

```c++
class Solution {
public:
    int longestPalindrome(string s) {
        int counter[126] = {0};
        int num_even = 0;

        for (auto & c : s)
            if (counter[c]) {
                counter[c] = 0;
                num_even += 2;
            }
            else
                counter[c]++;

        return num_even < s.size() ? num_even + 1 : num_even;

    }
};
```