Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

 

Example 1:

Input: "112358"
Output: true
Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
             1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
Example 2:

Input: "199100199"
Output: true
Explanation: The additive sequence is: 1, 99, 100, 199. 
             1 + 99 = 100, 99 + 100 = 199
 

Constraints:

num consists only of digits '0'-'9'.
1 <= num.length <= 35
Follow up:
How would you handle overflow for very large input integers?


#### Solutions

1. ##### dfs

```c++
class Solution {
public:
    string_view s;
    inline long sint(string_view sv) {
        long res = 0;
        for (auto & c : sv)
            res =  res * 10 + (c - '0');
        return res;
    }
    bool dfs(int st) {
        int d = (s.size() - st) / 3;
        int last1 = st + d, last2 = st + 2 * d; 
        for (int i = st; i <= last1; i++) {
            for (int j = i + 1; j <= last2; j++) {
                auto s1 = s.substr(st, i - st + 1);
                if (s1.size() > 1 && s1[0] == '0') continue;
                auto s2  = s.substr(i + 1, j - i);
                if (!s2.size() || (s2.size() > 1 && s2[0] == '0')) continue;
                auto s3 = to_string(sint(s1) + sint(s2));
                // rfind(s, 0) equals to starts_with
                if (s.substr(j + 1).rfind(s3, 0) != 0)
                    continue;
                else if (j + 1 + s3.size() == s.size())
                    return true;
                if (dfs(i + 1)) return true;
            }
        }
        return false;
    }
    bool isAdditiveNumber(string num) {
        s = string_view(num);
        return dfs(0);
    }
};
```