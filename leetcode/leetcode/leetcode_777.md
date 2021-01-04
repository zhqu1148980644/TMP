---
title: Swap Adjacent in LR String
date: 2021-01-04
---
In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.

Example:

Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
Output: True
Explanation:
We can transform start to end following these steps:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
 

Constraints:

1 <= len(start) == len(end) <= 10000.
Both start and end will only consist of characters in {'L', 'R', 'X'}.

#### Solutions

1. ##### math

- Only conversion from "RX" and "XL" to "XR" and "LX" are permitted, this denotes that `start` and `end` will be the same after excluding all "X".
- As moveing orders of `R` and `L` are unidirectional and length of two strings are the same, for each `R` in `start` with index `i`, it's corresponding 'R' in `end` must be pisitioned `>= i`. The same relation for L(<=).

```cpp
class Solution {
public:
    bool canTransform(string start, string end) {
        // j is used for checking the first rule: two strings exluding X are the same
        // l, r are used for the second rule.
        int len = start.size(), r = 0, l = 0, j = 0;
        for (int i = 0; i < len; i++) {
            if (start[i] == 'X') continue;
            while (end[j] == 'X') j++;
            if (start[i] != end[j++]) return false;
            if (start[i] == 'L') {
                while (l < len && end[l] != 'L') l++;
                if (l++ > i) return false;
            }
            else {
                while (r < len && end[r] != 'R') r++;
                if (r++ < i) return false;
            }
        }
        while (l < len) if (end[l++] == 'L') return false;
        while (r < len) if (end[r++] == 'R') return false;
        return true;
    }
};
```