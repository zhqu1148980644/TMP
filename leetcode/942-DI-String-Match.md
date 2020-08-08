Given a string S that only contains "I" (increase) or "D" (decrease), let N = S.length.

Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:

If S[i] == "I", then A[i] < A[i+1]
If S[i] == "D", then A[i] > A[i+1]
 

Example 1:

Input: "IDID"
Output: [0,4,1,3,2]
Example 2:

Input: "III"
Output: [0,1,2,3]
Example 3:

Input: "DDI"
Output: [3,2,0,1]

#### Solutions

1. ##### math

- Maximise the range of available numbers. ie: meets I, then push the minimum available number, vice versa.

```c++
class Solution {
public:
    vector<int> diStringMatch(string S) {
        int lo = 0, hi = S.size();
        vector<int> res;
        for (auto op : S) {
            if (op == 'I')
                res.push_back(lo++);
            else
                res.push_back(hi--);
        }
        res.push_back(lo);
        return res;
    }
};
```