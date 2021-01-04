---
title: Unique Binary Search Trees
date: 2021-01-04
---
#### Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

```
Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

#### Solutions


1. ##### dynamic programming

- `g[n] = g[j - 1] * g[n - j] for j = 1 to n`

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> g(n + 1);
        g[0] = g[1] = 1;
        for (int i = 2; i <= n; i++)
            for (int lsize = 0; lsize < i; lsize++)
                g[i] += g[lsize] * g[i - lsize - 1];
        
        return g[n];
    }
};
```

2. ##### catlan number

```cpp
int numTrees(int n){
    long c = 1;
    for (int i = 0; i < n; i++)
        c = ((4 * i + 2) * c / (i + 2));
    return c;
}
```