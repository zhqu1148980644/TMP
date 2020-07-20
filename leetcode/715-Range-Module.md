
A Range Module is a module that tracks ranges of numbers. Your task is to design and implement the following interfaces in an efficient manner.

addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
queryRange(int left, int right) Returns true if and only if every real number in the interval [left, right) is currently being tracked.
removeRange(int left, int right) Stops tracking every real number currently being tracked in the interval [left, right).
Example 1:
addRange(10, 20): null
removeRange(14, 16): null
queryRange(10, 14): true (Every number in [10, 14) is being tracked)
queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked, despite the remove operation)
Note:

A half open interval [left, right) denotes all real numbers left <= x < right.
0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
The total number of calls to addRange in a single test case is at most 1000.
The total number of calls to queryRange in a single test case is at most 5000.
The total number of calls to removeRange in a single test case is at most 1000.

#### Solutions

1. ##### tree map

- Adding `range[l, r)`, check if there are any ranges overlapped with `two ends`, extend l/r to the smaller/larger one. Then removing existing ranges between them.
- Removing `range[l, r)`, check if there are any ranges overlapped with `two ends, retain existing subranges that are outside `[l, r)`. Then remove existing ranges between them.
- Be careful when updating tree structures(insert and delte) as later process may be dependent on the original structure.
- During the whole preocess, keeping all ranges within the map unoverlapped.


```
# Adding range
   ----- -- --  ------   ->      --------------------------
     -------------

   ----       ---                ---------  ---
    --------

   ---------                     ---------
     -----

# Removing range
  ------  --  --    ------ ->
    -------------------          --              ---
```


```c++
class RangeModule {
public:
    map<int, int> s;
    RangeModule() {}
    void addRange(int left, int right) {
        // lo could be upper bound
        auto lo = s.lower_bound(left);
        auto hi = s.upper_bound(right);
        // for case when the added range is a subrange of existing range. This step can also be skipped.
        if (lo != s.begin() && prev(lo)->second >= right) return;
        // choose the smaller one as the left boundary
        if (lo != s.begin() && prev(lo)->second >= left) {
            lo = prev(lo); left = lo->first;
        }
        // choose the larger one as the right boundary
        if (hi != s.begin() && prev(hi)->second > right) {
            right = prev(hi)->second;
        }
        // clear every ranges overlapping the current range
        s.erase(lo, hi);
        // insert the altered range
        s.emplace(left, right);
    }
    
    bool queryRange(int left, int right) {
        auto lo = s.upper_bound(left);
        // return true only if both two ends reside in the same valid range with right <= this range's right boundary.
        return lo != s.begin() && prev(lo)->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto lo = s.lower_bound(left);
        auto hi = s.upper_bound(right);
        pair<int, int> rpart {INT_MAX, INT_MAX};
        // split the boundary overlapped with right, can not immediately insert it(would change structure)
        if (hi != s.begin() && prev(hi)->second > right)
            rpart =  {right, prev(hi)->second};
        // split the boundary overlapped with left, it's over to change `second`, as it must be visited in the former step if it overlaps with right.
        if (lo != s.begin() && prev(lo)->second > left)
            prev(lo)->second = left;
        s.erase(lo, hi);
        // insert the subrange(from the range overlapped with right).
        if (rpart.first != INT_MAX)
            s.emplace(rpart);
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
```