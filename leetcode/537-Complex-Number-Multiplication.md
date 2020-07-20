Given two strings representing two complex numbers.

You need to return a string representing their multiplication. Note i2 = -1 according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
Note:

The input strings will not have extra blank.
The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of [-100, 100]. And the output should be also in this form.


#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        auto complex = [](auto & s) {
            return pair<int, int>{
                stoi(s.substr(0, s.find('+'))), 
                stoi(s.substr(s.find('+') + 1))
            };
        };
        // or use sscanf(a.c_str(), "%d+%di", &i1, &i2);
        auto [i1, i2] = complex(a);
        auto [i3, i4] = complex(b);
        return  to_string(i1 * i3 - i2 * i4) + "+"
              + to_string(i1 * i4 + i2 * i3) + "i";
    }
};
```