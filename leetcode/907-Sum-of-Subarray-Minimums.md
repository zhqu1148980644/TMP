Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.

Since the answer may be large, return the answer modulo 10^9 + 7.

 

Example 1:

Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.
 

Note:

1 <= A.length <= 30000
1 <= A[i] <= 30000
 

#### Solutions


1. ##### mono stack

- reference: https://leetcode-cn.com/problems/sum-of-subarray-minimums/solution/c-dan-diao-zhan-jie-fa-by-da-li-wang/
- `Sum[i]` represents the the sum of min of subarrays end with `A[i]`(includeing A[i]).

```c++
class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        stack<int> s;
        vector<int> sums(A.size());
        for (int i = 0; i < A.size(); i++) {
            // monotonically increasing stack
            while (!s.empty() && A[s.top()] > A[i])
                s.pop();
            // all numbers left are larger than self
            if (s.empty())
                sums[i] = (i + 1) * A[i];
            else                
                // counts of subarrays with A[s.top()] as the minimum number and end with A[i] as right most element
                // counts of subarrays with A[i] as the minimum number and end with A[i].
                // if i - s.top() != 1, these exlucded numbers must be larger than A[i].
                sums[i] = sums[s.top()] + (i - s.top()) * A[i];
            s.push(i);
        }

        const long MOD = 1e9 + 7;
        long res = 0;
        for (auto n : sums)
            res = (res + n) % MOD;
        
        return res;
    }
};
```


or


```c++
class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        long res = 0, MOD = 1e9 + 7;

        A.push_back(-1);
        stack<pair<int, int>> s;
        for (int i = 0; i < A.size(); i++) {
            while (!s.empty() && A[s.top().first] > A[i]) {
                res = (res + s.top().second) % MOD;
                s.pop();
            }
            int cursum = 0;
            if (s.empty())
                cursum = (i + 1) * A[i];
            else
                cursum = s.top().second + (i - s.top().first) * A[i];
            s.emplace(i, cursum);
        }

        return res;
    }
};
```

2. ##### monstack

- ?????, how ???

```c++
class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        long long MOD = 1e9 + 7;
        stack<int> s;
        long long cur_sum = 0, ans = 0;
        for (int i = 0; i < A.size(); ++i) {
            while (!s.empty() && A[s.top()] >= A[i]) {
                int top = s.top(); s.pop();
                int new_top = s.empty() ? -1 : s.top();
                cur_sum += (A[i] - A[top]) * (top - new_top);
            }
            cur_sum += A[i];
            s.push(i);
            ans += cur_sum;
        }
        return ans % MOD;      
    }
};
```