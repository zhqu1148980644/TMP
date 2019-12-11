#### Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

```
Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
```

#### Note:

Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?


#### Solutions

1. ##### Staight forward

1 + 2 + 3... + n = n * (n + 1) / 2

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0;
        int expected_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            expected_sum += i + 1;
        }
        return expected_sum - sum;
    }
};
```