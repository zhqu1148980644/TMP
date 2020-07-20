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
- Proof the sorting works, ie: `A < B(means AB < BA) and B < C(means BC < CB) then, A < C(AC < CA)`
    - `s1(n1), len(s1) = l1, s2(n2), len(s2) = l2, s3(n3), len(s3) = l3` with `s1s2 < s2s1 and s2s3 < s3s2`
    - use interger represent the concatenation of two strings: `s1s2 = n1*l2 + n2`
    - 1: `n1*l2 + n2 < n2*l1 + n1 and n2*l3 + n3 < n3*l2 + n2`
    - 2: `n1(l2 - 1) < n2(l1 - 1) and n2(l3 - 1) < n3(l2 - 1)`
    - 3: `n1(l2 - 1) * n2(l3 - 1) < n2(l1 - 1) * n3(l2 - 1)`
    - 4: `n1(l3 - 1) < n3(l1 - 1)`
    - 5: `n1 * l3 + n3 < n3 * l1 + n1`
    - 6: `s1s3 < s3s1`
- Proof the concatenation of the sorted array is the maximum string.
    - Suppose strings A and B in the maxinum string `**BA***`(there must be an ajacent reverse pair in an unsorted array) does not satisfy the sorting rule(AB > BA). Since replacing `BA` with `AB` does not change positions of other characters, `**AB***` must be greater than `**BA***`, which is contrary to the supposition.
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
        if (res.size() && res[0] == '0')
            return "0";
        else
            return res;
    }
};
```