---
title: Sort Items by Groups Respecting Dependencies
date: 2021-01-04
---
There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.

#### Return a sorted list of the items such that:

-    The items that belong to the same group are next to each other in the sorted list.
-    There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).

Return any solution if there is more than one solution and return an empty list if there is no solution.

 

```
Example 1:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]

Example 2:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.
```

 

#### Constraints:

-    1 <= m <= n <= 3*10^4
-    group.length == beforeItems.length == n
-    -1 <= group[i] <= m-1
-    0 <= beforeItems[i].length <= n-1
-    0 <= beforeItems[i][j] <= n-1
-    i != beforeItems[i][j]
-    beforeItems[i] does not contain duplicates elements.


#### Solutions

1. ##### topological sort

- There exists two types of dependency, group vs group and items in one greoup vs items in the same group.
- Build a graph representing the dependency relationship between groups.
- Within each group, build a dependency graph for every item of that group.

```cpp
class Solution {
public:
    bool toposort(vector<int> & sorted, vector<int> & indegree, 
                  vector<vector<int>> & g, vector<int> & nodes) {

        queue<int> q;
        for (auto & i : nodes)
            if (indegree[i] == 0)
                q.push(i);
        int inc = 0;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            sorted.push_back(cur); inc++;
            for (auto & outnode : g[cur]) {
                if (--indegree[outnode] == 0)
                    q.push(outnode);
            }
        }

        return inc == nodes.size();
    }
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        for (auto & g : group)
            if (g == -1)
                g = m++;
        vector<vector<int>> groups(m);
        unordered_map<int, int> i2g;
        for (int i = 0; i < n; i++) {
            i2g[i] = group[i];
            groups[group[i]].push_back(i);    
        }

        vector<vector<int>> itemg(n), groupg(m);
        vector<int> indgreeitem(n), indgreeg(m);
        // build graph. ie: indegree and outnodes of each node/group
        for (int i = 0; i < n; i++) {
            if (!beforeItems[i].size())
                continue;
            int g = group[i];
            unordered_set<int> depitems(beforeItems[i].begin(), beforeItems[i].end());
            unordered_set<int> depgroups;
            depitems.erase(i);
            for (auto & item : depitems) {
                // graphs within each group
                if (i2g[item] == g) {
                    itemg[item].push_back(i);
                    indgreeitem[i]++;
                }
                else
                    // graph of groups
                    depgroups.insert(i2g[item]);
            }
            // graph of groups
            indgreeg[g] += depgroups.size();
            for (auto & grp : depgroups)
                groupg[grp].push_back(g);
        }

        vector<int> sortedg;
        vector<int> gnodes(m);
        for (int i = 0; i < m; i++)
            gnodes[i] = i;
        // topological sort of groups, exit if it's not a dag
        if (!toposort(sortedg, indgreeg, groupg, gnodes))
            return {};

        vector<int> res;
        // topological sort of items within the same group, exit if it's not a dag
        for (auto & g : sortedg) {
            if (!toposort(res, indgreeitem, itemg, groups[g]))
                return {};
        }
        
        return res;
    }
};
```

- We can also use radix sort for collecting items.