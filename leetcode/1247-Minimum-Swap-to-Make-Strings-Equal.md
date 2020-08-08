You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only. Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings, which means: swap s1[i] and s2[j].

Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.

 

Example 1:

Input: s1 = "xx", s2 = "yy"
Output: 1
Explanation: 
Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".
Example 2: 

Input: s1 = "xy", s2 = "yx"
Output: 2
Explanation: 
Swap s1[0] and s2[0], s1 = "yy", s2 = "xx".
Swap s1[0] and s2[1], s1 = "xy", s2 = "xy".
Note that you can't swap s1[0] and s1[1] to make s1 equal to "yx", cause we can only swap chars in different strings.
Example 3:

Input: s1 = "xx", s2 = "xy"
Output: -1
Example 4:

Input: s1 = "xxyyxyxyxx", s2 = "xyyxyxxxyx"
Output: 4
 

Constraints:

1 <= s1.length, s2.length <= 1000
s1, s2 only contain 'x' or 'y'.

#### Solutions

1. ##### math

- reference: https://leetcode-cn.com/problems/minimum-swaps-to-make-strings-equal/comments/427663

```
There are two cases:
1. the number of x/y is even number in `s1`
   ***xx****x**x**yy
   ***yy****y**y**xx
Then for each pair, we can use 1 swap to make them the same
    x    x               y     x
      \             ->   
    y    y               y     x

2. when both x and y has odd numbers, two redundant x and y needs two swap to make them the same
    ****xy****   ->   ****yy****   now y has even numbers, make another swap  ->  *****xy***
    ****yx****        ****xx****                                                  *****xy***
```


```c++
class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int x = 0, y = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) {
                if (s1[i] == 'x') x++;
                else y++;
            }
        }
        if ((x + y) & 1) return -1;
        if (x & 1)
            return (x + y - 2) / 2 + 2;
        else
            return (x + y) / 2;
    }
};
```