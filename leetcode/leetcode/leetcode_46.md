---
title: Permutations
date: 2021-01-04
---
### Given a collection of distinct integers, return all possible permutations.

```
Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

### Solutions

- In this problem, there is no need to firstly sort the array(Sorting is utilized for removing duplicate permutaion and pruning.). The only restriction is using each number exactly once in each permutation.
- Because there is no duplicate number, no need to remove duplicate permutations.

1. #### backtrack


- use swap to make sure each item is used only once.
- Caution: the result permutations are not listed in lexicographical order as the original list is not sorted and swap could shuffle the list.

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void permute(vector<int> & nums, int index) {
        if (index == nums.size()) {
            res.push_back(vector<int>(nums)); return;
        }
        for (int i = index; i < nums.size(); i++) {
            swap(nums[i], nums[index]);
            permute(nums, index + 1);
            swap(nums[i], nums[index]);
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        permute(nums, 0);
        return res;
    }
};
```

- use a hashset to record the usage of each item.

```cpp
class Solution {
private:
    vector<vector<int>> res;
    vector<bool> seen;
    vector<int> path;

    void Permute(vector<int> & nums) {
        if (path.size() == nums.size()) {
            res.push_back(path); return;
        }
        for (int i = 0; i < nums.size(); i++){
            if (seen[i]) continue;
            seen[i] = true;
            path.push_back(nums[i]);
            Permute(nums);
            path.pop_back();
            seen[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        seen = vector<bool>(nums.size(), false);
        Permute(nums);
        return res;
    }
};
```

2. #### recursion version

In anthor perspective, this problem can be solved like:

```python
solu[n] = [first + path for path in solu[n - 1] for first in nums]
```

```python
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        return [[n] + path
                for i, n  in enumerate(nums)
                for path in self.permute(nums[:i] + nums[i + 1:]) 
               ] or [[]]
```

Or insert the first element into different positions.

```python
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        return [path[:i] + [nums[0]] + path[i:]
                for i in range(len(nums))
                for path in self.permute(nums[1:])
               ] or [[]]
```
