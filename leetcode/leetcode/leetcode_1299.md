---
title: Replace Elements with Greatest Element on Right Side
date: 2021-01-04
---
#### Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.

After doing so, return the array.

 

```
Example 1:

Input: arr = [17,18,5,4,6,1]
Output: [18,6,6,6,1,-1]
```
 

#### Constraints:

- 1 <= arr.length <= 10^4
- 1 <= arr[i] <= 10^5

#### Solutions

1. Straight forward

```cpp
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        if (!arr.size()) return arr;
        int maxval = arr[arr.size() - 1];
        arr[arr.size() - 1] = -1;
        if (arr.size() >= 2) {
            for (int i = arr.size() - 2; i >= 0; i--) {
                int cur = arr[i];
                arr[i] = maxval;
                maxval = max(cur, maxval);
            }
        }
        return arr;
    }
};
```
