---
title: Count Good Meals
date: 2021-01-04
---
A good meal is a meal that contains exactly two different food items with a sum of deliciousness equal to a power of two.

You can pick any two different foods to make a good meal.

Given an array of integers deliciousness where deliciousness[i] is the deliciousness of the i​​​​​​th​​​​​​​​ item of food, return the number of different good meals you can make from this list modulo 109 + 7.

Note that items with different indices are considered different even if they have the same deliciousness value.

 

Example 1:

Input: deliciousness = [1,3,5,7,9]
Output: 4
Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
Example 2:

Input: deliciousness = [1,1,1,3,3,3,7]
Output: 15
Explanation: The good meals are (1,1) with 3 ways, (1,3) with 9 ways, and (1,7) with 3 ways.
 

Constraints:

1 <= deliciousness.length <= 105
0 <= deliciousness[i] <= 220

#### Solutions

1. ##### hash map O(21n)

- The most intuitive way(O(n2)) will gets TLE, here we loop over all possible `Power of 2`, as the number of possibilities(21) are far less then `n`.


```cpp
class Solution {
public:
    int countPairs(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<size_t> ps;
        for (int i = 0; i <= 21; i++)
            ps.push_back(size_t{1} << i);
        
        size_t res = 0;
        unordered_map<size_t, int> m;
        for (size_t n : nums) {
            for (auto s : ps) {
                if (s < n) continue;
                if (m.count(s - n)) {
                    res += m[s - n];
                    res %= 1000000007;
                }
            }
            m[n]++;
        }
        
        return res;
    }
};

```