---
title: Relative Sort Array
date: 2021-01-04
---
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.  Elements that don't appear in arr2 should be placed at the end of arr1 in ascending order.

 

Example 1:

Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]
 

Constraints:

arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
Each arr2[i] is distinct.
Each arr2[i] is in arr1.

#### Solutions

1. ##### sort O(nlog(n))

```cpp
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> ranks(1001, INT_MAX);
        for (int i = 0; i < arr2.size(); i++)
            ranks[arr2[i]] = i + 1;
        
        sort(arr1.begin(), arr1.end(), [&](int n1, int n2) {
            if (ranks[n1] != ranks[n2])
                return ranks[n1] < ranks[n2];
            else
                return n1 < n2;
        });
        return arr1;
    }
};
```

- When the range of numbers in arr is too large, we can simply sort the trailing part.

```cpp
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> m;
        for (auto n : arr1)
            m[n]++;
        vector<int> res(arr1.size());
        int w = 0;
        // fill the first part
        for (auto n : arr2) {
            fill(res.begin() + w, res.begin() + w + m[n], n);
            w += m[n];
            m.erase(n);
        }
        int sortst = w;
        // fill the trailing part that doesn't appear in arr2
        for (auto [n, cnt] : m) {
            fill(res.begin() + w, res.begin() + w + cnt, n);
            w += cnt;
        }
        // sort the trailing part
        sort(res.begin() + sortst, res.end());

        return res;
    }
};
```


2. ##### count sort O(n)

```cpp
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> count(1001);
        for (auto n : arr1)
            count[n]++;
        
        int w = 0;
        // the first part
        for (auto n : arr2) {
            fill(arr1.begin() + w, arr1.begin() + w + count[n], n);
            w += count[n];
            count[n] = 0;
        }
        // the last part
        for (int n = 0; n < 1001; n++) {
            if (!count[n]) continue;
            fill(arr1.begin() + w, arr1.begin() + w + count[n], n);
            w += count[n];
        }
        
        return arr1;
    }
};
```