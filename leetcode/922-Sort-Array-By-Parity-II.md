Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.

You may return any answer array that satisfies this condition.

 

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
 

Note:

2 <= A.length <= 20000
A.length % 2 == 0
0 <= A[i] <= 1000

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        vector<int> res(A.size());
        int we = 0, wo = 1;
        for (auto n : A) {
            if (n & 1) {
                res[wo] = n; wo += 2;
            }
            else {
                res[we] = n; we += 2;
            }
        }

        return res;
    }
};
```

2. ##### inplace with two pointers

```c++
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int j = 1;
        for (int i = 0; i < A.size(); i += 2) {
            if (A[i] & 1) {
                while (A[j] & 1) j += 2;
                swap(A[i], A[j]);
            }
        }
        return A;
    }
};
```