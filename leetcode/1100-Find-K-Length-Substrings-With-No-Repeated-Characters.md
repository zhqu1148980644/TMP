Given a string S, return the number of substrings of length K with no repeated characters.

 

Example 1:

Input: S = "havefunonleetcode", K = 5
Output: 6
Explanation: 
There are 6 substrings they are : 'havef','avefu','vefun','efuno','etcod','tcode'.
Example 2:

Input: S = "home", K = 5
Output: 0
Explanation: 
Notice K can be larger than the length of S. In this case is not possible to find any substring.
 

Note:

1 <= S.length <= 10^4
All characters of S are lowercase English letters.
1 <= K <= 10^4

#### Solutions

1. ##### hashmap

```c++
class Solution {
public:
    int numKLenSubstrNoRepeats(string S, int K) {
        if (K > S.size()) return 0;
        vector<int> count(126);
        int cnt = 0;
        for (int i = 0; i < K; i++)
            if (++count[S[i]] == 1) cnt++;
        
        int res = 0;
        if (cnt == K) res++;
        for (int i = K; i < S.size(); i++) {
            if (--count[S[i - K]] == 0) cnt--;
            if (++count[S[i]] == 1) cnt++;
            res += cnt == K;
        }

        return res;
    }
};
```