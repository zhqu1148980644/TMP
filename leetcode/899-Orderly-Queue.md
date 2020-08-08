A string S of lowercase letters is given.  Then, we may make any number of moves.

In each move, we choose one of the first K letters (starting from the left), remove it, and place it at the end of the string.

Return the lexicographically smallest string we could have after any number of moves.

 

```
Example 1:

Input: S = "cba", K = 1
Output: "acb"
Explanation: 
In the first move, we move the 1st character ("c") to the end, obtaining the string "bac".
In the second move, we move the 1st character ("b") to the end, obtaining the final result "acb".

Example 2:

Input: S = "baaca", K = 3
Output: "aaabc"
Explanation: 
In the first move, we move the 1st character ("b") to the end, obtaining the string "aacab".
In the second move, we move the 3rd character ("c") to the end, obtaining the final result "aaabc".
```

 

#### Note:

-    1 <= K <= S.length <= 1000
-    S consists of lowercase letters only.


#### Solutions

1. ##### math

- If `k == 1`, return the lexicographical smallest string by iteratively removing the first character and pushing onto the back.
- Else `k > = 2`, we can reverse the order of any pair of two adjacent characters.
    - We can reverse `s[i]` and `s[i + 1]` following the rules below:
    - Iteratively moving the head character at the back till `[i, i + 1, 0, 1, ... i - 1]`.
    - Choose the second character `s[i + 1]` and push onto the back. `[i, 0, 1, ... i - 1, i + 1]`. 
    - Choose the first character `s[i]` and push onto the back. `[0, 1, ... i - 1, i + 1, i]`.
- Bubble sort sorts the array using the same strategy, thus the minimum string is the sorted string.

```c++
class Solution {
public:
    string orderlyQueue(string S, int K) {
        if (K > 1) {
            sort(S.begin(), S.end());
            return S;
        }
        else {
            string res = S;
            for (int i = 1; i < S.size(); i++)
                res = min(res, S.substr(i) + S.substr(0, i));
            return res;
        }
    }
};
```