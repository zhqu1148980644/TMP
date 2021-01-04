---
title: Permutations II
date: 2021-01-04
---
### Given a collection of numbers that might contain duplicates, return all possible unique permutations.

```
Example:

Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
```

### Solutions

- The difference with problems 46: Contain duplicates.
- In general, use sort can remove duplicate permutation.
- In a for loop in backtrack, we can only use each unique number once.


1. #### backtracking with hashset

- use hashset to make each item been visited exactly once.
- here, we can not use swap operation as we did in problem 47 because swap will shuffle the sorted order. 

```cpp
class Solution {
private:
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> visited;

    void backtrack(vector<int> & nums) {
        if (path.size() == nums.size())  {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) continue;
            // if visited[i - 1], we can use nums[i] beacause nums[i - 1] is used in the lower level.
            // Only forbid multi-usage of a number in the same level to make sure no duplicate path are generated.
            if ((i && (nums[i] == nums[i - 1] && !visited[i - 1])))
                continue;
            path.push_back(nums[i]);
            visited[i] = true;
            backtrack(nums);
            visited[i] = false;
            path.pop_back();
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        visited = vector<bool>(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtrack(nums);
        return res;
    }
};
```

2. #### hash map to remove duplicate and reord usage

```cpp
class Solution {
public:
    vector<int> path;
    vector<vector<int>> res;
    unordered_map<int, int> m;
    void backtrack(int k, int n) {
        if (k == n) {
            res.push_back(path); return;
        }
        for (auto & it : m) {
            if (!it.second) continue;
            --it.second;
            path.push_back(it.first);
            backtrack(k + 1, n);
            path.pop_back();
            ++it.second;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        for (auto & n : nums) m[n]++;
        backtrack(0, nums.size());
        return res;
    }
};
```