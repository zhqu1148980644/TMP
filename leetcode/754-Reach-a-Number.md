You are standing at position 0 on an infinite number line. There is a goal at position target.

On each move, you can either go left or right. During the n-th move (starting from 1), you take n steps.

Return the minimum number of steps required to reach the destination.

```
Example 1:

Input: target = 3
Output: 2
Explanation:
On the first move we step from 0 to 1.
On the second step we step from 1 to 3.

Example 2:

Input: target = 2
Output: 3
Explanation:
On the first move we step from 0 to 1.
On the second move we step  from 1 to -1.
On the third move we step from -1 to 2.
```

#### Note:
target will be a non-zero integer in the range [-10^9, 10^9].


1. ##### math

- reference: https://leetcode-cn.com/problems/reach-a-number/solution/deng-jie-yu-shu-zu-tian-jia-zheng-fu-hao-wen-ti-by/
- Denote `s = 1 + 2 + 3 ... + n` and `s` is the first number larger than or equal to target.
- We need to flip signs of numbers with sum equals to `x` in `[1:n]` to make `s - 2x == target`, thus `s - target` must be even number.
- So, the answer is the first numer whose accumulate sum is larger than or equal to target and the difference between itself and the target is even.


```c++
class Solution {
public:
    int reachNumber(int target) {
        target = abs(target);
        int i = 1;

        while (true) {
            int sum = i * (i + 1) / 2;
            if (sum >= target && (sum - target) % 2 == 0)
                break;
            i++;
        }
        return i;
    }
};
```
