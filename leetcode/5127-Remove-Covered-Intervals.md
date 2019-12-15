#### Given a list of intervals, remove all intervals that are covered by another interval in the list. Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.

After doing so, return the number of remaining intervals.

```
Example 1:

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
```
 

#### Constraints:

- 1 <= intervals.length <= 1000
- 0 <= intervals[i][0] < intervals[i][1] <= 10^5
- intervals[i] != intervals[j] for all i != j


#### Solutions

1. ##### two pointer

```c++
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>> & intervals) {
        if (intervals.size() <= 1) return intervals.size();
        sort(intervals.begin(), intervals.end());
        int i = 0, j = 1; count = intervals.size();
        while (j < intervals.size) {
            if (intervals[j][1] < intervals[i][1])
                count--;
            else
                i = j;
            j++;
        }
        return count;
    }
};
```