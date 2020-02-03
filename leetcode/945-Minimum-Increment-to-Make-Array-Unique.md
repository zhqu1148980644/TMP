Given an array of integers A, a move consists of choosing any A[i], and incrementing it by 1.

Return the least number of moves to make every value in A unique.

 

```
Example 1:

Input: [1,2,2]
Output: 1
Explanation:  After 1 move, the array could be [1, 2, 3].

Example 2:

Input: [3,2,1,2,1,7]
Output: 6
Explanation:  After 6 moves, the array could be [3, 4, 1, 2, 5, 7].
It can be shown with 5 or less moves that it is impossible for the array to have all unique values.
```
 

#### Note:

    0 <= A.length <= 40000
    0 <= A[i] < 40000


##### Solutions


1. ##### counting O(range)

- Use buckets to store each unique value.

```c++
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        vector<int> buckets(100000);
        for (auto & n : A)
            buckets[n]++;
        
        int remain = 0, res = 0;
        for (int i = 0; i < 100000; i++) {
            if (buckets[i] >= 2) {
                remain += buckets[i] - 1;
                res -= i * (buckets[i] - 1);
            } else if (remain && buckets[i] == 0) {
                remain--;
                res += i;
            }
        }

        return res;
    }
};
```

2. ##### sort O(nlog(n))

```c++
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        if (!A.size()) return 0;
        sort(A.begin(), A.end());

        int prev = A[0], steps = 0;
        for (int i = 1; i < A.size(); i++) {
            if (A[i] <= prev)
                steps += prev++ - A[i] + 1;
            else
                prev = A[i];
        }
        
        return steps;
    }
};
```