Given an integer n. Each number from 1 to n is grouped according to the sum of its digits. 

Return how many groups have the largest size.

 

```
Example 1:

Input: n = 13
Output: 4
Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
[1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9]. There are 4 groups with largest size.
Example 2:

Input: n = 2
Output: 2
Explanation: There are 2 groups [1], [2] of size 1.
Example 3:

Input: n = 15
Output: 6
Example 4:

Input: n = 24
Output: 5
```
 

Constraints:

1 <= n <= 10^4


#### Solutions

1. ##### hash map


```c++
class Solution {
public:
    inline int sum(int n) {
        int s = 0;
        while (n) {
            s += n % 10;
            n /= 10;
        }
        return s;
    }
    int countLargestGroup(int n) {
        unordered_map<int, vector<int>> m;
        for (int i = 1; i <= n; i++)
            m[sum(i)].push_back(i);

        int maxsize = 1;
        for (auto [s, v] : m)
            maxsize = max((int)v.size(), maxsize);

        int res = 0;
        for (auto [s, v] : m)
            res += v.size() == maxsize;

        return res;
    }
};
```

Or update the maxsize when iterating.

```c++
class Solution {
public:
    inline int sum(int n) {
        int s = 0;
        while (n) {
            s += n % 10;
            n /= 10;
        }
        return s;
    }
    int countLargestGroup(int n) {
        unordered_map<int, vector<int>> m;
        int maxsize = 1, res = 0;

        for (int i = 1; i <= n; i++) {
            int s = sum(i);
            m[s].push_back(i);
            maxsize = max(maxsize, (int)m[s].size());
        }
        for (auto [s, v] : m)
            res += v.size() == maxsize;

        return res;
    }
};
```