#### You are given a string representing an attendance record for a student. The record only contains the following three characters:

-    'A' : Absent.
-    'L' : Late.
-    'P' : Present.

A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his attendance record.

```
Example 1:

Input: "PPALLP"
Output: True

Example 2:

Input: "PPALLL"
Output: False
```




#### Solutions

1. ##### Straight forward


```c++
class Solution {
public:
    bool checkRecord(string s) {
        int late = 0, absent = false;
        for (auto record : s) {
            if (record == 'A') {
                if (absent)
                    return false;
                else
                    absent = true;
                late = 0;
            }
            else if (record == 'L') {
                if (++late > 2)
                    return false;
            }
            else
                late = 0;
        }

        return true;
    }
};
```