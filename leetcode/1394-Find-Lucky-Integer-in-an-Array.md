Given an array of integers arr, a lucky integer is an integer which has a frequency in the array equal to its value.

Return a lucky integer in the array. If there are multiple lucky integers return the largest of them. If there is no lucky integer return -1.

 

```
Example 1:

Input: arr = [2,2,3,4]
Output: 2
Explanation: The only lucky number in the array is 2 because frequency[2] == 2.
Example 2:

Input: arr = [1,2,2,3,3,3]
Output: 3
Explanation: 1, 2 and 3 are all lucky numbers, return the largest of them.
Example 3:

Input: arr = [2,2,2,3,3]
Output: -1
Explanation: There are no lucky numbers in the array.
Example 4:

Input: arr = [5]
Output: -1
Example 5:

Input: arr = [7,7,7,7,7,7,7]
Output: 7
```
 

Constraints:

1 <= arr.length <= 500
1 <= arr[i] <= 500


#### Solutions

1. ##### hash map

```c++
class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int, int> m;
        for (auto n : arr)
            m[n]++;
        int max_num = -1;
        for (auto [n, c] : m)
            if (c == n && n > max_num)
                max_num = n;

        return max_num;
    }
};
```

Or search backwards

```c++
class Solution {
public:
    int findLucky(vector<int>& arr) {
        int m[501] = {0};
        for (auto n : arr)
            m[n]++;
        int res = -1;
        for (int n = 500; n >= 1; n--)
            if (m[n] == n && n > res)
                return n;
        return res;
    }
};
```