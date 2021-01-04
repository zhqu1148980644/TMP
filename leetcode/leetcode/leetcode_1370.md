---
title: Increasing Decreasing String
date: 2021-01-04
---
Given a string s. You should re-order the string using the following algorithm:

Pick the smallest character from s and append it to the result.
Pick the smallest character from s which is greater than the last appended character to the result and append it.
Repeat step 2 until you cannot pick more characters.
Pick the largest character from s and append it to the result.
Pick the largest character from s which is smaller than the last appended character to the result and append it.
Repeat step 5 until you cannot pick more characters.
Repeat the steps from 1 to 6 until you pick all characters from s.
In each step, If the smallest or the largest character appears more than once you can choose any occurrence and append it to the result.

Return the result string after sorting s with this algorithm.

 

```
Example 1:

Input: s = "aaaabbbbcccc"
Output: "abccbaabccba"
Explanation: After steps 1, 2 and 3 of the first iteration, result = "abc"
After steps 4, 5 and 6 of the first iteration, result = "abccba"
First iteration is done. Now s = "aabbcc" and we go back to step 1
After steps 1, 2 and 3 of the second iteration, result = "abccbaabc"
After steps 4, 5 and 6 of the second iteration, result = "abccbaabccba"
Example 2:

Input: s = "rat"
Output: "art"
Explanation: The word "rat" becomes "art" after re-ordering it with the mentioned algorithm.
Example 3:

Input: s = "leetcode"
Output: "cdelotee"
Example 4:

Input: s = "ggggggg"
Output: "ggggggg"
Example 5:

Input: s = "spo"
Output: "ops"
```
 

#### Constraints:

- 1 <= s.length <= 500
- s contains only lower-case English letters.


#### Solutions

- In summary, the whole process equals to:
- Picking characters in ascending order. 
    - Pick means the picked character cannot be picked again.
    - All characters are unique, when facing more than two candidates, pick any of them.
- Picking  characters in descending order.
- Repeat step 1 and step 2 until all characters are picked.

1. ##### straight forward

```cpp
class Solution {
public:
    string sortString(string s) {
        int num = s.size(), m[128] = {0};
        for (auto c : s) m[c]++;

        string mins;
        for (int c = 0; c < 128; c++)
            if (m[c] > 0) mins.push_back(c);
        
        string res;
        while (res.size() < num) {
            // pick in ascending order
            for (int i = 0; i < mins.size(); i++)
                if (m[mins[i]]-- > 0) res.push_back(mins[i]);
            // pick in decreasing order
            for (int i = mins.size() - 1; i >= 0; i--)
                if (m[mins[i]]-- > 0) res.push_back(mins[i]);
        }

        return res;
    }
};
```