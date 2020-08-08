A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:

For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

Return the length of a maximum size turbulent subarray of A.

 

Example 1:

Input: [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
Example 2:

Input: [4,8,12,16]
Output: 2
Example 3:

Input: [100]
Output: 1
 

Note:

1 <= A.length <= 40000
0 <= A[i] <= 10^9

#### Solutions

1. ##### dynamic programming

- Be careful to handle adjacent pairs with the same value, and the case when the array size is 1.

```c++
class Solution {
public:
    int maxTurbulenceSize(vector<int>& A) {
        // odd: the first rule, even: the second.
        int odd = 0, even = 0;
        int res = 0;
        for (int k = 0; k < A.size() - 1; k++) {
            if (A[k] == A[k + 1])
                odd = even = 0;
            else if (A[k] > A[k + 1] == k % 2 == 1) {
                odd++;
                even = 0;
            }
            else {
                even++;
                odd = 0;
            }

            res = max(res, max(odd, even) + 1);
        }
        return max(res, 1);
    }
};
```