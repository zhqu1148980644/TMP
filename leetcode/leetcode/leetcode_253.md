---
title: Meeting Rooms II
date: 2021-01-04
---
#### Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

```
Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:

Input: [[7,10],[2,4]]
Output: 1
```

#### NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

#### Solutions

1. ##### discretization 

- see `problem 252` for details.

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> cnt;
        for (auto & e : intervals) {
            cnt[e[0]]++;
            cnt[e[1]]--;
        }

        int curc = 0, maxc = 0;
        for (auto [t, c] : cnt)
            maxc = max(maxc, curc += c);

        return maxc;
    }
};
```


2. ##### minheap

- Sort meetings based on their start time.
- Fore each meetings find former meeting with the longest ending time, check if this ending time is greater than the current meeting's start time to decide if there is need to open a new meeting room.
- Use a `minheap` to reduce the complexity of `O(n2)` to `log(n)` in each step, thus the final time complexity is `2nlong(n)`.

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> rooms;
        if (intervals.size())
            rooms.push(intervals[0][1]);
        for (int i = 1; i < intervals.size(); i++) {
            if (rooms.top() <= intervals[i][0]) {
                rooms.pop();
            }
            rooms.push(intervals[i][1]);
        }
        return rooms.size();
    }
};
```


# 300 Metting room V in lintcode.com

1. ##### dynamic programing with binary search O(nlog(n))

- The same as `problem 1235`
- reference: https://www.geeksforgeeks.org/weighted-job-scheduling-log-n-time/
- sorting rooms by their finish time, then search for the nearest nonoverlapping room visited before. The search can be conducted by a naive lear scanning strategy or by binary search.
- It seems like sorting rooms by `start` works too, however, it won't be possible to use binary search to speed up the seaching process.

```cpp
class Solution {
public:
    /**
     * @param meeting: the meetings
     * @param value: the value
     * @return: calculate the max value
     */
    int maxValue(vector<vector<int>> &meeting, vector<int> &value) {
        // write your code here
        for (int i = 0; i < meeting.size(); i++)
            meeting[i].push_back(value[i]);
        
        sort(meeting.begin(), meeting.end(), [&](auto & v1, auto & v2) {
            return v1[1] < v2[1]; 
        });

        vector<int> dp(meeting.size());
        int res = 0;
        for (int j = 0; j < meeting.size(); j++) {
            auto  & v = meeting[j];
            int st = v[0], ed = v[1], val = v[2];
            dp[j] = val;
            vector<int> target = {INT_MAX, st, INT_MAX};
            auto find = upper_bound(meeting.begin(), meeting.end(), target, [&](auto & v1, auto  & v2) {
                return v1[1] < v2[1];
            });
            if (find != meeting.begin()) {
                dp[j] += dp[prev(find) - meeting.begin()];
            }
            dp[j] = max(j ?  dp[j - 1] : 0, dp[j]);
            res = max(res, dp[j]);
        }
        return res;
    }
};
```