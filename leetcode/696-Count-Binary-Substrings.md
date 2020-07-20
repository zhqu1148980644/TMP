Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
Example 2:
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
Note:

s.length will be between 1 and 50,000.
s will only consist of "0" or "1" characters.

#### Solutions

1. ##### dynamic programming

- borrowed from others
- `cur` represents the length of the `current` continous string(all are 0 or 1), `last ` represents the length of the previous continous string(the opposite of 1/0).

```c++
class Solution {
public:
    int countBinarySubstrings(string s) {
        int res = 0, last = 0, cur = 1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1])
                cur++;
            else {
                last = cur; cur = 1;
            }
            if (last >= cur)
                res++;
        }
        return res;
    }
};
```

The above solution is the simplified version of the below solution.
- count length of all continous substrings.
- For each pair of adjacent substrings, there are min(len(a), len(b)) counts will be added to the total count.

```c++
class Solution {
public:
    int countBinarySubstrings(string s) {
        vector<int> lens = {1};
        for (int i = 1; i < s.size(); i++)
            if (s[i] == s[i - 1])
                lens.back()++;
            else
                lens.push_back(1);

        int res = 0;
        for (int i = 0; i < lens.size() - 1; i++)
            res += min(lens[i], lens[i + 1]);

        return res;
    }
};
```