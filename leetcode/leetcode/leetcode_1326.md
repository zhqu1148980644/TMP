---
title: Minimum Number of Taps to Open to Water a Garden
date: 2021-01-04
---
#### There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the point n. (i.e The length of the garden is n).

There are n + 1 taps located at points [0, 1, ..., n] in the garden.

Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.

Return the minimum number of taps that should be open to water the whole garden, If the garden cannot be watered return -1.

 

```
Example 1:

Input: n = 5, ranges = [3,4,1,1,0,0]
Output: 1
Explanation: The tap at point 0 can cover the interval [-3,3]
The tap at point 1 can cover the interval [-3,5]
The tap at point 2 can cover the interval [1,3]
The tap at point 3 can cover the interval [2,4]
The tap at point 4 can cover the interval [4,4]
The tap at point 5 can cover the interval [5,5]
Opening Only the second tap will water the whole garden [0,5]

Example 2:

Input: n = 3, ranges = [0,0,0,0]
Output: -1
Explanation: Even if you activate all the four taps you cannot water the whole garden.

Example 3:

Input: n = 7, ranges = [1,2,1,0,2,1,0,1]
Output: 3

Example 4:

Input: n = 8, ranges = [4,0,0,0,0,0,0,0,4]
Output: 2

Example 5:

Input: n = 8, ranges = [4,0,0,0,4,0,0,0,4]
Output: 1
```

 

#### Constraints:

-    1 <= n <= 10^4
-    ranges.length == n + 1
-    0 <= ranges[i] <= 100


#### Solutions

1. ##### greedy strategy  O(n2) S(n)

- reference: https://leetcode-cn.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/solution/5318-by-ikaruga/
- `maxrange[i]` represents the rightmost(right closed) land could be covered by all taps that covered location `i`(the start point of land i).

```cpp
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> maxrange(n, 0);
        for (int i = 0; i < n + 1; i++) {
            int l = max(i - ranges[i], 0);
            int r = min(i + ranges[i], n);
            if (l == r)
                continue;
            for (int j = l; j < r; j++)
                maxrange[j] = max(maxrange[j], r);
        }

        int cur = 0;
        int count = 0;
        while (cur < n) {
            if (maxrange[cur] == 0)
                return -1;
            cur = maxrange[cur];
            count++;
        }
        return count;
    }
};
```


2. ##### greedy strategy similar to jump game II  O(n) S(n)

- See `problem 45 jump game II`
- Can be seen as a breath first approach.

```cpp
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> jumps(n + 1, 0);
        for (int i = 0; i < ranges.size(); i++) {
            int l = max(i - ranges[i], 0);
            int r = min(i + ranges[i], n);
            if (jumps[l] < r - l)
                jumps[l] = r - l;
        }
        // furthest represents the maximum point can be reched in the last jumping range
        int furthest = 0, end = 0, count = 0;
        for (int i = 0; i < n; i++) {
            furthest = max(i + jumps[i], furthest);
            if (furthest >= n) {
                count++;
                break;
            }
            // reach the end of the current jumping range, plus step by 1 representing the last jump
            if (i == end) {
                if (furthest <= end)
                    return -1;
                count++;
                end = furthest;
            }
        }
        return count;
    }
};
```