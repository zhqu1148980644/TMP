### Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

### Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

```
Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]
Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
```

### Solutions

1. #### sort with backtracking O(max(nlog(n), n2)) S(n)

- Sort the araay to remove duplicates solutions and facilitate pruning procedure. eg:  `2 2 3, 2 3 2, 3 2 2`.
- Use backtrack to check each path.
- Pre-exit(prune) when the path is impossible to extend benifited from sorting.

```c++
class Solution {
private:
    vector<int> path;
    vector<vector<int>> res;

    void traceback(vector<int> & candidates, int index, int target) {
        if (!target) {
            res.push_back(path); return;
        }
        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] > target) break;
            path.push_back(candidates[i]);
            traceback(candidates, i, target - candidates[i]);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        traceback(candidates, 0, target);
        return res;
    }
};
```
