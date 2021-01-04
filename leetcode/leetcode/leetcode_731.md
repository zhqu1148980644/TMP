---
title: My Calendar II
date: 2021-01-04
---
Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.

Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
Explanation: 
The first two events can be booked.  The third event can be double booked.
The fourth event (5, 15) can't be booked, because it would result in a triple booking.
The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
 

Note:

The number of calls to MyCalendar.book per test case will be at most 1000.
In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

#### Solutions


1. ##### straight forward O(n2)

- Use two arrays to store booked ranges with no overlap and ranges with exactly one overlap.

```cpp
class MyCalendarTwo {
public:
    vector<pair<int, int>> once, twice;
    MyCalendarTwo() {

    }
    
    bool book(int start, int end) {
        for (auto [st, ed] : twice)
            if (max(st, start) < min(ed, end))
                return false;
        

        for (auto [st, ed] : once) {
            int newst = max(st, start), newed = min(ed, end);
            if (newst < newed)
                twice.emplace_back(newst, newed);
        }
        once.emplace_back(start, end);
        return true;        
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
```


Or replace two arrays with two tree maps for speeding up the search process. `O(nlog(n))`.

```cpp

```

2. ##### discretization with tree map O(n2)

- This approach is similar to `problem 252 meeting rooms`'s.

```cpp
class MyCalendarTwo {
public:
    map<int, int> m;
    MyCalendarTwo() {

    }
    
    bool book(int start, int end) {
        m[start]++; m[end]--;
        int open = 0;
        for (auto & [t, cnt] : m) {
            if (t > end) break;
            open += cnt;
            if (open >= 3) {
                m[start]--; m[end]++;
                return false;
            }
        }
        return true;
    }
};
```


- Optimized version

```cpp


```

3. ##### segment tree wort(O(n2))

```cpp


```