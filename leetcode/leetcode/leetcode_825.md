---
title: Friends Of Appropriate Ages
date: 2021-01-04
---
Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person. 

Person A will NOT friend request person B (B != A) if any of the following conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 3
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.

##### Solutions

1. ##### sliding window O(nlog(n))

- Be sure to taken acount of people with the same age.

```cpp
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int res = 0, same = 1;
        sort(ages.begin(), ages.end());
        for (int i = 0, j = 0; j < ages.size(); j++) {
            double lo = ages[j] * 0.5 + 7;
            same = j && ages[j] == ages[j - 1] ? same + 1 : 1;
            if (same > 1 && ages[j] > lo)
                res += same - 1;
            while (i < j && ages[i] <= lo) i++;
            res += max(0, j - i);
        }
        return res;
    }
};
```

or with bucket sort

```cpp
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        vector<int> nums(121);
        for (auto a : ages) nums[a]++;

        int res = 0, lage = 0;
        for (int age = 0; age < 121; age++) {
            if (!nums[age]) continue;
            double lo = age * 0.5 + 7;
            if (nums[age] > 1 && age > lo)
                res += nums[age] * (nums[age] - 1);
            while (lage < age && lage <= lo) lage++;
            for (int mid = lage; mid < age; mid++)
                res += nums[age] * nums[mid];
        }

        return res;
    }
};
```