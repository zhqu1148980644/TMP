#### Given an array A of positive integers, A[i] represents the value of the i-th sightseeing spot, and two sightseeing spots i and j have distance j - i between them.

The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j) : the sum of the values of the sightseeing spots, minus the distance between them.

Return the maximum score of a pair of sightseeing spots.

 

```
Example 1:

Input: [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
```

 

#### Note:

-    2 <= A.length <= 50000
-    1 <= A[i] <= 1000


#### Solutions

1. ##### dynamic programming

- `(A[i] + A[j] + i - j)` equals to `(A[i] + i)  + (A[j] - j)`.
- Thus the problem is equivalent to finding the larget sum of two numbers in array.

```cpp
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int maxleft = 0, maxs = INT_MIN;
        for (int i = 0; i < A.size(); i++) {
            maxs = max(maxs, maxleft + A[i] - i);
            maxleft = max(maxleft, A[i] + i);
        }
        return maxs;
    }
};
```