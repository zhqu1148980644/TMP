Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

Example 1:

Input: 123
Output: "One Hundred Twenty Three"
Example 2:

Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Example 3:

Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Example 4:

Input: 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

#### Solutions

1. ##### recursion

- borrowed from stephan

```c++
class Solution {
public:
    string numberToWords(int num) {
        vector<string> 
            v1 {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", 
            "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"},
            v2 {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        function<string(int n)> solve = [&](int n) {
            string s;
            if (n < 20)
                s = v1[n];
            else if (n < 100)
                s = v2[n / 10] + " " + v1[n % 10];
            else if (n < 1000)
                s = solve(n / 100) + " Hundred " + solve(n % 100);
            else if (n < 1000000)
                s = solve(n / 1000) + " Thousand " + solve(n % 1000);
            else if (n < 1000000000)
                s = solve(n / 1000000) + " Million " + solve(n % 1000000);
            else
                s = solve(n / 1000000000) + " Billion " + solve(n % 1000000000);
            while (s.size() && s.back() == ' ') s.pop_back();
            return s;
        };
        return num ? solve(num) : "Zero";
    }
};
```