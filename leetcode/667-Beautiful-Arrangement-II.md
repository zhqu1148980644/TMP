Given two integers n and k, you need to construct a list which contains n different positive integers ranging from 1 to n and obeys the following requirement:
Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.

If there are multiple answers, print any of them.

Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.
Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.
Note:
The n and k are in the range 1 <= k < n <= 104.


##### Solutions

1. ##### straight forward

- A simple way to achieve this is to produce distinct integers from `1 to k`. For `n = 10, k = 4` as example, the sequence is:
    - sequence:     `1  5  2  4  3  6  7  8  9  10`
    - abs(diff):     `4  3   2  1  3  1  1  1  1`


```c++
class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> res(n, 1);
        int sign = 1, step = k;
        // 1  5  2  4  3
        for (int i = 1; i <= k; i++) {
            res[i] = res[i - 1] + step * sign;
            sign *= -1; step--;
        }

        // 1  5  2  4  3  6  7  8  9 10 11 12 13 14
        for (int i = k + 1; i < n; i++)
            res[i] = i + 1;
        // or iota(res.begin() + k + 1, res.end(), k + 2);
        
        return res;
    }
};
```