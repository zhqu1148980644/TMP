---
title: Pancake Sorting
date: 2021-01-04
---
Given an array A, we can perform a pancake flip: We choose some positive integer k <= A.length, then reverse the order of the first k elements of A.  We want to perform zero or more pancake flips (doing them one after another in succession) to sort the array A.

Return the k-values corresponding to a sequence of pancake flips that sort A.  Any valid answer that sorts the array within 10 * A.length flips will be judged as correct.

 

Example 1:

Input: [3,2,4,1]
Output: [4,2,4,3]
Explanation: 
We perform 4 pancake flips, with k values 4, 2, 4, and 3.
Starting state: A = [3, 2, 4, 1]
After 1st flip (k=4): A = [1, 4, 2, 3]
After 2nd flip (k=2): A = [4, 1, 2, 3]
After 3rd flip (k=4): A = [3, 2, 1, 4]
After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted. 
Example 2:

Input: [1,2,3]
Output: []
Explanation: The input is already sorted, so there is no need to flip anything.
Note that other answers, such as [3, 3], would also be accepted.
 

Note:

1 <= A.length <= 100
A[i] is a permutation of [1, 2, ..., A.length]

#### Solutions

1. ##### simulation O(n2)

- At each iteration, find the largest number and stack it at the front of the sorted suffix utill the whole array is sorted.

```cpp
class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        vector<int> res;
        int j = A.size() - 1;

        while (j > 0) {
            auto pos = max_element(A.begin(), A.begin() + j + 1) - A.begin();
            if (pos != j) {
                res.push_back(pos + 1);
                res.push_back(j + 1);
                reverse(A.begin(), A.begin() + pos + 1);
                reverse(A.begin(), A.begin() + j + 1);
            }
            j--;
        }

        return res;
    }
};
```