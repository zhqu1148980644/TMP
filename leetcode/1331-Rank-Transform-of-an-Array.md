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
        vector<int> index(arr.size());
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i1, int i2) {
            return arr[i1] < arr[i2];
        });

        vector<int> res(arr.size());
        res[index[0]] = 1;
        int r = 1;
        for (int i = 1; i < index.size(); i++) {
            if (arr[index[i]] != arr[index[i - 1]])
                res[index[i]] = ++r;
            else
                res[index[i]] = r;
        }
        return res;
    }
};
```


2. ##### hash map

```c++
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> res(arr);
        sort(res.begin(), res.end());
        unordered_map<int, int> m;
        int r = 1;
        for (auto n : res)
            if (!m.count(n))
                m[n] = r++;
        
        for (auto & n : arr)
            n = m[n];
        
        return arr;
    }
};
```