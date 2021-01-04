---
title: Combination Sum III
date: 2021-01-04
---
### Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

### Note:

All numbers will be positive integers.
The solution set must not contain duplicate combinations.

```
Example 1:

Input: k = 3, n = 7
Output: [[1,2,4]]
Example 2:

Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]
```

### Solutions

1. #### backtracking

```cpp
class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void backtrack(int index, int target, int & k) {
        if (!target) {
            if (path.size() == k) res.push_back(path);
            return;
        }
        if (path.size() == k) return;
        for (int i = index; i < 10; i++) {
            if (i > target) break;
            path.push_back(i);
            backtrack(i + 1, target - i, k);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtrack(1, n, k);
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    vector<int> path;
    vector<vector<int>> res;
    void solve(int st, int k, int sum) {
        if (k == 0 || sum == 0) {
            if (k == 0 && sum == 0)
                res.push_back(path);
        }
        else {
            for (int i = st; i <= 9; i++) {
                path.push_back(i);
                solve(i + 1, k - 1, sum - i);
                path.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        solve(1, k, n);
        return res;
    }
};
```