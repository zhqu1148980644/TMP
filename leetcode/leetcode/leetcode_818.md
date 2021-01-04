---
title: Race Car
date: 2021-01-04
---
Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)

Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

When you get an instruction "A", your car does the following: position += speed, speed *= 2.

When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)

For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

Now for some target position, say the length of the shortest sequence of instructions to get there.

```
Example 1:
Input: 
target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0->1->3.

Example 2:
Input: 
target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0->1->3->7->7->6.
```

 

#### Note:

-    1 <= target <= 10000.


#### Solutions

1. ##### dynamic programming with recursion  O(nlog(n)) S(nlog(n))

- After moved `n` times, the total length is: `2^0 + 2^1 + .. 2^(n - 1) = 2^n - 1`.
- This solution is based on the intuition that the number of steps is minimum when we firstly moving staight forward to the place nearest to the target. There are two cases, suppose `2 ^ (n - 1) < target < 2 ^ n`:
    - Move `n` steps, then move backwards, ie: solve a minimal subproblem with `target = 2 ^ n - 1 - target`
    - Move `n - 1` steps, move n steps backwards, then move forward, ie: solve two minimal subproblems.
        -  Or move `backwards 1 step` after moved n - 1 steps, then try to move n steps forward.
- As there are `n` subproblems in total and we need to scan(backward) `log(n)` times when solving each subproblem, the time complexity is `nlog(n)`.

```cpp
class Solution {
public:
    vector<int> memo;
    int solve(int target) {
        if (memo[target])
            return memo[target];
        
        // the minimum step to move at or over target
        int fstep = ceil(log2(target + 1));
        int foward = (1 << fstep) - 1;
        if (target == foward)
            return memo[target] = fstep;
        // moved fsteps and reverse 1 time then backwards
        int minstep = fstep + 1 + solve(foward - target);
        // choose fstep - 1, move to the nearst point before target
        fstep--;
        foward = (1 << fstep) - 1;
        // bstep = 0 is valid too, just use two steps to slow down
        for (int bstep = 0; bstep < fstep; bstep++) {
            int backward = (1 << bstep) - 1;
            // reverse 2 times, backwards plus forwards
            minstep = min(minstep, fstep + 2 + bstep + solve(target - (foward - backward)));
        }

        return memo[target] = minstep;
    }

    int racecar(int target) {
        memo = vector<int>(target + 1, 0);
        return solve(target);
    }
};
```



2. ##### dynamic programming with iteration

```cpp
class Solution {
public:
    int racecar(int target) {
        vector<int> dp(target + 1, INT_MAX);
        dp[0] = 0; dp[1] = 1;
        for (int target = 2; target < dp.size(); target++) {
            int fstep = ceil(log2(target + 1));
            if (target == (1 << fstep) - 1) {
                dp[target] = fstep;
                continue;
            }
            int forward = (1 << fstep) - 1;
            if (forward - target < target)
                dp[target] = fstep + 1 + dp[forward - target];
            fstep--;
            forward = (1 << fstep) - 1;
            for (int b = 0; b < fstep; b++) {
                int backward = (1 << b) - 1;
                dp[target] = min(dp[target], fstep + 2 + b + dp[target - forward + backward]);
            }
        }

        return dp[target];
    }
};
```



3. ##### bfs search

- reference: https://leetcode.com/problems/race-car/discuss/124312/Straightforward-C%2B%2B-BFS-solution-with-Explanation
- Use pruning to avoid TLE. Ie. dont geting away from the target.

```cpp
class Solution {
public:
    struct hash {
        size_t operator()(const pair<int, int> & p) const {
            return p.first * (size_t)1e6 + p.second;
        }
    };
    int racecar(int target) {
        unordered_set<pair<int, int>, hash> seen;
        queue<pair<int, int>> q;
        q.push({0, 1}); seen.insert({0, 1});

        int step = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [pos, sp] = q.front(); q.pop();
                int newpos = pos + sp;
                if (newpos == target)
                    return step + 1;
                // key step, if the distance is larger than (target - 0), skip
                if (seen.insert({newpos, 2 * sp}).second && abs(newpos - target) < target)
                    q.push({newpos, 2 * sp});
                if (seen.insert({pos, sp > 0 ? -1 : 1}).second)
                    q.push({pos, sp > 0 ? -1 : 1});
            }
            step++;
        }
        return -1;
    }
};
```


4. ##### dijkstra


