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

- Start from the beginning of the string, replace the current character with the lasgest charater after it if it's greater than self.

```c++
class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);

        vector<int> maxv(s.size());
        int maxi = s.size() - 1;
        // find the larget one each each one
        for (int i = (int)s.size() - 1; i >= 0; i--) {
            if (s[i] > s[maxi]) {
                maxi = i;
            }
            maxv[i] = maxi;
        }

        for (int i = 0; i < s.size(); i++)
            if (s[i] < s[maxv[i]]) {
                swap(s[i], s[maxv[i]]);
                break;
            }

        return stoi(s);
    }
};
```

Another way is to firstly sort the string in descending order, and reverse the first char pair with the smaller one belongs to the original string when compared with the original string.