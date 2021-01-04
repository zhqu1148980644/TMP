---
title: Boats to Save People
date: 2021-01-04
---
The i-th person has weight people[i], and each boat can carry a maximum weight of limit.

Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.  (It is guaranteed each person can be carried by a boat.)

 

Example 1:

Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
Example 2:

Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
Example 3:

Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
Note:

1 <= people.length <= 50000
1 <= people[i] <= limit <= 30000

#### Solutions

1. ##### binary search O(2nlog(n))

- Use binary search to find the minimum number of boat for carring all people, if the proposed number of boat is `mid`, and `numcarry(mid)` represents the number of people can be carried at most. If `numcarry(mid) < len(pepople)`, then the correct numboat must be `> numcarry(mid)`. ie: `lo = mid + 1`
- However, `numcarry(mid)` is not that easy to implement.
- The implementation of `numcarry(numboat)` leads to a greedy method.


```cpp
class Solution {
public:
    int numcarry(vector<int> & people, int numboat, int limit) {
        int n = people.size(), i = 0, j = n - 1, nump = 0;
        // greedy approach
        // the idea is to couple the smallest one to the maximum one, thus leaving as much as possible boats for people with heigh weight
        for (int b = 0; b < numboat; b++) {
            while (i < j && people[i] + people[j] > limit) j--;
            if (j > i++) {
                nump += 2; people[j] = -people[j]; j--;
            }
            else
                nump++;
            while (i < n && people[i] < 0) i++;
        }
        for (auto & w : people)
            if (w < 0) w = -w;

        return nump;
    }
    int numRescueBoats(vector<int>& people, int limit) {
        if (!people.size()) return 0;
        sort(people.begin(), people.end());
        int lo = 1, hi = people.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (numcarry(people, mid, limit) < people.size())
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
};
```

2. ##### greedy strategy O(nlog(n))

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int n = people.size(), i = 0, j = n - 1, boats = 0;
        while (i <= j) {
            boats++;
            if (people[i] + people[j] <= limit)
                i++;
            j--;
        }
        return boats;
    }
};
```