---
title: Four Divisors
date: 2021-01-04
---
Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors.

If there is no such integer in the array, return 0.

 

```
Example 1:

Input: nums = [21,4,7]
Output: 32
Explanation:
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.
```

 

#### Constraints:

    1 <= nums.length <= 10^4
    1 <= nums[i] <= 10^5

#### Solutions

1. ##### straight forward O(n * sqrt(n))

```cpp
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int res = 0;
        for (auto n : nums) {
            int cnt = 2, sum = 1 + n;
            int sq = sqrt(n);
            for (int i = 2; i <= sq; i++) {
                if (n % i == 0) {
                    cnt += 2;
                    sum += i + n / i;
                }
            }
            if (sq * sq == n) {
                cnt--;
                sum -= sq;
            }
            if (cnt == 4)
                res += sum;
        }

        return res;
    }
};
```