Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.

 

Example 1:

Input: "abbaca"
Output: "ca"
Explanation: 
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
 

Note:

1 <= S.length <= 20000
S consists only of English lowercase letters.

#### Solutions

1. ##### simulate with list

```c++
class Solution {
public:
    string removeDuplicates(string S) {
        if (S.size() < 2) return S;
        list<char> s(S.begin(), S.end());
        s.push_front(' ');
        auto cur = s.begin();
        auto next = cur++;
        while (next != s.end())
            if (*cur != *next)
                cur = next++;
            else {
                next = s.erase(cur, ++next);
                cur = prev(next);
            }

        s.pop_front();
        return {s.begin(), s.end()};
    }
};
```

2. ##### stack

```c++
class Solution {
public:
    string removeDuplicates(string S) {
        int top = 0;
        for (auto c : S) {
            if (!top || c != S[top - 1])
                S[top++] = c;
            else
                top--;
        }

        S.resize(top);
        return S;
    }
};
```