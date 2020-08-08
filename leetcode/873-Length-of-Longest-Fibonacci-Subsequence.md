A sequence X_1, X_2, ..., X_n is fibonacci-like if:

n >= 3
X_i + X_{i+1} = X_{i+2} for all i + 2 <= n
Given a strictly increasing array A of positive integers forming a sequence, find the length of the longest fibonacci-like subsequence of A.  If one does not exist, return 0.

(Recall that a subsequence is derived from another sequence A by deleting any number of elements (including none) from A, without changing the order of the remaining elements.  For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].)

 

Example 1:

Input: [1,2,3,4,5,6,7,8]
Output: 5
Explanation:
The longest subsequence that is fibonacci-like: [1,2,3,5,8].
Example 2:

Input: [1,3,7,11,12,14,18]
Output: 3
Explanation:
The longest subsequence that is fibonacci-like:
[1,11,12], [3,11,14] or [7,11,18].
 

Note:

3 <= A.length <= 1000
1 <= A[0] < A[1] < ... < A[A.length - 1] <= 10^9
(The time limit has been reduced by 50% for submissions in Java, C, and C++.)

#### Solutions

1. ##### dynamic programming O(n2)

- state is represented as unique tuple of (i, j, k) such that `A[i] + A[j] = A[k]`.

```c++
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        unordered_map<int, int> index;
        for (int i = 0; i < A.size(); i++)
            index[A[i]] = i;
        
        int n = A.size(), res = 0;
        // only need to record (j, k), i can be fethced uisng index(A[k] - A[j])
        unordered_map<int, int> longest;
        for (int k = 0; k < n; k++)
            for (int j = 0; j < k; j++) {
                if (A[k] - A[j] < A[j] && index.count(A[k] - A[j])) {
                    int i = index[A[k] - A[j]];
                    // hash each unique pair of (j, k)
                    longest[k * n + j] = longest[j * n + i] + 1;
                    res = max(res, longest[k * n + j] + 2);
                }
            }

        return res;
    }
};
```

2. ##### hash map O(n3)

- Try all possible heads`(i, j)` of Fibonacci sequences.


```c++
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        unordered_map<int, int> index;
        for (int i = 0; i < A.size(); i++)
            index[A[i]] = i;
        
        int n = A.size(), res = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int len = 2;
                int a = A[i], b = A[j];
                while (index.count(a + b)) {
                    res = max(res, ++len);
                    int c = a + b;
                    a = b; b = c;
                }
            }

        return res;
    }
};
``