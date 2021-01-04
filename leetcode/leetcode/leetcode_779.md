---
title: K th Symbol in Grammar
date: 2021-01-04
---
On the first row, we write a 0. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

Given row N and index K, return the K-th indexed symbol in row N. (The values of K are 1-indexed.) (1 indexed).

Examples:
Input: N = 1, K = 1
Output: 0

Input: N = 2, K = 1
Output: 0

Input: N = 2, K = 2
Output: 1

Input: N = 4, K = 5
Output: 1

Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001
Note:

N will be an integer in the range [1, 30].
K will be an integer in the range [1, 2^(N-1)].

#### Solutions

1. ##### math

- Exp: `01101001`'s next row is `01101001 10010110`, the first part is the the same as the previous row, the second part is the reversed(bit reverse) version.

```cpp
class Solution {
public:
    int kthGrammar(int N, int K) {
        if (N == 1) return 0;
        // 2^(N - 1) is the size of the N'th row, the half size is 2^(N - 2)
        if (K <= 1 << (N - 2))
            return kthGrammar(N - 1, K);
        return kthGrammar(N - 1, K - (1 << (N - 2))) ^ 1;
    }
};
```

- Exp: `0` ->  `01`  -> `01 10` -> `01 10 10 01`, `digit[N, K]` comes from `digit(N - 1, (K + 1) / 2)`, and `digit[N, K] = (!(K % 2) ^ digit[N - 1, (k + 1) / 2])`.
    - the formular is deduced from 1 -> 10 and 0 -> 01

```cpp
class Solution {
public:
    int kthGrammar(int N, int K) {
        if (N == 1) return 0;
        return !(K % 2) ^ kthGrammar(N - 1, (K + 1) / 2);
    }
};
```

- Check the official answer for another solution
