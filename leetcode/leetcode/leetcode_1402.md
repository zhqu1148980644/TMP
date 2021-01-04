---
title: Reducing Dishes
date: 2021-01-04
---
A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.

Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level  i.e.  time[i]*satisfaction[i]

Return the maximum sum of Like-time coefficient that the chef can obtain after dishes preparation.

Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.

 

```
Example 1:

Input: satisfaction = [-1,-8,0,5,-9]
Output: 14
Explanation: After Removing the second and last dish, the maximum total Like-time coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14). Each dish is prepared in one unit of time.
Example 2:

Input: satisfaction = [4,3,2]
Output: 20
Explanation: Dishes can be prepared in any order, (2*1 + 3*2 + 4*3 = 20)
Example 3:

Input: satisfaction = [-1,-4,-5]
Output: 0
Explanation: People don't like the dishes. No dish is prepared.
Example 4:

Input: satisfaction = [-2,5,-1,0,3,-3]
Output: 35
```
 

Constraints:

n == satisfaction.length
1 <= n <= 500
-10^3 <= satisfaction[i] <= 10^3

#### Solutions

1. ##### greedy approach

- reference: https://leetcode-cn.com/problems/reducing-dishes/solution/reducing-dishes-by-ikaruga/
- Obviuosly, dishes with higher satisfaction score should be aranged more delayed.
- Thus the first step should be sorting the satisfaction array in ascending order and the next step is to find a starting point and discard dishes before this point. However this strategy has `O(n2)` time complexity.
- Another method is to traversing dishes reversely, and iteratively add dishes as long as the prefix sum is greater than 0. By using prefix sum we can calculate `n1 * 1 + n2 * 2 + n3 * 3 ...` in `O(1)` time based on `n2 * 1 + n3 * 2 ....`

```cpp
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int n = satisfaction.size();
        sort(satisfaction.rbegin(), satisfaction.rend());
        int res = 0, sum = 0;
        for (auto n : satisfaction) {
            sum += n;
            if (sum < 0) break;
            // + prefix sum equals to add another copy for all elements before.
            res += sum;
        }

        return res;
    }
};
```