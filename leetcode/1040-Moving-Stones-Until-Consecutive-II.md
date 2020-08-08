On an infinite number line, the position of the i-th stone is given by stones[i].  Call a stone an endpoint stone if it has the smallest or largest position.

Each turn, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.

In particular, if the stones are at say, stones = [1,2,5], you cannot move the endpoint stone at position 5, since moving it to any position (such as 0, or 3) will still keep that stone as an endpoint stone.

The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.

When the game ends, what is the minimum and maximum number of moves that you could have made?  Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]

 

Example 1:

Input: [7,4,9]
Output: [1,2]
Explanation: 
We can move 4 -> 8 for one move to finish the game.
Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
Example 2:

Input: [6,5,4,3,10]
Output: [2,3]
We can move 3 -> 8 then 10 -> 7 to finish the game.
Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.
Example 3:

Input: [100,101,104,102,103]
Output: [0,0]
 

Note:

3 <= stones.length <= 10^4
1 <= stones[i] <= 10^9
stones[i] have distinct values.

#### Solutions

- It's strongly recommended to firstly check problem 1033.

1. ##### sliding window/math

- referene: https://leetcode-cn.com/problems/moving-stones-until-consecutive-ii/solution/chua-dong-chuang-kou-by-xiaoneng-2/
- Compared to the previous problem, the difference is that the moved endpoint stone should not longer be a endpoint after it's been moved.
- For maximum number. 
    - Use the left endpoint as example, after we move it at the next empty position of the second stone, then we can repeat these kinds of process(move the front at the next element of the continuous array), iteratively expanding the continuous prefix and shifting this prefix till all elements are positioned contiguously. Obviuosly the total steps we need to move equals to the number of empty positions within `stones[1:last]`
    - The same process can be starting from the last element too.
    - Thus `maxmove` equals to the maximum one of these two cases.

- For minimum move, we use sliding window, i.e. check all windows(defined by the first/last element of the window) with `at most` positions(some are occupied by existed stones) and  the number of empty spaces witin are the minimum steps to fill the current window.
    - However, there are special cases like: `[3,4,5,6,10]`, these kind of cases need two steps: move 3 to 8 then 10 to 7.
    - We can prove that as long as the lenght of the continous array is less than `n - 1`, we can always ends with `n - cur` steps(cur is the number of stones in the current valid window).

```c++
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        sort(stones.begin(), stones.end());
        int n = stones.size(), minmove = n;
        
        int maxmove = max(
            stones[n - 1] - stones[1] - n + 2, 
            stones[n - 2] - stones[0] - n + 2
        );

        if (stones[n - 2] - stones[0] + 1 == n - 1
        ||  stones[n - 1] - stones[1] + 1 == n - 1)
            return {min(maxmove, 2), maxmove};

        for (int i = 0, j = 0; j < n; j++) {
            while (stones[j] - stones[i] + 1 > n)
                ++i;
            minmove = min(minmove, n - (j - i + 1));
        }
        return {minmove, maxmove};
    }
};
```