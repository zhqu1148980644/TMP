#### Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

#### Note:

- The length of both num1 and num2 is < 5100.
- Both num1 and num2 contains only digits 0-9.
- Both num1 and num2 does not contain any leading zero.
- You must not use any built-in BigInteger library or convert the inputs to integer directly.


#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    string addStrings(string num1, string num2) {
        vector<char> res;
        int l1 = num1.size(), l2 = num2.size(), carry = 0;
        while (l1 || l2 || carry) {
            if (l1) carry += (num1[--l1] - '0');
            if (l2) carry += (num2[--l2] - '0');
            res.push_back('0' + (carry % 10));
            carry /= 10;
        }
        return {res.rbegin(), res.rend()};
    }
};
```

