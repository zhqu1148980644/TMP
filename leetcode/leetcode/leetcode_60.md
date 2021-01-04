---
title: Permutation Sequence
date: 2021-01-04
---
#### The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

```
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note:

Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.
Example 1:

Input: n = 3, k = 3
Output: "213"
Example 2:

Input: n = 4, k = 9
Output: "2314"
```

#### Solutions


1. ##### dfs with pruning

- Note: we cannot use `swap` as we did in `problem 46` where the ordering of permutations is not required. for example:
    - `1 2 3` swapped `1` with `3` will be `3 2 1`, the ordering of `1` and `2` is changed due to the swap, the permutaion order will not be guaranteed when we choose the next number. ie. 2 will be choosed before 1.
    - Thus we use a `seen` hashset to record which number has been used in the current permutation.
- Inorder to speed up the backtracking process or eliminate unnecessary backtrackings, we can pre-calculate the number of permutations will be generated in each recursive call and skip to the right recursive call where the target permutations will be created.

```cpp
class Solution {
public:
    vector<bool> seen;
    vector<int> factoral;
    int cur = 0;

    void dfs(int n, int k, string & permute) {
        for (int i = 0; i < n; i++) {
            if (seen[i]) continue;
            int num = factoral[n - permute.size() - 1];
            // reaches the answer when cur + num == k
            if (cur + num < k) {
                cur += num;
                continue;
            }
            seen[i] = true;
            permute.push_back('1' + i);
            dfs(n, k, permute);
            // no need to pop_back() or seen, their is no tackback process
        }
    }
    string getPermutation(int n, int k) {
        seen = vector<bool>(n);
        factoral = vector<int>(n + 1, 1);
        for (int i = 1; i <= n; i++)
            factoral[i] = factoral[i - 1] * i;
        
        string permute;
        dfs(n, k, permute);
        return permute;
    }
};
```

2. ##### finding every digit

- Though the intrinsic idea are the same as the first solution, the first solution follows a backtracking strategy but with efficient pruning, while this solution trys to find every digit in the final permutation in a iterative way.
- use 0-based indexing to faciliate the calculation.
    - for example, when the group size is `2`.
    - 1-based. `5 / 2  == 4 / 2`. 5 and 4 are within the same group which is incorrect.
    - 0-based. `(5 - 1) / 2 != (4 - 1) / 2`.

```cpp
class Solution {
public:
    string getPermutation(int n, int k) {
        int factoral[n + 1] = {1};
        for (int i = 1; i <= n; i++)
            factoral[i] = factoral[i - 1] * i;

        vector<int> nums{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        string res;
    
        k = k - 1;
        for (int i = 0; i < n; i++) {
            int index = (k / factoral[n - i - 1]);
            res += nums[index];
            k = k - index * factoral[n - i - 1];
            // to ensure each number is used only once
            nums.erase(nums.begin() + index);
        }

        return res;
    }
};
```