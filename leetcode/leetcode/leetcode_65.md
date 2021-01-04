---
title:  Valid Number
date: 2021-01-04
---
Validate if a given string can be interpreted as a decimal number.

```
Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false
```

#### Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. However, here is a list of characters that can be in a valid decimal number:

-    Numbers 0-9
-    Exponent - "e"
-    Positive/negative sign - "+"/"-"
-    Decimal point - "."

Of course, the context of these characters also matters in the input.


#### Solutions

1. ##### Deterministic finite automaton

- reference: https://leetcode.com/problems/valid-number/discuss/23798/Cleanest-C%2B%2B-Solution-using-DFA-(impress-your-interviewer-with-elegant-code!!)

```cpp
class Solution {
public:
    bool isNumber(string s) {
        int states[9][6] = {
        // states[2][4] = 5 represents state 2 can be converted to state 5 when meets type 4 (e). ie: 42.1 -> 42.1e
        //  edges(transition)
        //  ' '  +/- 1/2  .   e   other
            { 0,  1,  2,  3, -1, -1}, // state 0: begin(with blank)
            {-1, -1,  2,  3, -1, -1}, // state 1: "  +"
            { 8, -1,  2,  4,  5, -1}, // state 2: " 42" or "  +3"                 valid end
            {-1, -1,  4, -1, -1, -1}, // state 3: "  +." or " ."       
            { 8, -1,  4, -1,  5, -1}, // state 4: " +1." or " .5" or "+.4"        valid end
            {-1,  6,  7, -1, -1, -1}, // state 5: " +6.4e" or "-.04e" or "  5e"
            {-1, -1,  7, -1, -1, -1}, // state 6: " +6.4e+" or " .1e+" or "  4e+"
            { 8, -1,  7, -1, -1, -1}, // state 7: " +6.4e12" or " .1e+2"          valid end
            { 8, -1, -1, -1, -1, -1}, // state 8: end(with blank)
        };
        int isvalid[9] = {0, 0, 1, 0, 1, 0, 0, 1, 1};
        function<int(int, char &)> type = [](int state, char & c) {
            if (c == ' ')
                return 0;
            if (c == '+' || c == '-')
                return 1;
            if (isdigit(c))
                return 2;
            if (c == '.')
                return 3;
            if (c == 'e')
                return 4;
            return 5;
        };
        int state = 0;
        for (auto & c : s) {
            state = states[state][type(state, c)];
            if (state == -1)
                return false;
        }
        return isvalid[state];
    }
};
```