### Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

### Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

```
Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]
```

### Solutions

The difference between problem 39 and this problem is:

- Each number in candidates may only be used once in the combination.
    - We need to expand the path start at current `index + 1`.
- The array contains duplicate numbers.
    - We need to bypass used numbers in for loop of backtrack.

1. #### The same as problem 40 except to remove duplicates.

- Because the array are sorted, we can easily bypass the same number in each step. ie. Ensure that in the for loop of backtrack, each number after the index will be used once.

```c++
class Solution {
private:
    vector<vector<int>> res;
    vector<int> path;

    void backtrack(vector<int> & candidates, int index, int target) {
        if (!target) {res.push_back(path); return; }
        int last = -1;
        for (int i = index; i < candidates.size(); i++) {
            // Change 2.
            if (candidates[i] > target || candidates[i] == last) continue;
            last = candidates[i];
            path.push_back(candidates[i]);
            // Change 1.
            backtrack(candidates, i + 1, target - candidates[i]);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, 0, target);
        return res;
    }
};
```