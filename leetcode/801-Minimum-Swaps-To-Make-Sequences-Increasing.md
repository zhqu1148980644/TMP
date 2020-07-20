We have two integer sequences A and B of the same non-zero length.

We are allowed to swap elements A[i] and B[i].  Note that both elements are in the same index position in their respective sequences.

At the end of some number of swaps, A and B are both strictly increasing.  (A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)

Given A and B, return the minimum number of swaps to make both sequences strictly increasing.  It is guaranteed that the given input always makes it possible.

```
Example:
Input: A = [1,3,5,4], B = [1,2,3,7]
Output: 1
Explanation: 
Swap A[3] and B[3].  Then the sequences are:
A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
which are both strictly increasing.
```

#### Note:

-    A, B are arrays with the same length, and that length will be in the range [1, 1000].
-    A[i], B[i] are integer values in the range [0, 2000].


#### Solutions

1. ##### dynamic programming O(n)

- To make an array sorted, we just need to esure every pair of adjacent elements are ordered.
- Thus, the problem of making `s[:i]` sorted can be solved by firstly solving `s[:i - 1]`(dynamic programming).
- To check if two adjacent elements are sorted, we need to know if the former character has been swapped. The subproblem(previous pair) has two states: 
    - The last pair of characters has been swapped.
    - Remain the same.
- There are two conditions need to be considered to ensure every pair of ajacent numbers are in sorted order.
    - `A[i] > A[i - 1] and B[i] > B[i - 1]`
    - `A[i] > B[i - 1] and B[i] > A[i - 1]`
    - For every possible `i`, `at least` one of two conditions is satisfied.
- `dp[i][keep]` represents the minimum swap to make s[:i] sorted with the last pair of numbers not swapped.
- `dp[i][swap]` the last pair of numbers was swapped.


```c++
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int keep = 0, swap = 1;
        for (int i = 1; i < A.size(); i++) {
            int curkeep = INT_MAX, curswap = INT_MAX;
            if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
                curkeep = min(curkeep, keep);
                curswap = min(curswap, swap + 1);
            }

            if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
                curkeep = min(curkeep, swap);
                curswap = min(curswap, keep + 1);
            }

            keep = curkeep;
            swap = curswap;
        }

        return min(keep, swap);
    }
};
```