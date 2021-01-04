---
title: Super Ugly Number
date: 2021-01-04
---
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:

Input: n = 12, primes = [2,7,13,19]
Output: 32 
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
             super ugly numbers given primes = [2,7,13,19] of size 4.
Note:

1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.


#### Solutions

1. ##### merge sort O(nk)

- The same as problem 264


```cpp
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<long> dp(n + 1, 1);
        vector<int> pos(primes.size(), 1);
        for (int i = 2; i  <= n; i++) {
            long minval = INT_MAX;
            for (int i = 0; i < primes.size(); i++)
                minval = min(minval, dp[pos[i]] * primes[i]);
            for (int i = 0; i < primes.size(); i++)
                if (dp[pos[i]] * primes[i] == minval)
                    pos[i]++;
            dp[i] = minval;            
        }
        return dp[n];
    }
};
```

or use minheap O(nklog(n))

```cpp
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<int, vector<int>, greater<int>> pq;
        pq.push(1);
        int minval;

        for (int i = 1; i <= n; i++) {
            minval = pq.top();
            for (auto p : primes)
                pq.push(p * minval);
            while (pq.top() == minval)
                pq.pop();
        }

        return minval;
    }
};
```


Or use treemap `O(nlog(k))`
Though this method is much slower than the first one.

```cpp
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<long> dp(n + 1, 1);
        multimap<int, pair<int, int>> val_pos;
        for (auto p : primes)
            val_pos.insert({1, {1, p}});
        int minval = 1;
        auto [lo, hi] = val_pos.equal_range(minval);

        for (int i = 2; i  <= n; i++) {
            while (lo != val_pos.end() && lo->first == minval) {
                auto & [key, pos] = *lo;
                val_pos.emplace(pos.second * dp[pos.first], move(pos));
                lo = val_pos.erase(lo);
            }

            minval = val_pos.begin()->first;
            dp[i] = minval;
            auto it_range = val_pos.equal_range(minval);
            lo = it_range.first, hi = it_range.second;
            for (auto it = it_range.first; it != it_range.second; it++)
                it->second.first++;
            
        }
        return dp[n];
    }
};
```