In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice, then repeatedly perform the following steps:

Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?

 

Example 1:

Input: [1,2,1]
Output: 3
Explanation: We can collect [1,2,1].
Example 2:

Input: [0,1,2,2]
Output: 3
Explanation: We can collect [1,2,2].
If we started at the first tree, we would only collect [0, 1].
Example 3:

Input: [1,2,3,2,2]
Output: 4
Explanation: We can collect [2,3,2,2].
If we started at the first tree, we would only collect [1, 2].
Example 4:

Input: [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can collect [1,2,1,1,2].
If we started at the first tree or the eighth tree, we would only collect 4 fruits.
 

Note:

1 <= tree.length <= 40000
0 <= tree[i] < tree.length

#### Solutions

1. ##### sliding window

- Maintaining a window contains at most two fruit types of fruits.

```c++
class Solution {
public:
    int totalFruit(vector<int>& tree) {
        unordered_map<int, int> count;
        int i = 0, j = 0, n = tree.size(), cnt = 0, res = 0;
        while (j < n) {
            if (++count[tree[j++]] == 1 && ++cnt > 2) {
                res = max(res, j - 1 - i);
                while (--count[tree[i++]] != 0);
                cnt--;
            }
        }
        res = max(res, j - i);
        return res;
    }
};
```

- or without hash map
- reference: https://leetcode-cn.com/problems/fruit-into-baskets/solution/shui-guo-cheng-lan-by-leetcode/402047
- l is the first index of the firtst number in the current valid window.
- m is the first index of the second number in the current valid window
- r is the first index outside of the current valid window.
- After each iteration, `m` must be set as `m + 1`, for example:
    - [2,1,2,3,3,4], the current window is `[2:3)`, the number `1` can be find out in the next window search only if `m` is set to `m + 1`.

```c++
class Solution {
public:
    int totalFruit(vector<int>& tree) {
        int n = tree.size(), l = 0, m = 0, r = 0, res = 0;
        while (r < n) {
            while (m < n && tree[m] == tree[l]) m++;
            r = m;
            while (r < n && (tree[r] == tree[m] || tree[r] == tree[l]))
                r++;
            res = max(res, r - l);
            // m mus be set to m + 1, for case like: `2122223`
            l = m; m = m + 1;
        }

        return res;
    }
};
```