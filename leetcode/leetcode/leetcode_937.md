---
title: Reorder Data in Log Files
date: 2021-01-04
---
You have an array of logs.  Each log is a space delimited string of words.

For each log, the first word in each log is an alphanumeric identifier.  Then, either:

Each word after the identifier will consist only of lowercase letters, or;
Each word after the identifier will consist only of digits.
We will call these two varieties of logs letter-logs and digit-logs.  It is guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.  The letter-logs are ordered lexicographically ignoring identifier, with the identifier used in case of ties.  The digit-logs should be put in their original order.

Return the final order of the logs.

 

Example 1:

Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
 

Constraints:

0 <= logs.length <= 100
3 <= logs[i].length <= 100
logs[i] is guaranteed to have an identifier, and a word after the identifier.

#### Solutions

1. ##### stable sort

- Remember to stable_sort, the default sort in stl uses unstable quick sort.

```cpp
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        stable_sort(logs.begin(), logs.end(), [&](auto & s1, auto & s2) {
            if (isdigit(s1.back()) != isdigit(s2.back()))
                return isalpha(s1.back()) != 0;
            if (isdigit(s1.back()))
                return false;
            else {
                int i1 = s1.find(' ') + 1;
                int i2 = s2.find(' ') + 1;
                auto cmp = s1.compare(i1, -1, s2, i2, -1);
                return cmp == 0 ? s1.compare(0, i1, s2, 0, i2) < 0 : cmp < 0;
            }
        });

        return logs;
    }
};
```