---
title: Global and Local Inversions
date: 2021-01-04
---
We have some permutation A of [0, 1, ..., N - 1], where N is the length of A.

The number of (global) inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j].

The number of local inversions is the number of i with 0 <= i < N and A[i] > A[i+1].

Return true if and only if the number of global inversions is equal to the number of local inversions.

Example 1:

Input: A = [1,0,2]
Output: true
Explanation: There is 1 global inversion, and 1 local inversion.
Example 2:

Input: A = [1,2,0]
Output: false
Explanation: There are 2 global inversions, and 1 local inversion.
Note:

A will be a permutation of [0, 1, ..., A.length - 1].
A will have length in range [1, 5000].
The time limit for this problem has been reduced.

#### Solutions

1. ##### straight forward

- Check if numbers in the array are monotonically increasing except local inversion points.

```cpp
class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        A.push_back(INT_MAX);
        int revcnt = 0, prevmax = INT_MIN;
        for (int i = 0; i < A.size() - 1; i++) {
            // ensure there is only one local inversion.
            // do not set premax at inversion points
            if (A[i] > A[i + 1]) {
                if (++revcnt > 1) return false;
            }
            // ensure all numbers are larger/eq than the maximum number before
            else if (A[i] >= prevmax) {
                prevmax = revcnt == 1 ? A[i - 1] : A[i];
                revcnt = 0;
            }
            else
                return false;
        }

        return true;
    }
};
```

- Or chcek if all `i` satisfies `max[:i] <= nums[i + 2]`.

```cpp
class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        int curmax = 0;
        for (int i = 0; i < (int)A.size() - 2; i++) {
            curmax = max(A[i], curmax);
            if (curmax > A[i + 2])
                return false;
        }
        return true;
    }
};
```

2. ##### math

- Borrowed from the official answer.

```cpp
class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        if (!A.size()) return false;
        for (int i = 0; i < A.size(); i++)
            if (abs(A[i] - i) > 1)
                return false;

        return true;
    }
};
```