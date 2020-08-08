Given an array of integers A, consider all non-empty subsequences of A.

For any sequence S, let the width of S be the difference between the maximum and minimum element of S.

Return the sum of the widths of all subsequences of A. 

As the answer may be very large, return the answer modulo 10^9 + 7.

 

Example 1:

Input: [2,1,3]
Output: 6
Explanation:
Subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
The sum of these widths is 6.
 

Note:

1 <= A.length <= 20000
1 <= A[i] <= 20000

#### Solutions

1. ##### math O(n)

- reference: https://leetcode-cn.com/problems/sum-of-subsequence-widths/solution/pai-xu-shu-xue-by-lucifer1004/
- As subsequence are independance of positions of each element, sorting the array would not change the result.
- For element `A[i]`, there are `i` elements smaller than `A[i]`, thus all subsequences(2^i)(either choose or not) in the left side has the maximum with `number(A[i])`, then these subsequences would contribute `2^i * A[i]` to the final result. The same for subsequences in the right, the contribution are `-2^(n - i - 1) * A[i]`.

```c++
Sorted array in ascending order.
              |
           |
         |
       | |
     |   |
   |     A[i]
   0          n
```


```c++
class Solution {
public:
    int sumSubseqWidths(vector<int>& A) {
        long long MOD = 1e9 + 7, n = A.size();
        vector<long long> pow2(n); pow2[0] = 1;
        for (int i = 1; i < n; i++)
            pow2[i] = (pow2[i - 1] << 1) % MOD;
        sort(A.begin(), A.end());

        long long res = 0;
        for (int i = 0; i < n; i++) {
            int nl = i, nr = n - nl - 1;
            res = (res + (pow2[nl] - pow2[nr]) * A[i]) % MOD;
        }
        // res may be negative
        return (res + MOD) % MOD;
    }
};
```