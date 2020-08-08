There are some chips, and the i-th chip is at position chips[i].

You can perform any of the two following types of moves any number of times (possibly zero) on any chip:

Move the i-th chip by 2 units to the left or to the right with a cost of 0.
Move the i-th chip by 1 unit to the left or to the right with a cost of 1.
There can be two or more chips at the same position initially.

Return the minimum cost needed to move all the chips to the same position (any position).

 

Example 1:

Input: chips = [1,2,3]
Output: 1
Explanation: Second chip will be moved to positon 3 with cost 1. First chip will be moved to position 3 with cost 0. Total cost is 1.
Example 2:

Input: chips = [2,2,2,3,3]
Output: 2
Explanation: Both fourth and fifth chip will be moved to position two with cost 1. Total minimum cost will be 2.
 

Constraints:

1 <= chips.length <= 100
1 <= chips[i] <= 10^9

#### Solutions

1. ##### straight forward

- In summary, the problem requires we change all numbers into the same number with `+/-(even number)` cost `1` and `+/-(odd number)` cost `0`. Under these rules, return the minimum number of costs.
- For odd numbers, they all can be changed the same odd numbers with `zero cost`, the same with even numbers changes to the same even number.
- Finally, if there are both even and odd numbers in the original array, there would be `2` unique numbers(one odd and one even) left with count of ``cnt1` and `cnt2`, to make them the same, move the one with less count to the other by plusing a odd number(cost cnt * 1).

```c++
class Solution {
public:
    int minCostToMoveChips(vector<int>& chips) {
        int odd = 0, even = 0;
        for (auto n : chips)
            if (n % 2) odd++;
            else even++;

        return min(odd, even);
    }
};
```