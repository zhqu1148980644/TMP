#### Given a list of non negative integers, arrange them such that they form the largest number.

```
Example 1:

Input: [10,2]
Output: "210"

Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
```

#### Note: The result may be very large, so you need to return a string instead of an integer.


#### Solutions

1. ##### compare

- Proof: https://leetcode.com/problems/largest-number/discuss/291988/A-Proof-of-the-Concatenation-Comparator's-Transtivity

```c++
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> snum;
        for (auto & n : nums)
            snum.push_back(to_string(n));
        sort(snum.begin(), snum.end(), [](string & s1, string & s2) {
            return s1 + s2 > s2 + s1;
        });

        string res;
        for (auto & n : snum)
            res += n;
        
        return res;
    }
};
```