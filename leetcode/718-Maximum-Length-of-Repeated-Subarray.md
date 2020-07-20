Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:

Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation: 
The repeated subarray with maximum length is [3, 2, 1].
 

Note:

1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100

##### Solutions

1. #### binary search O((m + n)log(min(n, m)))

- Guess the maximum length using binary search strategy. In each guess state, use rabin-karp-like hashing method to check if the there exists a repeated substring in both two strings.

```c++
class Solution {
public:
    bool dup(vector<int> & A, vector<int> & B, int k) {
        unordered_set<long> seen;
        // be careful, don't choose 10 as the base, the problem said the num range is [0, 100], thus choose the first larger prime number as the base.
        long long m = 1e9 + 7, R = 113, ML = 1, h;
        // could also use fast power method to speed up time complexity from O(k) to log(k)
        for (int i = 1; i < k; i++)
            ML = (ML * R) % m;

        h = 0;
        for (int i = 0; i < k; i++)
            h = (h * R + A[i]) % m;
        seen.insert(h);
        for (int i = k; i < A.size(); i++) {
            h = (h - A[i - k] * ML) % m;
            h = (h * R + A[i]) % m;
            // must check
            if (h < 0) h += m;
            seen.insert(h);
        }

        h = 0;
        for (int i = 0; i < k; i++)
            h = (h * R + B[i]) % m;
        if (seen.count(h)) return true;
        for (int i = k; i < B.size(); i++) {
            h = (h - B[i - k] * ML) % m;
            h = (h * R + B[i]) % m;
            // must check
            if (h < 0) h += m;
            if (seen.count(h))
                return true;
        }

        return false;
    }
    int findLength(vector<int>& A, vector<int>& B) {
        int lo = 0, hi = min(A.size(), B.size());

        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            // the binary search is different than normal cases
            // to ensure the moveing direction's correctness, it should be if (!dup()) hi = mid - 1; else lo = mid.
            // However, this shrinking strategy would leads to endless loop.
            // for example: mid = (0 + 1) / 2, dup(mid) = true, then lo = 0 again.
            // A solution is to end loops when lo >= hi - 1, and then check both lo and lo + 1 for the final answer.
            // Or compare with mid + 1 like codes below, then the comparison is the same as normal case.
            if (dup(A, B, mid + 1))
                lo = mid + 1;
            else
                hi = mid;
        }

        return lo;
    }
};
```

2. ##### dynamic programming O(mn)

- `dp[i][j] = dp[i - 1][j - 1] + 1 if A[i] == A[j] else 0`

```c++
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size(), n = B.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        int res = 0;
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                res = max(res, dp[i][j] = A[i] == B[j] ? dp[i + 1][j + 1] + 1 : 0);

        return res;
    }
};
```

or

```c++
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        if (A.size() < B.size())
            return findLength(B, A);
        
        int m = A.size(), n = B.size(), res = 0;
        vector<int> dp(n + 1);

        for (int i = 1; i <= m; i++) {
            int diag = 0;
            for (int j = 1; j <= n; j++) {
                int tmp = dp[j];
                res = max(res, dp[j] = A[i - 1] == B[j - 1] ? diag + 1 : 0);
                diag = tmp;
            }
        }

        return res;
    }
};
```

3. ##### sliding window?  O((m + n) * min(m, n))

- Check the official answer

```c++
class Solution {
public:
    int duplen(vector<int> & A, vector<int> & B, int sta, int stb, int maxlen) {
        int len = 0, res = 0;
        for (int i = 0; i < maxlen; i++) {
            len = A[sta + i] == B[stb + i] ? len + 1 : 0;
            res = max(res, len);
        }
        return res;
    }
    int findLength(vector<int>& A, vector<int>& B) {
        if (A.size() < B.size())
            return findLength(B, A);
        int m = A.size(), n = B.size();

        int res = 0;
        for (int i = 0; i < m - res; i++) {
            int len = min(m - i, n);
            res = max(res, duplen(A, B, i, 0, len));
        }

        for (int i = 0; i < n - res; i++) {
            int len = min(n - i, m);
            res = max(res, duplen(A, B, 0, i, len));
        }

        return res;
    }
};
```