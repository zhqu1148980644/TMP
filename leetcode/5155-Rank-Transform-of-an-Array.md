Given an array of integers arr, replace each element with its rank.

The rank represents how large the element is. The rank has the following rules:

-    Rank is an integer starting from 1.
-    The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
-    Rank should be as small as possible.

 

```
Example 1:

Input: arr = [40,10,20,30]
Output: [4,1,2,3]
Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.

Example 2:

Input: arr = [100,100,100]
Output: [1,1,1]
Explanation: Same elements share the same rank.

Example 3:

Input: arr = [37,12,28,9,100,56,80,5,12]
Output: [5,3,4,2,8,6,7,1,3]
```

 

#### Constraints:

-    0 <= arr.length <= 105
-    -109 <= arr[i] <= 109


#### Solutions

1. ##### straight forward


```c++
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        if (!arr.size()) return {};
        vector<pair<int, int>> A;
        for (int i = 0; i < arr.size(); i++)
            A.push_back({arr[i], i});
        sort(A.begin(), A.end(), [](pair<int, int> & a1, pair<int, int> & a2) {
            return a1.first < a2.first;
        });
        
        int index = 0;
        for (int i = 0; i < A.size(); i++) {
            if (i == 0 || A[i].first != A[i - 1].first)
                index++;
            arr[A[i].second] = index;
        }
        return arr;
    }
};
```


2. ##### hash map

```c++
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sarr = arr;
        sort(sarr.begin(), sarr.end());
        unordered_map<int, int> m;
        int i = 1;
        for (auto & num : sarr)
            if (!m.count(num))
                m[num] = i++;

        for (auto & num : arr)
            num = m[num];

        return arr;
    }
};
```