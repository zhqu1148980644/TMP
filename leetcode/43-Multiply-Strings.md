#### Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

```
Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"
```

#### Note:

- The length of both num1 and num2 is < 110.
- Both num1 and num2 contain only digits 0-9.
- Both num1 and num2 do not contain any leading zero, except the number 0 itself.
- You must not use any built-in BigInteger library or convert the inputs to integer directly.

#### Solutions

1. ##### straight forward

- Multipy the first number with each digit of the second number.
- Add these multiplied number.

```c++
class Solution {
public:
    string multiply(string num1, string num2) {
        if ((num1.size() == 1 && num1[0] == '0') 
            || (num2.size() == 1 && num2[0] == '0')) 
            return "0";
        string res, mures;
        for (int i = num2.size() - 1, j = 0; i >= 0; i--, j++) {
            mures = multiplynum(num1, num2[i] - '0');
            for (int k = 0; k < j; k++) mures.push_back('0');
            res = addnum(res, mures);
        }
        return res;
    }

    string multiplynum(string & num1, int num2) {
        vector<char> res;
        int l = num1.size(), carry = 0;
        while (l || carry) {
            if (l) carry += (num1[--l] - '0') * num2;
            res.push_back('0' + carry % 10);
            carry /= 10;
        }
        reverse(res.begin(), res.end());
        return string(res.begin(), res.end());
    }

    string addnum(string & num1, string num2) {
        vector<char> res;
        int l1 = num1.size(), l2 = num2.size(), carry = 0;
        while (l1 || l2 || carry) {
            if (l1) carry += (num1[--l1] - '0');
            if (l2) carry += (num2[--l2] - '0');
            res.push_back('0' + carry % 10);
            carry /= 10;
        }
        reverse(res.begin(), res.end());
        return string(res.begin(), res.end());
    }
};
```

2. ##### math

- borrowed for others
- Instead of calculating level by level and suming up all numbers, we calculate each digit in the result number from the last to the first.
    - The multiplication's digit length will be no longer than the sum length of two mutiplier's digit length.
    - The multiplication of two digits `num1[i]` and `num2[j]` will contribute to digits in position `i + j` and `i + j + 1` of the final result.

![](https://drscdn.500px.org/photo/130178585/m%3D2048/300d71f784f679d5e70fadda8ad7d68f)

```c++
#define num(x) ((x - '0'))
class Solution {
public:
    string multiply(string num1, string num2) {
        string res(num1.size() + num2.size(), '0');
        for (int i = num1.size() - 1; i >= 0; i--) {
            for (int j = num2.size() - 1; j >= 0; j--) {
                int sum = num(res[i + j + 1]) + num(num1[i]) * num(num2[j]);
                res[i + j + 1] = sum % 10 + '0';
                res[i + j] += sum / 10;
            }
        }
        for (int i = 0; i < res.size(); i++) {
            if (res[i] != '0')
                return res.substr(i);
        }
        return "0";
    }
};
```
