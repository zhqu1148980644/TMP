Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
Note:
The given number is in the range [0, 108]

#### Solutions

1. ##### straight forward O(n)

- Start from the beginning of the string, replace the first character with the lasgest charater after it if it's greater than self.

```c++
class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        vector<int> v(s.size());

        v.back() = v.size() - 1;
        for (int i = s.size() - 2; i >= 0; i--)
            v[i] = s[i + 1] > s[v[i + 1]] ? i + 1 : v[i + 1];
        
        for (int i = 0; i < v.size() - 1; i++)
            if (s[v[i]] > s[i]) {
                swap(s[i], s[v[i]]);
                break;
            }

        return stoi(s);
    }
};
```

Another way is to firstly sort the string in descending order, and reverse the first char pair with the smaller one belongs to the original string when compared with the original string.