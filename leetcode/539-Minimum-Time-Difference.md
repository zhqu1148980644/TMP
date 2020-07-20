Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum minutes difference between any two time points in the list.
Example 1:
Input: ["23:59","00:00"]
Output: 1
Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.

#### Solutions

1. ##### sort

```c++
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> times(timePoints.size());
        int w = 0, h, m;
        for (auto & ts : timePoints) {
            sscanf(ts.c_str(), "%d:%d", &h, &m);
            times[w++] = h * 60 + m;
        }
        sort(times.begin(), times.end());
        // compare the last time with the first time
        times.push_back(24 * 60 + times[0]);
        int res = INT_MAX;
        for (int i = 0; i < times.size() - 1; i++)
            res = min(res, times[i + 1] - times[i]);
        
        return res;
    }
};
```