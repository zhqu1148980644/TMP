We have an array A of integers, and an array queries of queries.

For the i-th query val = queries[i][0], index = queries[i][1], we add val to A[index].  Then, the answer to the i-th query is the sum of the even values of A.

(Here, the given index = queries[i][1] is a 0-based index, and each query permanently modifies the array A.)

Return the answer to all queries.  Your answer array should have answer[i] as the answer to the i-th query.

 

Example 1:

Input: A = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
Output: [8,6,2,4]
Explanation: 
At the beginning, the array is [1,2,3,4].
After adding 1 to A[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
After adding -3 to A[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
After adding -4 to A[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
After adding 2 to A[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.
 

Note:

1 <= A.length <= 10000
-10000 <= A[i] <= 10000
1 <= queries.length <= 10000
-10000 <= queries[i][0] <= 10000
0 <= queries[i][1] < A.length

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        int even = 0;
        for (auto n : A)
            if (n % 2 == 0)
                even += n;

        int w = 0;
        vector<int> res(queries.size());
        for (auto & v : queries) {
            auto n = v[0];
            bool oldodd = A[v[1]] & 1;;
            bool newodd = n & 1;
            if (oldodd && newodd)
                even += n + A[v[1]];
            else if (!oldodd && !newodd)
                even += n;
            else if (!oldodd && newodd)
                even -= A[v[1]];
            res[w++] = even;
            A[v[1]] += n;
        }

        return res;
    }
};
```

or

```c++
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        int even = 0;
        for (auto n : A)
            if (n % 2 == 0)
                even += n;

        int w = 0;
        vector<int> res(queries.size());
        for (auto & v : queries) {
            int n = v[0], index = v[1];
            if (A[index] % 2 == 0)
                even -= A[index];
            A[index] += n;
            if (A[index] % 2 == 0)
                even += A[index];
            res[w++] = even;
        }

        return res;
    }
};
```