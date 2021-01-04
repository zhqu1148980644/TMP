---
title: Number of Ways to Split a String
date: 2021-01-04
---
Given a binary string s (a string consisting only of '0's and '1's), we can split s into 3 non-empty strings s1, s2, s3 (s1+ s2+ s3 = s).

Return the number of ways s can be split such that the number of characters '1' is the same in s1, s2, and s3.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "10101"
Output: 4
Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"
Example 2:

Input: s = "1001"
Output: 0
Example 3:

Input: s = "0000"
Output: 3
Explanation: There are three ways to split s in 3 parts.
"0|0|00"
"0|00|0"
"00|0|0"
Example 4:

Input: s = "100100010100110"
Output: 12
 

Constraints:

s[i] == '0' or s[i] == '1'
3 <= s.length <= 10^5


#### Solutions


1. ##### straight forward

```cpp
class Solution {
public:
    int numWays(string s) {
        int MOD =  1000000007;
        long long n = s.size();
        long long zero = count(s.begin(), s.end(), '1');
        if (zero == 0)
            return (((n - 1) * (n - 2)) / 2) % MOD;
        else if ((zero / 3) * 3 != zero)
            return 0;
        // find the region can be choosed as the left splitting point
        int i = 0, cnt1 = 0;
        while (true) {
            if (s[i++] == '1' && ++cnt1 == zero / 3) break;
        }
        i--;
        long long len1 = s.find('1', i + 1) - i;
        // find the                              right
        int j = n - 1, cnt2 = 0;
        while (true) {
            if (s[j--] == '1' && ++cnt2 == zero / 3) break;
        }
        j++;
        long long len2 = j - s.rfind('1', j - 1);
        return len1 * len2 % MOD;
    }
};

```