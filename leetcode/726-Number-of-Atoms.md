Given a chemical formula (given as a string), return the count of each atom.

An atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.

1 or more digits representing the count of that element may follow if the count is greater than 1. If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.

Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula. For example, (H2O2) and (H2O2)3 are formulas.

Given a formula, output the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

Example 1:
Input: 
formula = "H2O"
Output: "H2O"
Explanation: 
The count of elements are {'H': 2, 'O': 1}.
Example 2:
Input: 
formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: 
The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:
Input: 
formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: 
The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
Note:

All atom names consist of lowercase letters, except for the first character which is uppercase.
The length of formula will be in the range [1, 1000].
formula will only consist of letters, digits, and round parentheses, and is a valid formula as defined in the problem.

#### Solutions

1. ##### stack with hash map

```c++
class Solution {
public:
    string countOfAtoms(string formula) {
        formula.push_back(' ');
        stack<unordered_map<string, int>> s; s.push({});

        string prevc;
        int i = 0, len = formula.size();
        while (i < len) {
            auto curc = formula[i];
            if (isdigit(curc)) {
                int num = curc - '0';
                while (++i < len && isdigit(formula[i]))
                    num = num * 10 + (formula[i] - '0');
                // two cases:  O2   and (AgC)2
                if (prevc != ")")
                    s.top()[prevc] += num - 1;
                else {
                    for (auto & [c, n] : s.top())
                        n *= num;
                    auto curm = move(s.top()); s.pop();
                    for (auto & [c, n] : curm)
                        s.top()[c] += n;
                }
            }
            else if (curc == '(') {
                s.push({}); i++;
            }
            else if (curc == ')') {
                prevc = ")"; i++;
            }
            else {
                int size = i + 1 < len && islower(formula[i + 1]) ? 2 : 1;
                s.top()[prevc = formula.substr(i, size)]++;
                i += size;
            }
        }

        auto & m = s.top(); m.erase(" ");
        vector<string> vs(m.size());
        int w = 0;
        for (auto & [c, n] : m)
            vs[w++] = c;
        sort(vs.begin(), vs.end());

        string res;
        for (auto & s : vs)
            res += m[s] > 1 ? (s + to_string(m[s])) : s;

        return res;
    }
};
```