A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

Example 1:

Input:  "69"
Output: true
Example 2:

Input:  "88"
Output: true
Example 3:

Input:  "962"
Output: false

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    unordered_map<char, char> m = {{'6', '9'}, {'9', '6'}, {'1', '1'}, {'0', '0'}, {'8', '8'}};
    bool isStrobogrammatic(string num) {
        string num1(num.rbegin(), num.rend());
        for (auto & n : num1) {
            if (m.count(n))
                n = m[n];
            else
                n = '*';
        }
        return num1 == num;
    }
};
```

OR

```c++
class Solution {
public:
    unordered_map<char, char> m = {{'6', '9'}, {'9', '6'}, {'1', '1'}, {'0', '0'}, {'8', '8'}};
    bool isStrobogrammatic(string num) {
        int i = 0, len = num.size();
        for (int i = 0; i <= (len - 1) / 2; i++) {
            if (m[num[i]] != num[len - i - 1])
                return false;
        }
        return true;
    }
};
```