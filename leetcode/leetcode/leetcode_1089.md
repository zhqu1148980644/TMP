---
title: Duplicate Zeros
date: 2021-01-04
---
Given a fixed length array arr of integers, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.

Do the above modifications to the input array in place, do not return anything from your function.

 

Example 1:

Input: [1,0,2,3,0,4,5,0]
Output: null
Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
Example 2:

Input: [1,2,3]
Output: null
Explanation: After calling your function, the input array is modified to: [1,2,3]
 

Note:

1 <= arr.length <= 10000
0 <= arr[i] <= 9

#### Solutions

1. ##### queue O(n) S(n)

```cpp
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        deque<int> dq;
        int i = 0;
        while (i < arr.size()) {
            dq.push_back(arr[i]);
            arr[i] = dq.front(); dq.pop_front();
            if (arr[i] == 0 && i + 1 < arr.size()) {
                dq.push_back(arr[i + 1]);
                arr[i++ + 1] = 0;
            }
            i++;
        }
    }
};
```

2. ##### two pass O(n) S(1)

- Count the number of elements needed to discard.
    - It should be mentioned that the last valid zero may not be duplicated successfully. ie: the duplicate is outside of the array.
- Then fill the array backwards starting form the last valid element.

```cpp
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int over = 0;
        bool unfull = false;
        for (int i = 0; i <= arr.size(); i++) {
            over += arr[i] == 0;
            // the duplicate of the curent 0 can be putted at the back
            if (i + over == arr.size() - 1)
                break;
            // cannot, the duplicate 0 is outside of the array
            else if (i + over >= arr.size()) {
                unfull = true; over--; break;
            }
        }
        int r = arr.size() - over - 1, w = arr.size() - 1;
        // for the last 0 with duplicate outside of the array, do not duplicate it
        if (unfull)
            arr[w--] = arr[r--];
        while (r >= 0) {
            if (arr[r--] == 0) {
                arr[w--] = 0; arr[w--] = 0;
            }
            else
                arr[w--] = arr[r + 1];
        }
    }
};
```