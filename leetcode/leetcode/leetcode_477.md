---
title: Total Hamming Distance
date: 2021-01-04
---
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the given numbers.

Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Note:
Elements of the given array are in the range of 0 to 10^9
Length of the array will not exceed 10^4.


#### Solutions

1. ##### count distance for every bit O(32n)

- For each bit, the distance in this bit equals to `nzero * none`, `nzero` represents the number of elements with this bit set to `0`.

```cpp
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            int zero = 0, one = 0;
            for (auto n : nums) {
                if (n & (1 << i))
                    one++;
                else
                    zero++;
            }
            res += one * zero;
        }
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(32);

        for (auto num : nums) {
            int i = 0;
            while (num) {
                if (num & 1)
                    count[i]++;
                num >>= 1; i++;
            }
        }

        int res = 0;
        for (auto c : count)
            res += c * (n - c);
        return res;
    }
};
```