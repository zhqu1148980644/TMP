Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.

If there is no non-empty subarray with sum at least K, return -1.

 

Example 1:

Input: A = [1], K = 1
Output: 1
Example 2:

Input: A = [1,2], K = 4
Output: -1
Example 3:

Input: A = [2,-1,2], K = 3
Output: 3
 

Note:

1 <= A.length <= 50000
-10 ^ 5 <= A[i] <= 10 ^ 5
1 <= K <= 10 ^ 9

#### Solutions

1. ##### mono stack O(n)

- From the official answer.
- Note that since the prefix sum is not monoincreasing due to the existence of negative numbers. We can not directly use sliding window strategy.
- For example, `[10 -5 15] K = 13`. The prefix sum is `[10, 5, 20]`
    - The prefix sum becomes >= K when `j == 2`, then the window's left boundary starts to shrink untill the windows's sum is smaller than `K = 13`, the stop point is number `10`, however `[10, -5, 15]` is not the smallest window with `sum >= k`.
- The solution is to only record prefix sums in monotonically increasing order, suppose `prefix[i] > prefix[j] with i < j`, then discard `prefix[i]` is totally more reasonable because `sum[j:k]` is definitely larger than `sum[i:k]` and with shorter length. After the stack has been built in this way, use the same strategy as in sliding window to shrink the left boundary till the sum is smaller `K`. ie: Find the last element `i` with `sums[k] - sums[i] >= k`.

```c++
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size(), cursum = 0, res = INT_MAX;
        // sum[i] represents prefix sum of array[:i]

        deque<pair<int, int>> mq;
        // must be put in
        mq.push_back({0, -1});
        for (int i = 0; i < n; i++) {
            cursum += A[i];
            while (!mq.empty() && mq.back().first >= cursum)
                mq.pop_back();
            // ie: cursum - presum >= K. find the last element satisfy this requirement.
            while (!mq.empty() && mq.front().first <= cursum - K) {
                res = min(i - mq.front().second, res);
                mq.pop_front();
            }
            mq.push_back({cursum, i});
        }

        return res == INT_MAX ? -1 : res;
    }
};
```

or replace the deque with a stack.

```c++
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        vector<pair<int, int>> sums;
        sums.push_back({0, -1});
        int i = 0, j = 0, cursum = 0, res = INT_MAX;
        while (j < A.size()) {
            cursum += A[j];
            while (sums.size() && sums.back().first >= cursum)
                sums.pop_back();
            while (i < sums.size() && cursum - sums[i].first >= K)
                res = min(j - sums[i++].second, res);
            sums.emplace_back(cursum, j++);
        }

        return res == INT_MAX ? -1 : res;
    }
};
```