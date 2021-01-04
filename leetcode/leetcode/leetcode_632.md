---
title: Smallest Range Covering Elements from K Lists
date: 2021-01-04
---
You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

 

Example 1:

Input: [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
 

Note:

The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.

#### Solutions


1. ##### sliding window with priority queue O(nlog(k))

- Maintaing a window(defined by min and max val) which contains the smallest elements in each vectors, This windows is putted into a priority queue and update by forwarding the minimum elements one step.
- When ever the priority queue has the size of k, the window is a valid range that includes 1 elements for each vector. The required minimum range must be one of these windows while traversing all windows till the queue size is smaller than k.
    - This works because the shortest range must be made by (>=k)-most nearest neighbours, when updating the priority queue, we are traversing all (k>=)-nearest neighbours that contains at least one number in each vector.
    - This leads to another solution: Firtly sort arrays containing all numbers(with mark tells which array it belongs to), then use traditional sliding window strategy to find the minimum range.


```cpp
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        auto greater = [](auto & pit1, auto & pit2) {
            return *(pit1.first) > *(pit2.first);
        };
        using pit = pair<vector<int>::iterator, vector<int>::iterator>;
        priority_queue<vector<pit>, vector<pit>, decltype(greater)> pq(greater);
        
        int maxval = INT_MIN;
        for (auto & v : nums) {
            pq.emplace(v.begin(), v.end());
            maxval = max(v[0], maxval);
        }

        vector<int> res = {0, INT_MAX};
        while (true) {
            auto [begin, end] = pq.top(); pq.pop();
            int minval = *begin++;
            if (maxval - minval < res[1] - res[0])
                res = {minval, maxval};
            // here is the trick, maxval can be updated in O(1) time.
            if (begin != end)
                maxval = max(*begin, maxval);
            else
                break;
            pq.emplace(begin, end);
        }

        return res;
    }
};
```

2. ##### sliding window with sort O(nlog(n))

```cpp
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<pair<int, int>> vs;
        for (int i = 0; i < nums.size(); i++)
            for (auto n : nums[i])
                vs.emplace_back(n, i);

        sort(vs.begin(), vs.end());

        int i = 0, j = 0, c = 0;
        vector<int> m(nums.size()), res = {0, INT_MAX};
        while (j < vs.size())
            // start shrinking left boundary when the current window is valid(c == k)
            if (++m[vs[j++].second] == 1 && ++c == nums.size()) {
                // move i to the next position of the left boundary of the smallest valid window
                while (--m[vs[i++].second] != 0);
                c--;
                int l = vs[i - 1].first, r = vs[j - 1].first;
                if (r - l < res[1] - res[0])
                    res = {l, r};
            }

        return res;
    }
};
```