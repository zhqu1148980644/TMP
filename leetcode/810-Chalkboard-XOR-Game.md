We are given non-negative integers nums[i] which are written on a chalkboard.  Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first.  If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become 0, then that player loses.  (Also, we'll say the bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is 0.)

Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to 0, then that player wins.

Return True if and only if Alice wins the game, assuming both players play optimally.

Example:
Input: nums = [1, 1, 2]
Output: false
Explanation: 
Alice has two choices: erase 1 or erase 2. 
If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
If Alice erases 2 first, now nums becomes [1, 1]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.

Notes:

1 <= N <= 1000. 
0 <= nums[i] <= 2^16.

#### Solutions

1. ##### math

- From the official answer.
- if `final xor != 0`, then the first player will win only if `num.size() is even`
    - For a player start with even numbers, all it's turn will has even numbers. If this player will not lose in all steps, then the other player will erase the last element and the first pair win.
    - Suppose the remaining even number of elements are `n1...ni` and the current xor is `S`(must not be 0, otherwise won't come into this step). The current player will lose only if `S ^ n1 == 0 and S ^ n2 == 0 and ... S ^ ni == 0`. ie: lose for all choices.
        - As `0 ^ 0 ^ 0 ... == 0`, we have `S ^ n1 ^ S ^ n2 ^ S ^ n3 ... == 0`
        - `S ^ S ^ ... S ^ n1 ^ n2 ^ ... ni`
        - `(even number of S xor) ^ (S)`
        - `0 ^ nonzero != 0`. The hypothesis fails.

```c++
class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int res = 0;
        for (auto n : nums)
            res ^= n;
        return res == 0 || nums.size() % 2 == 0;
    }
};
```