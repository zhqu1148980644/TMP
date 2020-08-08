Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.

 

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Note:

1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A is sorted in non-decreasing order.

#### Solutions

1. #### merge sorted list

- When the first element is already a positive integer, simply return the square forms.

```c++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        if (!A.size()) return {};
        vector<int> res(A.size());
        int i = 0, j = A.size() - 1, w = A.size() - 1;
        while (i <= j) {
            if (A[j] * A[j] > A[i] * A[i])
                res[w--] = A[j] * A[j--];
            else
                res[w--] = A[i] * A[i++];
        }

        return res;
    }
};
```