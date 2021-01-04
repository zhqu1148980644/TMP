---
title: Delete Columns to Make Sorted II
date: 2021-01-04
---
We are given an array A of N lowercase letter strings, all of the same length.

Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef","vyz"].

Suppose we chose a set of deletion indices D such that after deletions, the final array has its elements in lexicographic order (A[0] <= A[1] <= A[2] ... <= A[A.length - 1]).

Return the minimum possible value of D.length.

 

Example 1:

Input: ["ca","bb","ac"]
Output: 1
Explanation: 
After deleting the first column, A = ["a", "b", "c"].
Now A is in lexicographic order (ie. A[0] <= A[1] <= A[2]).
We require at least 1 deletion since initially A was not in lexicographic order, so the answer is 1.
Example 2:

Input: ["xc","yb","za"]
Output: 0
Explanation: 
A is already in lexicographic order, so we don't need to delete anything.
Note that the rows of A are not necessarily in lexicographic order:
ie. it is NOT necessarily true that (A[0][0] <= A[0][1] <= ...)
Example 3:

Input: ["zyx","wvu","tsr"]
Output: 3
Explanation: 
We have to delete every column.
 

Note:

1 <= A.length <= 100
1 <= A[i].length <= 100

#### Solutions

1. ##### greedy strategy

- Iteratively removing columns from the left that doesn't satisfy the lexicographical order and stop when the current column suits.

```cpp
class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        if (!A.size()) return 0;
        int n = A.size(), len = A[0].size(), del = 0;

        bitset<101> issmall;
        for (int i = 0; i < len; i++) {
            bitset<101> cur;
            bool needdel = false;
            int numeq = 0;
            for (int j = 0; j < n - 1; j++) {
                if (!issmall[j] && A[j][i] > A[j + 1][i]) {
                    needdel = true; break;
                }
                cur[j] = A[j][i] < A[j + 1][i];
                numeq += A[j][i] == A[j + 1][i];
            }
            del += needdel;
            if (!needdel) {
                if (numeq == 0) break;
                issmall |= cur;
            }
        }

        return del;
    }
};
```