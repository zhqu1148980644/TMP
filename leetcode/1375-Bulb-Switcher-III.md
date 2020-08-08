

There is a room with n bulbs, numbered from 1 to n, arranged in a row from left to right. Initially, all the bulbs are turned off.

At moment k (for k from 0 to n - 1), we turn on the light[k] bulb. A bulb change color to blue only if it is on and all the previous bulbs (to the left) are turned on too.

Return the number of moments in which all turned on bulbs are blue.

 
![](https://assets.leetcode.com/uploads/2020/02/29/sample_2_1725.png)

```
Example 1:

Input: light = [2,1,3,5,4]
Output: 3
Explanation: All bulbs turned on, are blue at the moment 1, 2 and 4.

Example 2:

Input: light = [3,2,4,1,5]
Output: 2
Explanation: All bulbs turned on, are blue at the moment 3, and 4 (index-0).

Example 3:

Input: light = [4,1,2,3]
Output: 1
Explanation: All bulbs turned on, are blue at the moment 3 (index-0).
Bulb 4th changes to blue at the moment 3.

Example 4:

Input: light = [2,1,4,3,6,5]
Output: 3

Example 5:

Input: light = [1,2,3,4,5,6]
Output: 6
```

 

##### Constraints:

-    n == light.length
-    1 <= n <= 5 * 10^4
-    light is a permutation of  [1, 2, ..., n]



#### Solutions

1. ##### straight forward

- All opened bubbles are blue when the number of open bubbles equals to the last(max) index of open bubbles.


```c++
class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        if (light.size() == 0)
            return 0;
        int cnt = 0, maxb = 0, num = 0;
        for (auto index : light) {
            maxb = max(maxb, index);
            num += 1;
            cnt += num == maxb;
        }
        
        return cnt;
    }
};
```