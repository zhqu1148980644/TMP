Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.

 

Example 1:

Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
 

Note:

1 <= A.length <= 5000
0 <= A[i] <= 5000

#### Solutions

1. ##### two points

```c++
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int n = A.size(), i = 0, j = n - 1;
        while (i < j)
            if (A[i] & 1)
                swap(A[i], A[j--]);
            else
                i++;
        return A;
    }
};
```

or

```c++
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int n = A.size(), i = 0, j = n - 1;
        while (i < j) {
            while (i < j && A[j] & 1)
                j--;
            while (i < j && A[i] % 2 == 0)
                i++;
            swap(A[i++], A[j--]);
        }
        return A;
    }
};
```