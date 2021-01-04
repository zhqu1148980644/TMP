---
title: Meeting Rooms
date: 2021-01-04
---
#### Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

```
Example 1:

Input: [[0,30],[5,10],[15,20]]
Output: false

Example 2:

Input: [[7,10],[2,4]]
Output: true
```

#### NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

#### Solutions

1. ##### intervals overlapping check with sort

```cpp
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        for (int i = 1; i < intervals.size(); i++)
            if (intervals[i][0] < intervals[i - 1][1])
                return false;
        return true;
    }
};
```


2. ##### another method

- reference: https://leetcode-cn.com/problems/meeting-rooms/solution/c-liang-chong-jie-fa-by-da-fei-kai/

- `num_meeting` represents the number of meeting being hold at each time point.
- return false if there are two or more meetings at the same time.

```cpp
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        map<int, int> delta;
        for (auto & v : intervals) {
            delta[v[0]]++;
            delta[v[1]]--;
        }
        int num_meeting = 0;
        for (auto & it : delta) {
            num_meeting += it.second;
            if (num_meeting > 1)
                return false;
        }
        return true;
    }
};
```