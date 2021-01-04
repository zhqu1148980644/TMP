---
title: Goal Parser Interpretation
date: 2021-01-04
---
You own a Goal Parser that can interpret a string command. The command consists of an alphabet of "G", "()" and/or "(al)" in some order. The Goal Parser will interpret "G" as the string "G", "()" as the string "o", and "(al)" as the string "al". The interpreted strings are then concatenated in the original order.

Given the string command, return the Goal Parser's interpretation of command.

 

Example 1:

Input: command = "G()(al)"
Output: "Goal"
Explanation: The Goal Parser interprets the command as follows:
G -> G
() -> o
(al) -> al
The final concatenated result is "Goal".
Example 2:

Input: command = "G()()()()(al)"
Output: "Gooooal"
Example 3:

Input: command = "(al)G(al)()()G"
Output: "alGalooG"
 

Constraints:

1 <= command.length <= 100
command consists of "G", "()", and/or "(al)" in some order.


#### Solutions

```cpp
class Solution {
public:
    string interpret(string command) {
        string res;
        int st = 0;
        while (st < command.size()) {
            if (command[st] == 'G') {
                res += "G"; st += 1;
            }
            else if (command[st + 1] == ')') {
                res += "o"; st += 2;
            }
            else {
                res += "al"; st += 4;
            }
        }
        return res;
    }
};
```