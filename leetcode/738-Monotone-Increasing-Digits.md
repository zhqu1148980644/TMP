Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.

(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

Example 1:
Input: N = 10
Output: 9
Example 2:
Input: N = 1234
Output: 1234
Example 3:
Input: N = 332
Output: 299
Note: N is an integer in the range [0, 10^9].

#### Solutions

1. ##### straight forward

- Find the last reversing point(num pair that a > b), and deduce the greater number by 1 and setting all numbers followed to 9. Recursively repeating this process until all numbers are non-decreasing.

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        bool inc = true;
        int i = (int)num.size() - 2;
        while (i >= 0) {
            if (num[i] > num[i + 1]) {
                inc = false;
                break;
            }
            i--;
        }
        if (inc) return N;
        string res = num.substr(0, i);
        if (num[i] - 1)
            res.push_back(num[i] - 1);
        res += string(num.size() - i - 1, '9');
        return monotoneIncreasingDigits(stoi(res));
    }
};
```


or iterative version

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int i = 0;
        while (i < num.size() - 1 && num[i] <= num[i + 1]) i++;
        if (i == num.size() - 1) return N;
        while (i >= 0 && num[i] > num[i + 1]) num[i--]--;
        i++;
        while (++i < num.size()) num[i] = '9';
        return stoi(num);
    }
};
```