---
title: Group the People Given the Group Size They Belong To
date: 2021-01-04
---
There are n people whose IDs go from 0 to n - 1 and each person belongs exactly to one group. Given the array groupSizes of length n telling the group size each person belongs to, return the groups there are and the people's IDs each group includes.

You can return any solution in any order and the same applies for IDs. Also, it is guaranteed that there exists at least one solution. 

 

Example 1:

Input: groupSizes = [3,3,3,3,3,1,3]
Output: [[5],[0,1,2],[3,4,6]]
Explanation: 
Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].
Example 2:

Input: groupSizes = [2,1,3,3,3,2]
Output: [[1],[0,5],[2,3,4]]
 

Constraints:

groupSizes.length == n
1 <= n <= 500
1 <= groupSizes[i] <= n

#### Solutions

1. ##### sort

```cpp
class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<int> indexes(groupSizes.size());
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&](int i1, int i2) {
            return groupSizes[i1] < groupSizes[i2];
        });
        vector<vector<int>> res;
        int i = 0;
        while (i < groupSizes.size()) {
            int num = groupSizes[indexes[i]];
            res.emplace_back(indexes.begin() + i, indexes.begin() + i + num);
            i += num;
        }

        return res;
    }
};
```

2. ##### hashmap

```cpp
class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int>> groups(501), res;
        for (int i = 0; i < groupSizes.size(); i++) {
            int gs = groupSizes[i];
            groups[gs].push_back(i);
            if (groups[gs].size() % gs == 0)
                res.emplace_back(groups[gs].rbegin(), groups[gs].rbegin() + gs);
        }

        return res;
    }
};
```