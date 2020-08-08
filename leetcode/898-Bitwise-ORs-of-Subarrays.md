We have an array A of non-negative integers.

For every (contiguous) subarray B = [A[i], A[i+1], ..., A[j]] (with i <= j), we take the bitwise OR of all the elements in B, obtaining a result A[i] | A[i+1] | ... | A[j].

Return the number of possible results.  (Results that occur more than once are only counted once in the final answer.)

 

Example 1:

Input: [0]
Output: 1
Explanation: 
There is only one possible result: 0.
Example 2:

Input: [1,1,2]
Output: 3
Explanation: 
The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.
Example 3:

Input: [1,2,4]
Output: 6
Explanation: 
The possible results are 1, 2, 3, 4, 6, and 7.
 

Note:

1 <= A.length <= 50000
0 <= A[i] <= 10^9

#### Solutions

1. ##### dynamic programming

- reference: https://leetcode-cn.com/problems/bitwise-ors-of-subarrays/solution/c-si-lu-pou-xi-fu-yong-he-jian-zhi-by-wen-mu-yang/
- OR operations will collected all bit hasbeen visited thus the OR results are in monotonically increasing order.
- For the current `i`, `dp[j]` represents the OR operation of numbers in `num[j:i - 1]`.
- If `dp[j] == num[i]`, this denotes that `dp[j:i-1]` has collected all bits that are within the current number `nums[i]`, thus the OR result of `nums[k:i - 1]` equals to that of `nums[k:i]`, and because we are traversing the array forwards, `nums[k:i-1]` has already been visited before thus no need to visit again.

```c++
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        unordered_set<int> ors;
        for (int i = 0; i < A.size(); i++) {
            ors.insert(A[i]);
            for (int j = i - 1; j >= 0; j--) {
                // A[j] represents OR of numbers in A[j:i - 1]
                // A[j] == A[i] means all bits within A[j:i] has been recorded, thus OR of nums[k:i](k < j) would be the same as OR of nums[: i - 1] whcih is visited before.
                // can also be replaced with if ((A[j] | A[i]) == A[j])
                if ((A[j] & A[i]) == A[i])
                    break;
                // update dp[j] for further use
                ors.insert(A[j] |= A[i]);
            }
        }

        return ors.size();
    }
};
```