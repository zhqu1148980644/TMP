---
title: Missing Number In Arithmetic Progression
date: 2021-01-04
---
In some array arr, the values were in arithmetic progression: the values arr[i+1] - arr[i] are all equal for every 0 <= i < arr.length - 1.

Then, a value from arr was removed that was not the first or last value in the array.

Return the removed value.

 

Example 1:

Input: arr = [5,7,11,13]
Output: 9
Explanation: The previous array was [5,7,9,11,13].
Example 2:

Input: arr = [15,13,12]
Output: 14
Explanation: The previous array was [15,14,13,12].
 

Constraints:

3 <= arr.length <= 1000
0 <= arr[i] <= 10^5

#### Solutions

1. #### straight forward

- Be careful when the step size is 0

```cpp
class Solution {
public:
    int missingNumber(vector<int>& arr) {
        int step = (arr.back() - arr.front()) / (int)arr.size();
        if (step == 0) return arr[0];
        for (int i = 1; i < arr.size(); i++)
            if (arr[i] - arr[i - 1] != step)
                return arr[i] - step;
        return -1;
    }
};
```