---
title: Circular Permutation in Binary Representation
date: 2021-01-04
---
Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that :

p[0] = start
p[i] and p[i+1] differ by only one bit in their binary representation.
p[0] and p[2^n -1] must also differ by only one bit in their binary representation.
 

Example 1:

Input: n = 2, start = 3
Output: [3,2,0,1]
Explanation: The binary representation of the permutation is (11,10,00,01). 
All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
Example 2:

Input: n = 3, start = 2
Output: [2,6,7,5,4,0,1,3]
Explanation: The binary representation of the permutation is (010,110,111,101,100,000,001,011).
 

Constraints:

1 <= n <= 16
0 <= start < 2 ^ n

#### Solutions

1. ##### gray code

- based on `problem 89 Gray code`
- Two attributes:
    - all ajacent intergers differ by only 1 bits in gray code sequence.
    - The `first` and the `last` interger in a gray code sequence with n digits also differ by only one bit. ie: the end and the begin are looped.
- example: n = 3, start = 2

```c
gray code with 3 bits
(000,001,011,010,110,111,101,100).
0             2   3           7

has diff(i, i + 1) = 1 and diff(0, 7) = 1


we can reverse 3 - 7  and 0 - 2
```

```cpp
class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        vector<int> res = {0};
        int head = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = res.size() - 1; j >= 0; j--)
                res.push_back(res[j] + head);
            head <<= 1;
        }

        int k = 0;
        for (k = 0; k < res.size(); k++)
            if (res[k] == start) break;
        
        reverse(res.begin(), res.begin() + k + 1);
        reverse(res.begin() + k + 1, res.end());
        return res;
    }
};
```