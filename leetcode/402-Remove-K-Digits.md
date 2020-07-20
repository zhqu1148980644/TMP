Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.


#### Solutions

1. ##### stack

- For number like `xxx54`, since 5 is larger than 4, replacing(deleting) 5 with 4 could generate a smaller number.
- Do not forget to remove leading zeroes and return 0 if the final string is empty.

```c++
class Solution {
public:
    string removeKdigits(string num, int k) {
        if (num.size() == k) return "0";
        string s(1, num[0]);
        for (int i = 1; i < num.size(); i++) {
            while (s.size() && k > 0 && num[i] < s.back()) {
                s.pop_back(); k--;
            }
            s.push_back(num[i]);
        }

        while (k--)
            s.pop_back();
        auto it = s.begin();
        while (it != s.end() && *it == '0') it++;
        return it != s.end() ? string(it, s.end()) : "0";
    }
};
```