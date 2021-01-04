---
title: 秋叶收藏集
date: 2021-01-04
---
小扣出去秋游，途中收集了一些红叶和黄叶，他利用这些叶子初步整理了一份秋叶收藏集 leaves， 字符串 leaves 仅包含小写字符 r 和 y， 其中字符 r 表示一片红叶，字符 y 表示一片黄叶。
出于美观整齐的考虑，小扣想要将收藏集中树叶的排列调整成「红、黄、红」三部分。每部分树叶数量可以不相等，但均需大于等于 1。每次调整操作，小扣可以将一片红叶替换成黄叶或者将一片黄叶替换成红叶。请问小扣最少需要多少次调整操作才能将秋叶收藏集调整完毕。

示例 1：

输入：leaves = "rrryyyrryyyrr"

输出：2

解释：调整两次，将中间的两片红叶替换成黄叶，得到 "rrryyyyyyyyrr"

示例 2：

输入：leaves = "ryr"

输出：0

解释：已符合要求，不需要额外操作

提示：

3 <= leaves.length <= 10^5
leaves 中只包含字符 'r' 和字符 'y'


#### Solutions

1. ##### dynamic programming O(n)

- `dp[i][r]` represents the number of replaces to make `leaves[:i]` be like `r*` pattern.
- `dp[i][ry]`                                                             `r*y*` pattern.       
- `dp[i][ryr]`                                                          `r*y*r*` pattern.

```cpp
class Solution {
public:
    int minimumOperations(string leaves) {
        if (!leaves.size()) return 0;
        vector<int> dp(3, 0x3f3f3f3f);
        dp[0] = leaves[0] == 'r' ? 0 : 1;
            
        for (int i = 1; i < leaves.size(); i++) {
            auto c = leaves[i];
            vector<int> dp1(3);
            if (c == 'y') {
                dp1[0] = dp[0] + 1;
                dp1[1] = min(dp[0], dp[1]);
                dp1[2] = min(dp[1], dp[2]) + 1;
            }
            else {
                dp1[0] = dp[0];
                dp1[1] = min(dp[0], dp[1]) + 1;
                dp1[2] = min(dp[1], dp[2]);
            }
            dp = move(dp1);
        }

        return dp[2];
    }
};
```


2. ##### math/prefix sum O(n)

- reference: https://leetcode-cn.com/problems/UlBDOe/solution/simple-java-by-aerysn/
- check reference for details.

```cpp
class Solution {
public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        vector<int> numr(n + 1);
        for (int i = 0; i < n; i++)
            numr[i + 1] = numr[i] + (leaves[i] == 'r');
        
        int base = n - numr[n];
        int minl = 1 - 2 * numr[1];
        int res = INT_MAX;
        for (int j = 2; j < n; j++) {
            res = min(res, minl - (j - 2 * numr[j]));
            minl = min(minl, j - 2 * numr[j]);
        }

        return base + res;
    }
};
```