A string is called happy if it does not have any of the strings 'aaa', 'bbb' or 'ccc' as a substring.

Given three integers a, b and c, return any string s, which satisfies following conditions:

s is happy and longest possible.
s contains at most a occurrences of the letter 'a', at most b occurrences of the letter 'b' and at most c occurrences of the letter 'c'.
s will only contain 'a', 'b' and 'c' letters.
If there is no such string s return the empty string "".

 

```
Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.
Example 2:

Input: a = 2, b = 2, c = 1
Output: "aabbc"
Example 3:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It's the only correct answer in this case.
```
 

Constraints:

0 <= a, b, c <= 100
a + b + c > 0

#### Solutions

1. ##### greedy approach

- To fetch the longest string satisfying all constraints, the most ideal string should be looked like this: `aabaabccb` ie: char pairs separated by single char.

```c++
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        vector<pair<int, char>> v = {{a, 'a'}, {b, 'b'}, {c, 'c'}};
        static int limit = 2;
        string res;
        while (true) {
            // add char pairs with the largest amount
            sort(v.begin(), v.end(), greater<>());
            // remove empty characters.
            while (v.size() && v.back().first == 0)
                v.pop_back();
            if (v.empty()) break;
            auto & maxchar = *v.begin();
            // bbca a  or bbcbb aa
            int n = (res.size() && res.back() == maxchar.second)
                    ? 1 : min(limit, maxchar.first);
            while (n--) {
                res.push_back(maxchar.second);
                maxchar.first--;
            }
            // add a single character with the smallest amount
            if (v.size() >= 2) {
                res.push_back(v.back().second);
                v.back().first--;
            }
            else break;
        }

        return res;
    }
};
```