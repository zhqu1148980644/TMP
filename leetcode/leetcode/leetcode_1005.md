---
title: Maximize Sum Of Array After K Negations
date: 2021-01-04
---
Given an array A of integers, we must modify the array in the following way: we choose an i and replace A[i] with -A[i], and we repeat this process K times in total.  (We may choose the same index i multiple times.)

Return the largest possible sum of the array after modifying it in this way.

 

Example 1:

Input: A = [4,2,3], K = 1
Output: 5
Explanation: Choose indices (1,) and A becomes [4,-2,3].
Example 2:

Input: A = [3,-1,0,2], K = 3
Output: 6
Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].
Example 3:

Input: A = [2,-3,-1,5,-4], K = 2
Output: 13
Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].
 

Note:

1 <= A.length <= 10000
1 <= K <= 10000
-100 <= A[i] <= 100

#### Solutions

1. ##### greedy with sort

- Prefer to flip lower numbers.
- For negative numbers we only flip it once and change it to positive.
- When k is still left after flipped all negative numbers, we choose to flip the one with the minimum absolute value(either it's negative or positive).

```cpp
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        if (!A.size()) return 0;
        sort(A.begin(), A.end());

        int i = 0;
        while (i < A.size() && A[i] < 0 && K) {
            A[i] = -A[i]; i++; K--;
        }
        if (i >= A.size()) i--;
        if (K) {
            if (i - 1 >= 0 && A[i - 1] < A[i])
                i = i - 1;
            A[i] = K % 2 == 0 ? A[i] : -A[i];
        }

        return accumulate(A.begin(), A.end(), 0);
    }
};
```


or use counting sort since the range of values are from 1-100, though it's length may be 10000.

2. ##### greedy with priority_queue

```cpp
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        auto cmp = [&](int i, int j) {
            return A[i] > A[j];
        };
        vector<int> pq(A.size()); iota(pq.begin(), pq.end(), 0);
        make_heap(pq.begin(), pq.end(), cmp);

        while (K) {
            pop_heap(pq.begin(), pq.end(), cmp);
            int mini = pq.back();
            if (A[mini] < 0) {
                A[mini] = -A[mini];
                push_heap(pq.begin(), pq.end(), cmp); 
            }
            else {
                A[mini] = K % 2 == 0 ? A[mini] : -A[mini];
                break;
            }
            K--;
        }

        return accumulate(A.begin(), A.end(), 0);
    }
};
```