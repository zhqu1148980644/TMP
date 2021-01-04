---
title: Maximum Number of Balloons
date: 2021-01-04
---
Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of instances that can be formed.

 

Example 1:



Input: text = "nlaebolko"
Output: 1
Example 2:



Input: text = "loonbalxballpoon"
Output: 2
Example 3:

Input: text = "leetcode"
Output: 0
 

Constraints:

1 <= text.length <= 10^4
text consists of lower case English letters only.

#### Solutions

```cpp
class Solution {
public:
    int maxNumberOfBalloons(string text) {
        vector<int> count(126);
        for (auto c : text)
            count[c]++;
        return min({count['b'], count['a'], count['l'] / 2, count['o'] / 2, count['n']});
    }
};
```