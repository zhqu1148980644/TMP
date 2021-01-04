---
title: Partition Array Into Three Parts With Equal Su
date: 2021-01-04
---
Given an array A of integers, return true if and only if we can partition the array into three non-empty parts with equal sums.

Formally, we can partition the array if we can find indexes i+1 < j with (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1])

 

Example 1:

Input: A = [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
Example 2:

Input: A = [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false
Example 3:

Input: A = [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
 

Constraints:

3 <= A.length <= 50000
-10^4 <= A[i] <= 10^4

#### Solutions

1. ##### straight forward

- Find the first two part with sum equals to `total/3`, then break and check if the remaining sum is equal to `total/3`.

```cpp
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int sum = accumulate(A.begin(), A.end(), 0);
        if (sum % 3 != 0) return false;
        
        int target = sum / 3, cnt = 0, cur = 0;
        int i = 0;
        while (i < A.size()) {
            cur += A[i]; sum -= A[i++];
            if (cur == target) {
                if (++cnt == 2) break;
                cur = 0;
            }
        }

        return i < A.size() && sum == target;
    }
};
```

2. ##### two pointers

```cpp
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        if (A.size() < 3) return false;
        int sum = accumulate(A.begin(), A.end(), 0);
        if (sum % 3 != 0) return false;
        
        // make sure each part has at least 1 element.
        int target = sum / 3, suma = A[0], sumb = A.back();
        int i = 1, j = A.size() - 2;
        while (i < j) {
            if (suma != target)
                suma += A[i++];
            if (sumb != target)
                sumb += A[j--];
            if (i > j) return false;
            if (suma == target && sumb == target)
                break;
        }

        return suma == sumb  && suma == target;
    }
};
```