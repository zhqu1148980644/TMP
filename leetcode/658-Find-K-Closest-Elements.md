Given a sorted array arr, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
 

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 10^4
Absolute value of elements in the array and x will not exceed 104


#### Solutions


1. ##### two pointers

- Iteratively removing the border with larger diff value.

```c++
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int i = 0, j = arr.size() - 1;
        while (i < j && j - i + 1 > k)
            if (x - arr[i] <= arr[j] - x)
                j--;
            else
                i++;
        
        return {arr.begin() + i, arr.begin() + i + k};
    }
};
```


2. ##### binary search

- Seach for the left boundary.
- reference: https://leetcode.com/problems/find-k-closest-elements/discuss/106426/JavaC%2B%2BPython-Binary-Search-O(log(N-K)-%2B-K)
```
case 1: x - A[mid] < A[mid + k] - x, need to move window go left
-------x----A[mid]-----------------A[mid + k]----------

case 2: x - A[mid] <= A[mid + k] - x, need to move window go left again
Since A[mid + K] has larger diff than A[mid], the left boundary must be smaller than mid + 1
ie diff(A[mid], x) + diff(A[mid + k - 1], x) < diff(A[mid + 1], x) + diff(A[mid + k], x)
-------A[mid]----x-----------------A[mid + k]----------

case 3: x - A[mid] > A[mid + k] - x, need to move window go right
Since A[mid + k] has smaller diff than A[mid], the left boundary must be greater than mid
-------A[mid]------------------x---A[mid + k]----------

case 4: x - A[mid] > A[mid + k] - x, need to move window go right
-------A[mid]---------------------A[mid + k]----x------
```

```c++
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int lo = 0, hi = arr.size() - k;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (x - arr[mid] <= arr[mid + k] - x)
                hi = mid;
            else
                lo = mid + 1;
        }
        return {arr.begin() + lo, arr.begin() + lo + k};
    }
};
```