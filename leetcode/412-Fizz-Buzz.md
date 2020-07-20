Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        unordered_map<int, string> m {{3, "Fizz"}, {5, "Buzz"}};
        vector<string> res(n);
        int i = 1;
        for (auto & s : res) {
            for (auto & [k, v] : m)
                if (i % k == 0)
                    s += v;
            if (s.empty())
                s += to_string(i);
            i++;
        }
        return res;
    }
};
```