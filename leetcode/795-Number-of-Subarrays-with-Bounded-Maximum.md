We are given an array A of positive integers, and two positive integers L and R (L <= R).

Return the number of (contiguous, non-empty) subarrays such that the value of the maximum array element in that subarray is at least L and at most R.

Example :
Input: 
A = [2, 1, 4, 3]
L = 2
R = 3
Output: 3
Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
Note:

L, R  and A[i] will be an integer in the range [0, 10^9].
The length of A will be in the range of [1, 50000].

#### Solutions

1. ##### math

- `res = numunder(R) - numunder(L - 1)`, numunder(n) means the number of subarrays with the maximum number <= n.

```c++
class Solution {
public:
    int numunder(vector<int> & A, int bound) {
        int res = 0, cur = 0;
        for (auto n : A) {
            cur = n <= bound ? cur + 1 : 0;
            res += cur;
        }
        return res;
    }
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        return numunder(A, R) - numunder(A, L - 1);
    }
};
```


2. ##### sliding window

- reference: https://leetcode-cn.com/problems/number-of-subarrays-with-bounded-maximum/solution/javascripthua-dong-chuang-kou-fa-by-jack-108/
- `Window `A(abover: cur)` are numbers not greater than the upper_bound.
- `abovel` is the index of the first number >= lower_bound within the window.

```c++
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int abover = -1, abovel = -1, res = 0;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] <= R) {
                if (A[i] >= L) {
                    abovel = i;
                    // subarrays does not contain abover
                    res += i - abover;
                }
                else
                    // subarrays contaning abovel but not contain abover
                    res += abovel - abover;
            }
            else
                abovel = abover = i;
        }

        return res;
    }
};
```










### if the question asks the number of subarrays with sum at least L and at least R

```c++
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int i = 0, j = 0, sum = 0, res = 0;
        A.push_back(1e9);
        while (j < A.size()) {
            if ((sum + A[j]) > R && sum <= R)
                while ((sum -= A[i++]) >= L && ++res);
            sum += A[j++];
            if (sum > R)
                while ((sum -= A[i++]) > R);
            else
                res += sum >= L;
        }
        return res;
    }
};
```

