#### Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

#### Note: 
The solution set must not contain duplicate subsets.

```
Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
```

#### Solutions


1. ##### backtrack with sorting

```c++
class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void dfs(vector<int> & nums, int start) {
        res.push_back(path);
        for (int i = start; i < nums.size(); i++) {
            // only extend the first element
            if (i > start && nums[i] == nums[i - 1])
                continue;
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),  nums.end());
        dfs(nums, 0);
        return res;
    }
};
```

2. ##### divide and conquer with sorting

- Compared to `problem 78`, duplicate subsets needs to be removed in this problem.
- lastsize represents the number of subsets has been added to the resulting vector in the last step, and only these subsets can be used to generate non-duplicate subsets.
- reference: https://leetcode-cn.com/problems/subsets-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-19/

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        res.push_back(vector<int>());
        int size, start = 0;

        for (int i = 0; i < nums.size(); i++) {
            size = res.size();
            if (!i || nums[i] != nums[i - 1])
                start = 0;
            // start from the newly added subsets in the last level
            while (start != size) {
                auto subset = res[start];
                subset.push_back(nums[i]);
                res.push_back(subset);
                start++;
            }
            start = size;
        }
        return res;
    }
};
```

- Another iterative approach
- Handle duplicted number at one time.

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        res.push_back(vector<int>());
        int size, dupcount = 1;

        for (int i = 0; i < nums.size(); i++) {
            // count the number of duplicates minus 1
            if (i + 1 < nums.size() && nums[i + 1] == nums[i]) {
                dupcount++;
                continue;
            }

            size = res.size();
            while (size--) {
                // generate the first subset
                auto subset = res[size];
                // there are duplicates
                for (int j = 0; j < dupcount; j++) {
                    subset.push_back(nums[i]);
                    res.push_back(subset);
                }
            }
            dupcount = 1;
        }
        return res;
    }
};
```


3. ##### devide and conquer with hashmap

- reference: https://leetcode-cn.com/problems/subsets-ii/solution/tong-ji-pin-ci-zai-zu-he-fa-by-mai-mai-mai-mai-zi/
- Similar to the second iterative approach described above.

```python
class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        from collections import Counter
        c = Counter(nums)
        res = [[]]

        for num, count in c.items():
            res += [[num] * i + subset
                    for subset in res
                    for i in range(1, count + 1)]
        return res
```

4. ##### bit operations

- reference: https://leetcode-cn.com/problems/subsets-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-19/
- As we saw in the previous solution where duplicates of unique subsets containing duplicate numbers are always continous, thus, all subsets are guaranteed to be unique.
- In this method, we only choose bit subsets with contiguous duplicates.
- For a sorted nums `4444`. Only `1000` `1100` `1110` `1111` are selected.


```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int num = 1 << nums.size();
        bool valid;

        while (num--) {
            vector<int> com;
            valid = true;
            for (int i = 0; i < nums.size(); i++) {
                if (num & (1 << i)) {
                    // make sure they are contiguous if a duplicated number is set to 1.
                    if (i && nums[i] == nums[i - 1] && !(num & (1 << (i - 1)))) {
                        valid = false;
                        break;
                    } else
                        com.push_back(nums[i]);
                }
            }
            if (valid) res.push_back(move(com));
        }

        return res;
    }
};
```