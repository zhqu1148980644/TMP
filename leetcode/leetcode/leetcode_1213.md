---
title: Intersection of Three Sorted Arrays
date: 2021-01-04
---
Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order, return a sorted array of only the integers that appeared in all three arrays.

 

Example 1:

Input: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
Output: [1,5]
Explanation: Only 1 and 5 appeared in the three arrays.
 

Constraints:

1 <= arr1.length, arr2.length, arr3.length <= 1000
1 <= arr1[i], arr2[i], arr3[i] <= 2000

#### Solutions

1. ##### two pointers

```cpp
class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        vector<int> res;
        int n1 = arr1.size(), n2 = arr2.size(), n3 = arr3.size();
        int i = 0, j = 0, k = 0;

        while (i < n1 && j < n2 && k < n3) {
            int a = arr1[i], b = arr2[j], c = arr3[k];
            if (a == b && b == c) {
                i++; j++; k++; res.push_back(a);
            }
            else
                if (b < a || c < a) {
                    if (b < a) j++;
                    if (c < a) k++;
                }
                else i++;
        }

        return res;
    }
};
```

or use binary search when the array with the minimum length is too small compared to the other two's.