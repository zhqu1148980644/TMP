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

- Did not figured out yet.

1. ##### dynamic programming

- `g[n] = g[j - 1] * g[n - j] for j = 1 to n`

```c++
int numTrees(int n){
    int g[n + 1];
    for (int i = 0; i <= n; i++) g[i] = 0;
    g[0] = g[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++)
            g[i] += g[j - 1] * g[i - j];

    return g[n];
}
```

2. ##### catlan number

```c++
int numTrees(int n){
    long c = 1;
    for (int i = 0; i < n; i++)
        c = ((4 * i + 2) * c / (i + 2));
    return c;
}
```