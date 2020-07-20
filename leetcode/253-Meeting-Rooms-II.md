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

```c++
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> delta;
        for (auto & v : intervals) {
            delta[v[0]]++;
            delta[v[1]]--;
        }
        int max_meeting = 0;
        int num_meeting = 0;
        for (auto & it : delta) {
            num_meeting += it.second;
            max_meeting = max(max_meeting, num_meeting);
        }
        return max_meeting;
    }
};
```


2. ##### minheap

- Sort meetings based on their start time.
- Fore each meetings find former meeting with the longest ending time, check if this ending time is greater than the current meeting's start time to decide if there is need to open a new meeting room.
- Use a `minheap` to reduce the complexity of `O(n2)` to `log(n)` in each step, thus the final time complexity is `2nlong(n)`.

```c++
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