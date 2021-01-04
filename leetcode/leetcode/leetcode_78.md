---
title: Subsets
date: 2021-01-04
---
#### Given a set of distinct integers, nums, return all possible subsets (the power set).

#### Note: 
The solution set must not contain duplicate subsets.

```
Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

#### Solutions

1. ##### backtracking

- Similar to finding all combinations.

```cpp
class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void dfs(vector<int> & nums, int start) {
        res.push_back(path);
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};
```

python version

```python
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        def backtrack(cans, start):
            res.append(cans)
            for i in range(start, len(nums)):
                backtrack([nums[i]] + cans, i + 1)

        res = []
        backtrack([], 0)

        return res
```

2. #### bit operations


- Treat a subset of given numers as bit combination where `1` bit represents the occurrence of a certain number. ie  `132` is a subset of `1232` that can be represented as `1110` or `1011`.

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;

        int num = (1 << nums.size());
        while (num--) {
            vector<int> com;
            for (int i =0 ; i < nums.size(); i++) {
                if (num & (1 << i))
                    com.push_back(nums[i]);
            }
            res.push_back(com);
        }
        return res;
    }
};
```

3. #### divide and conquer

- bottom-up

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back(vector<int>());

        for (int i = 0; i < nums.size(); i++) {
            int size = res.size();
            while (size--) {
                auto subet = res[size];
                subset.push_back(nums[i]);
                res.push_back(subset);
            }
        }

        return res;
    }
};
```

```python
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = [[]]
        for num in nums:
            res += [[num] + subset for subset in res]

        return res
```

- top-down

```python
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        if not nums:
            return [[]]
        subset = self.subsets(nums[1:])
        return subset + [[nums[0]] + subs for subs in subset]
```