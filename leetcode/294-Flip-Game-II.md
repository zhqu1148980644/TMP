You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

Example:

Input: s = "++++"
Output: true 
Explanation: The starting player can guarantee a win by flipping the middle "++" to become "+--+".
Follow up:
Derive your algorithm's runtime complexity.

#### Solutions

1. ##### dfs with memoization O(2^n)

```c++
class Solution {
public:
    unordered_map<string, bool> m;
    bool canwin(string s) {
        if (m.count(s)) return m[s];
        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == '+' && s[i + 1] == '+') {
                s[i] = '-'; s[i + 1] = '-';
                bool res = !canwin(s);
                s[i] = '+'; s[i + 1] = '+';
                if (res) return m[s] = true;
            }
        }
        return m[s] = false;
    }
    bool canWin(string s) {
        if (s.size() < 2) return false;
        return canwin(s);
    }
};
```


2. ##### SG O(n2)