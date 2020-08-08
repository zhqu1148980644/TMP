Given an array of 4 digits, return the largest 24 hour time that can be made.

The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from 00:00, a time is larger if more time has elapsed since midnight.

Return the answer as a string of length 5.  If no valid time can be made, return an empty string.

 

Example 1:

Input: [1,2,3,4]
Output: "23:41"
Example 2:

Input: [5,5,5,5]
Output: ""
 

Note:

A.length == 4
0 <= A[i] <= 9

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    string largestTimeFromDigits(vector<int>& A) {
        string res = "";
        int resm = -1;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++) {
                    if (i == j || j == k || i == k) continue;
                    int l = 6 - i - j - k;
                    int h = A[i] * 10 + A[j];
                    int m = A[k] * 10 + A[l];
                    if (h > 23 || m > 59) continue;
                    if (!res.size() || h * 60 + m > resm) {
                        res = to_string(A[i]) + to_string(A[j]) 
                      + ":" + to_string(A[k]) + to_string(A[l]);
                        resm = h * 60 + m;
                    }
                }
        return res;
    }
};
```