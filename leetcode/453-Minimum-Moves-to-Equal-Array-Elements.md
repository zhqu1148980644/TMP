Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]



#### Solutions

1. ##### math O(n)

- `1 2 3 4 3` except the largest number, all plus `1` is `2 3 4 4 4`, which is equivalent to decuce the largest number by `1`: `1 2 3 3 3`.

```c++
class Solution {
public:
    int minMoves(vector<int>& nums) {
        if (!nums.size()) return 0;
        long sum = 0, minv = nums[0];
        for (long n : nums) {
            sum += n;
            minv = min(minv, n);
        }
        return sum - minv * nums.size();
    }
};
```

2. ##### dynamic programming O(nlog(n))

- reference: https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/solution/c-dong-tai-gui-hua-by-gu-hai-qi/

```c++
class Solution {
public:
    int minMoves(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0, prevc = 0;
        for (int i = 0; i < nums.size() - 1; i++)
            res += prevc = nums[i + 1] - nums[i] + prevc;

        return res;
    }
};
```