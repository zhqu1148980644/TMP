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


```c++
class Solution {
public:
    bool checkRecord(string s) {
        int counter = 0;
        bool late = false;
        int i = 0;
        while (i < s.size()) {
            if (s[i] == 'A') {
                if (late) return false;
                else late = true;
            } else if (s[i] == 'L') {
                if (i > 0 && s[i - 1] == 'L') {
                    if (++counter == 3)
                        return false;
                }
                else
                    counter = 1;
            }
            i++;
        }
        return true;
    }
};
```

#### Solutions

1. ##### Straight forward

- one pass

```c++
class Solution {
public:
    bool checkRecord(string s) {
        int late = 0;
        bool absent = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'A') {
                if (absent)
                    return false;
                else
                    absent = true;
                late = 0;
            } else if (s[i] == 'L') {
                if (++late > 2)
                    return false;
            } else
                late = 0;
        }
        return true;
    }
};
```