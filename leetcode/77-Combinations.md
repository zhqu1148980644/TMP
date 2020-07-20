#### Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

```
Example:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

1. ##### recursive backtracking

```c++
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    int size;

    void dfs(int n, int start) {
        if (path.size() == size) {
            res.push_back(path);
            return;
        }
        // or i <= n   naive one
        // Stop if the number of remaining candidates is smaller than what we need
        // starting from the lower one is similar to use sorting for removing duplicate permutaions
        for (int i = start; i <= n - (size - path.size()) + 1; i++) {
            path.push_back(i);
            dfs(n, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        size = k;
        dfs(n, 1);
        return res;
    }
};
```

2. ##### iterative backtracking

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> com(k, 0);
        int pos = 0;
        while (pos >= 0) {
            com[pos]++;
            // or use com[pos] > n
            // pre-exit or prune
            if (com[pos] > n - (k - pos - 1))
                pos--;
            else if (pos == k - 1)
                res.push_back(com);
            else {
                com[pos + 1] = com[pos];
                pos++;
            }
        }
        return res;
    }
};
```

3. ##### Similar to solution 2 in problem 46

- The difference between this problem and problem 46 is that the comibation doesn't care about the ordering of items.
- `combination(n, k) = [i + subcom for i in range(n) for subcom in combination(n - 1, k - 1)]`
- We start from the largest n and `reduce n` in subproblem to remove combinations with different order.


```python
class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        if k == 0: return [[]]
        return [[i] + subcom
                # pre-exit(prune) and make sure the resulting array contain k items.
                for i in range(n, k - 1, -1)
                # for i in range(k , n + 1)
                for subcom in self.combine(i - 1, k - 1)]
                # self.combine(n, k - 1) will produce duplicate combination
```

Or convert to an iterative way.

```python
class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        coms = [[]]
        for start in range(k):
            coms = [[i] + c
                    for c in coms
                    for i in range(k - start, c[0] if c else n + 1)]
        return coms
# this could works too but with more overhead because many impossible path are created and abandoned in future steps by range call.
# for i in range(1, c[0] if c else n + 1))
```

4. ##### bit operation

- treat each combination as a number with the same number of 1 bit.
- This problem is the same as problem 5123.
- https://leetcode.com/problems/combinations/discuss/27088/C%2B%2B-solution-using-bit-opration this method doesn't generate combinations `lexicographically`.


5. ##### bit operation

- Can't understand.
- https://leetcode-cn.com/problems/combinations/solution/zu-he-by-leetcode/