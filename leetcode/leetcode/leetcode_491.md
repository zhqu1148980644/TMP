---
title: Increasing Subsequences
date: 2021-01-04
---
Given an integer array, your task is to find all the different possible increasing subsequences of the given array, and the length of an increasing subsequence should be at least 2.

 

Example:

Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
 

Constraints:

The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.


#### Solutions

1. ##### dynamic programming

```cpp
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int n = nums.size();
        vector<vector<vector<int>>> dp(n);
        for (int j = 0; j < n; j++) {
            dp[j].push_back({nums[j]});
            for (int i = 0; i < j; i++) {
                if (nums[j] < nums[i]) continue;
                for (auto & prev : dp[i]) {
                    auto cur = prev; cur.push_back(nums[j]);
                    dp[j].push_back(move(cur));
                }
            }
        }

        set<vector<int>> res;
        for (auto & vv : dp)
            for (auto & v : vv)
                if (v.size() >= 2)
                    res.insert(move(v));
        
        return {move_iterator(res.begin()), move_iterator(res.end())};
    }
};
```


2. ##### backtrack

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path, previndex;
    void dfs(vector<int>& nums, int st) {
        if (path.size() >= 2) res.push_back(path);
        // choose or not
        for (int i = st; i < nums.size(); i++) {
            // in the current step can not choose the same number twice
            if (previndex[i] >= st || (path.size() && nums[i] < path.back()))
                continue;
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        if (!nums.size()) return {};
        previndex = vector<int>(nums.size());
        unordered_map<int, int> index;
        for (int i = 0; i < nums.size(); i++) {
            previndex[i] = index.count(nums[i]) ? index[nums[i]] : -1;
            index[nums[i]] = i;
        }
        dfs(nums, 0);
        return res;
    }
};
```