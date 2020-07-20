We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

 

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 

Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8

##### Solutions

- The problem equals to find the region outside the merged interval of all intervals.

1. ##### discretization with tree map O(nlog(n)) n is the number of intervals

```c++
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/


class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        map<int, int> times;
        for (auto & e : schedule)
            for (auto & sc : e) {
                times[sc.start]++;
                times[sc.end]--;
            }

        int busy = 0, unbusyt = INT_MIN;
        vector<Interval> frees;
        for (auto [t, n] : times) {
            bool firstbusy = busy == 0;
            busy += n;
            if (!busy)
                unbusyt = t;
            else if (firstbusy && unbusyt != INT_MIN)
                frees.push_back(Interval(unbusyt, t));
        }

        return frees;
    }
};
```

2. ##### sort O(nlog(n))

```c++
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        vector<pair<int, int>> v;
        for (auto & ev : schedule)
            for (auto & sc : ev)
                v.emplace_back(sc.start, sc.end);
        
        sort(v.begin(), v.end());

        vector<pair<int, int>> merged;
        vector<Interval> res;
        int unbusyt = INT_MIN;
        for (auto [st, ed] : v) {
            if (merged.empty())
                merged.emplace_back(st, ed);
            else {
                auto & preved = merged.back().second;
                if (st > preved) {
                    if (unbusyt != INT_MIN)
                        res.emplace_back(preved, st);
                    merged.emplace_back(st, ed);
                }
                else
                    preved = max(preved, ed);
            }
            unbusyt = merged.back().second;
        }

        return res;
    }
};
```

or

```c++
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        vector<Interval *> vs;
        for (auto & ev : schedule)
            for (auto & sc : ev)
                vs.push_back(&sc);
            
        sort(vs.begin(), vs.end(), [](auto & ps1, auto & ps2) {
            return ps1->start == ps2->start ? ps1->end < ps2->end 
                    : ps1->start < ps2->start;
        });

        vector<Interval> res;
        int prevend = INT_MIN;
        for (auto ps : vs) {
            if (prevend != INT_MIN && ps->start > prevend)
                res.emplace_back(prevend, ps->start);
            prevend = max(ps->end, prevend);
        }

        return res;
    }
};
```

3. ##### priority queue O(nlog(n))

```c++
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        auto cmp = [](auto & ps1, auto & ps2) {
            return ps1->start == ps2->start ? ps1->end > ps2->end 
                    : ps1->start > ps2->start;
        };
        priority_queue<Interval *, vector<Interval *>, decltype(cmp)> pq(cmp);
        for (auto & ev : schedule)
            for (auto & sc : ev)
                pq.push(&sc);

        vector<Interval> res;
        int prevend = INT_MIN;
        while (!pq.empty()) {
            auto ps = pq.top(); pq.pop();
            if (prevend != INT_MIN && ps->start > prevend)
                res.emplace_back(prevend, ps->start);
            prevend = max(ps->end, prevend);
        }

        return res;
    }
};
```