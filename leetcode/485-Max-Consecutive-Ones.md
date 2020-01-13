#### Given a binary array, find the maximum number of consecutive 1s in this array.

```
Example 1:

Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
```

#### Note:

-    The input array will only contain 0 and 1.
-    The length of input array is a positive integer and will not exceed 10,000

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxc = 0, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1)
                count++;
            else {
                maxc = max(maxc, count);
                count = 0;
            }
        }
        maxc = max(maxc, count);
        return maxc;
    }
};
```