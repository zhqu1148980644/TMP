#### Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

 

```
Example 1:

Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.

Example 2:

Input: [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.

Example 3:

Input: [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
```

 

#### Note:

-    You may assume the interval's end point is always bigger than its start point.
-    Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.

#### Solutions

1. ##### dynamic programming sort by start O(n2)

- `dp[i]` represents the maximum number of non-overlapping intervals including `intervals[i]`

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<int> dp(intervals.size(), 0);
        
        int maxnum = 0;
        for (int j = 0; j < intervals.size(); j++) {
            dp[j] = 1;
            for (int i = 0; i < j; i++) {
                if (intervals[i][1] <= intervals[j][0])
                    dp[j] = max(dp[j], dp[i] + 1);
            }
            maxnum = max(maxnum, dp[j]);
        } 

        return intervals.size() - maxnum;
    }
};
```


2. ##### greedy strategy

- Sort by end.
- To make the number of non-overlapping intervals as large as possible, we need to select the interval with the minimum end as the next interval of growing intervals.
- Sorting the array by end can reduce the number of comparisons to satisify the second rule.

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (!intervals.size()) return 0;
        sort(intervals.begin(), intervals.end(), [](vector<int> & v1, vector<int> & v2) {
            return v1[1] <= v2[1];
        });

        int count = 1, prevend = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= prevend) {
                count++;
                prevend = intervals[i][1];
            }
        }

        return intervals.size() - count;
    }
};
```

- For demonstration, here is the version sorted by start.

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (!intervals.size()) return 0;
        sort(intervals.begin(), intervals.end());

        int count = 1, prevend = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][1] < prevend) {
                // this interval has a smaller end, repalce the last interval with this
                prevend = intervals[i][1];
            }
            else if (intervals[i][0] >= prevend) {
                count++;
                prevend = intervals[i][1];
            }
        }

        return intervals.size() - count;
    }
};
```