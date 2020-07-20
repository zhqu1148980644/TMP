##### Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

#### Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.

```
Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

```


#### Solutions

The problem states that the RPN expression is always valid, tedius checking of edges cases can be ignored.

1. ##### move forward with stack

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
    stack<int> s;
        int res, num1, num2;
        for (auto & op : tokens) {
            // care for cases when "-22".
            if (!(op.size() == 1 && op[0] < 48))
                s.push(stoi(op));
            else {
                num2 = s.top(); s.pop();
                num1 = s.top(); s.pop();
                switch (op[0]) {
                    case '+': s.push(num1 + num2); break;
                    case '-': s.push(num1 - num2); break;
                    case '*': s.push(num1 * num2); break;
                    case '/': s.push(num1 / num2); break;
                }
            }
        }
        return s.top();
    }
};
```

- use map to control logic branches.

```c++
class Solution {
public:
    int evalRPN(vector<string> & tokens) {
        unordered_map<string, function<int (int, int)>> mop = {
            { "+", [] (int a, int b) { return a + b; } },
            { "-", [] (int a, int b) { return a - b; } },
            { "*", [] (int a, int b) { return a * b; } },
            { "/", [] (int a, int b) { return a / b; } }
        };
        stack<int> s;

        for (auto & op : tokens) {
            if (mop.count(op)) {
                int num2 = s.top(); s.pop();
                int num1 = s.top(); s.pop();
                s.push(mop[op](num1, num2));
            } else
                s.push(stoi(op));
        }
        return s.top();
    }
};

```


2. ##### move backward with recursion

- borrowed from others
- Evaluate from the back to the front.
    - Whenever meets a opearation string, call the same function to get the operated num1 and num2.
    - Just return this number when a number string is encountered.

```c++
class Solution {
public:
    int evalRPN(vector<string> & tokens) {
        string s = tokens.back(); tokens.pop_back();
        if (!(s.size() == 1 && s[0] < 48))
            return stoi(s);
        else {
            auto num2 = evalRPN(tokens);
            auto num1 = evalRPN(tokens);
            switch (s[0]) {
                case '+': return num1 + num2; 
                case '-': return num1 - num2;
                case '*': return num1 * num2;
                case '/': return num1 / num2;
            }
        }
        return 0;
    }
};


```
