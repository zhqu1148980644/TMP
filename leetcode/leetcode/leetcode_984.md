---
title: String Without AAA or BBB
date: 2021-01-04
---
Given two integers A and B, return any string S such that:

S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
The substring 'aaa' does not occur in S;
The substring 'bbb' does not occur in S.
 

Example 1:

Input: A = 1, B = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.
Example 2:

Input: A = 4, B = 1
Output: "aabaa"
 

Note:

0 <= A <= 100
0 <= B <= 100
It is guaranteed such an S exists for the given A and B.

#### Solutions

1. ##### greedy

- prefer appending two equal chars. ie: `aa/bb`

```cpp
class Solution {
public:
    string strWithout3a3b(int A, int B) {
        string aa = "aa", bb = "bb";
        char a = 'a', b = 'b';
        if (A < B) {
            swap(aa, bb); swap(a, b); swap(A, B);
        }

        string res;
        int step = 0;
        while (A && B) {
            if (step % 2 == 0) {
                if (A > B) {
                    res += aa;
                    A -= 2;
                }
                else {
                    res += a;
                    A -= 1;
                }
            }
            else {
                if (B > A) {
                    res += bb;
                    B -= 2;
                }
                else {
                    res += b;
                    B -= 1;
                }
            }
            step++;
        }
        if (A) res += string(A, a);
        if (B) res += string(B, b);
        return res;
    }
};
```