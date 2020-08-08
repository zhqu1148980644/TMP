Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].

Return any permutation of A that maximizes its advantage with respect to B.

 

Example 1:

Input: A = [2,7,11,15], B = [1,10,4,11]
Output: [2,11,7,15]
Example 2:

Input: A = [12,24,8,32], B = [13,25,32,11]
Output: [24,32,8,12]
 

Note:

1 <= A.length = B.length <= 10000
0 <= A[i] <= 10^9
0 <= B[i] <= 10^9

#### Solutions

1. ##### greedy strategy with treemap O(nlog(n))

- For each number in the array B, choose the smallest number that is greater than the  current number, if this number does not exist, choose the smallest available number in array A.

```c++
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        multiset<int> s(A.begin(), A.end());
        vector<int> res(A.size());

        int w = 0;
        for (auto n : B) {
            auto find = s.upper_bound(n);
            if (find == s.end())
                find = s.begin();
            res[w++] = *find;
            s.erase(find);
        }
        return res;
    }
};
```

2. ##### greedy strategy with sort O(nlog(n))

- Sort both two arrays and find the slowest larger one in A array for each number in array B, if the required number doesn't exist in A then just mark it as unused and check for the next number in A. After this step, the prefix of B array(sorted version) has found their first larger one.
- At last, randomly(means the size of number doesn't matter) choose unused numbers in A to fill unmatched numbers in B.

```c++
#include <functional>
using namespace placeholders;
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> v1(n), v2(n);
        iota(v1.begin(), v1.end(), 0);
        iota(v2.begin(), v2.end(), 0);
        sort(v1.begin(), v1.end(), 
            [&](int i1, int i2) { return A[i1] < A[i2]; });
        sort(v2.begin(), v2.end(), 
            [&](int i1, int i2) { return B[i1] < B[i2]; });

        int w = 0;
        vector<int> res(n, -1);
        for (auto r : v1) {
            if (A[r] > B[v2[w]])
                res[v2[w++]] = A[r];
            else
                A[r] -= 1000000000;
        }

        int j = 0;
        for (auto & n : A)
            if (n < 0) {
                while (res[j] != -1) j++;
                res[j++] = (n += 1000000000);
            }
        
        return res;
    }
};
```