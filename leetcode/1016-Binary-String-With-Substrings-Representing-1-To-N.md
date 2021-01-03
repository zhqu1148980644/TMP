Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N, return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.

 

Example 1:

Input: S = "0110", N = 3
Output: true
Example 2:

Input: S = "0110", N = 4
Output: false
 

Note:

1 <= S.length <= 1000
1 <= N <= 10^9

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    bool queryString(string S, int N) {
        while (N > 0) {
            bitset<32> v(N);
            int len = log2(N--) + 1;
            if (S.find(v.to_string().substr(32 - len)) == string::npos)
                return false;
        }
        return true;
    }
};
```