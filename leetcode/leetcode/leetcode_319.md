---
title: Bulb Switcher
date: 2021-01-04
---
There are n bulbs that are initially off. You first turn on all the bulbs. Then, you turn off every second bulb. On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the i-th round, you toggle every i bulb. For the n-th round, you only toggle the last bulb. Find how many bulbs are on after n rounds.

Example:

Input: 3
Output: 1 
Explanation: 
At first, the three bulbs are [off, off, off].
After first round, the three bulbs are [on, on, on].
After second round, the three bulbs are [on, off, on].
After third round, the three bulbs are [on, off, off]. 

So you should return 1, because there is only one bulb is on.


#### Solution

- In summary, in the x'th(1-based) round, toggle bubbles with index(1-based) satisfies `index % x == 0`.


1. ##### math

- For bubble `6`(1-based), with any total number of bubbles denoted as n, it will be:
    - turned on at 1'th round 6 = 1 * 6
    - turned off at 2'th round 6 = 2 * 3
    - turned on at 3'th round 6 = 3 * 2
    - turned off at 6'th round 6 = 6 * 1
    - The final result is off
- We can see that if the bubble index is a square number, it will be turned on/off with even times `x = ab, a != b`. Only square numbers will be turned on at the end because `sq = a*a, a == a`
- The totoal number of square numbers below a given number equals to `floor(sqrt(n))`
    - `1 * 1, 2 * 2, 3 * 3, 4 * 4, .... sqrt(n) * sqrt(n) <= n`.

```cpp
class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(n);
    }
};
```