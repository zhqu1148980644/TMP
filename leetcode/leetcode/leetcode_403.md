---
title: Frog Jump
date: 2021-01-04
---
A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

Note:

The number of stones is ≥ 2 and is < 1,100.
Each stone's position will be a non-negative integer < 231.
The first stone's position is always 0.
Example 1:

[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping 
1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.
Example 2:

[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as 
the gap between the 5th and 6th stone is too large.


#### Solutions


1. ##### dfs with memoization

```cpp
class Solution {
public:
    bool canCross(vector<int>& stones) {
        using pii = pair<int, int>;
        unordered_set<int> s(stones.begin(), stones.end());
        auto h = [](const pii & p) {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        };
        unordered_map<pii, bool, decltype(h)> m(10, h);
        function<bool(pii)> jump = [&](const pii & p) {
            if (m.count(p)) return m[p];
            int pos = p.first, psize = p.second;
            if (pos == stones.back()) return true;
            for (int step = psize - 1; step < psize + 2; step++)
                if (s.count(pos + step)
                    && step >= 1
                    && jump({pos + step, step}))
                    return true;
            return m[p] = false;
        };

        return jump({0, 0});
    }
};
```

2. ##### dynamic programming or bfs search ?

```cpp
class Solution {
public:
    bool canCross(vector<int>& stones) {
        unordered_map<int, unordered_set<int>> m;
        for (auto st : stones)
            m[st] = unordered_set<int>();
        m[0].insert(0);
        for (auto pos : stones) {
            if (!m.count(pos)) continue;
            for (auto psize : m[pos])
                for (int step = psize - 1; step < psize + 2; step++) {
                    if (step <= 0 || !m.count(pos + step)) continue;
                    m[pos + step].insert(step);
                }
        }

        return m[stones.back()].size() > 0;
    }
};
```

or

```cpp
class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        // must be n + 1, when step reaches n, dp[i][step + 1] will be outofbound, cuase undefined behavior
        vector<vector<bool>> dp(n, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int j = 1; j < n; j++)
            for (int i = j - 1; i >= 0; i--) {
                int step = stones[j] - stones[i];
                if (step >= n || i < stones[j] - stones[i] - 1) break;
                dp[j][step] = dp[i][step - 1] || dp[i][step] || dp[i][step + 1];
                if (dp[j][step] && j == n - 1) return true;
            }
        return false;
    }
};

```