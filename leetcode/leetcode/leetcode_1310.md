---
title: XOR Queries of a Subarray
date: 2021-01-04
---
#### Given the array arr of positive integers and the array queries where queries[i] = [Li, Ri], for each query i compute the XOR of elements from Li to Ri (that is, arr[Li] xor arr[Li+1] xor ... xor arr[Ri] ). Return an array containing the result for the given queries.

 

```
Example 1:

Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
Output: [2,7,14,8] 
Explanation: 
The binary representation of the elements in the array are:
1 = 0001 
3 = 0011 
4 = 0100 
8 = 1000 
The XOR values for queries are:
[0,1] = 1 xor 3 = 2 
[1,2] = 3 xor 4 = 7 
[0,3] = 1 xor 3 xor 4 xor 8 = 14 
[3,3] = 8

Example 2:

Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
Output: [8,0,4,4]
```

 

#### Constraints:

-    1 <= arr.length <= 3 * 10^4
-    1 <= arr[i] <= 10^9
-    1 <= queries.length <= 3 * 10^4
-    queries[i].length == 2
-    0 <= queries[i][0] <= queries[i][1] < arr.length


#### Solutions

1. ##### xor prefix

- borrowed from others
- Xor of a collection of numbers is independent of the ordering xor operations.
- `x ^ x` equals `0` and `x ^ 0` equals `x`.

```cpp
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        // make the first position vacant to handle edges cases. ie index < 0
        int xor_prefix[arr.size() + 1] = {0};
        for (int i = 0; i < arr.size(); i++)
            xor_prefix[i + 1] = xor_prefix[i] ^ arr[i];

        vector<int> res;
        int l, r;
        for (auto & range : queries) {
            l = range[0], r = range[1] + 1;
            res.push_back(xor_prefix[l] ^ xor_prefix[r]);
        }
        return res;
    }
};
```