Given an array A of integers, for each integer A[i] we need to choose either x = -K or x = K, and add x to A[i] (only once).

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the minimum value of B.

 

Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]
Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]
Example 3:

Input: A = [1,3,6], K = 3
Output: 3
Explanation: B = [4,6,3]
 

Note:

1 <= A.length <= 10000
0 <= A[i] <= 10000
0 <= K <= 10000

#### Solutions

1. ##### greedy O(nlog(n))

- reference: https://leetcode-cn.com/problems/smallest-range-ii/solution/tai-nan-liao-zhi-neng-hua-tu-ping-zhi-jue-by-user8/
- Split the sorted array into two parts, then move the lower part `k` steps forward and the other part `k` steps downward. Check reference for demonstration figures.

```c++
class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        if (A.size() <= 1) return 0;
        sort(A.begin(), A.end());

        int n = A.size(), res = A.back() - A.front();
        for (int i = 0; i < n - 1; i++) {
            int hi = max(A[i] + K, A[n - 1] - K);
            int lo = min(A[0] + K, A[i + 1] - K);
            res = min(res, hi - lo);
        }

        return res;
    }
};
```