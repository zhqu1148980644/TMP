---
title: Reconstruct Original Digits from English
date: 2021-01-04
---
Given a non-empty string containing an out-of-order English representation of digits 0-9, output the digits in ascending order.

Note:
Input contains only lowercase English letters.
Input is guaranteed to be valid and can be transformed to its original digits. That means invalid inputs such as "abc" or "zerone" are not permitted.
Input length is less than 50,000.
Example 1:
Input: "owoztneoer"

Output: "012"
Example 2:
Input: "fviefuro"

Output: "45"

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    string originalDigits(string s) {
        unordered_map<char, int> m;
        for (auto ch : s)
            m[ch]++;
        vector<int> c(10);
        c[0] = m['z'];
        c[2] = m['w'];
        c[8] = m['g'];
        c[3] = m['h'] - c[8];
        c[4] = m['u'];
        c[6] = m['x'];
        c[7] = m['s'] - c[6];
        c[1] = m['o'] - c[2] - c[4] - c[0];
        c[5] = m['v'] - c[7];
        c[9] = m['i'] - c[5] - c[6] - c[8];
        
        string res;
        for (int i = 0; i < 10; i++)
            for (int k = 0; k < c[i]; k++)
                res.push_back('0' + i);
        
        return res;
    }
};
```