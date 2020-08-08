A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s. Return the longest happy prefix of s .

Return an empty string if no such prefix exists.

 

```
Example 1:

Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".

Example 2:

Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.

Example 3:

Input: s = "leetcodeleet"
Output: "leet"

Example 4:

Input: s = "a"
Output: ""
```

 

##### Constraints:

    1 <= s.length <= 10^5
    s contains only lowercase English letters.

#### Solutions


1. ##### straight forward O(n2)

- Dierectly compare prefix and suffix for every possible pairs.

2. ##### kmp algorithm O(n)

- In `next` array, `next[i]` represents the length of the longest prefix-suffix pair in substring `s[:i)`.

```c++
class Solution {
public:
    vector<int> build_next(string & s) {
        vector<int> next(s.size());
        int i = next[0] = -1;
        int j = 0;
        while (j < s.size() - 1) {
            if (i < 0 || s[i] == s[j]) {
                i++; j++;
                next[j] = i;
            }
            else
                i = next[i];
        }
        return next;
    }

    string longestPrefix(string s) {
        if (!s.size())
            return "";
        s.push_back(' ');
        vector<int> next = build_next(s);
        if (next.back() == s.size() - 1)
            return "";
        else
            return s.substr(0, next.back());
    }
};
```


3. ##### rolling hash O(n) on average

- The time complexity may not be `O(n)` due to hash collisions.

```c++
#define num(x) (((x) - 'a'))
class Solution {
public:
    string longestPrefix(string s) {
        long m = pow(2, 32), R = 131;
        int n = s.size();

        vector<bool> issame(s.size());
        long h1 = 0, h2 = 0, ML = 1;
        for (int i = 0; i < n; i++) {
            h1 = (h1 * R + num(s[i])) % m;
            h2 = (num(s[n - i - 1]) * ML + h2) % m;
            ML = (ML * R) % m;
            if (h1 == h2)
                issame[i] = true;
        }
        
        // incase of hash collisions, we need to check if suffix matches prefix correctly.
        for (int i = n - 2; i >= 0; i--)
            if (issame[i])
                return s.substr(0, i + 1);

        return "";
    }
};
```