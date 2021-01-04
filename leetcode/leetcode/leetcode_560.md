---
title: Subarray Sum Equals K
date: 2021-01-04
---
#### Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

```
Example 1:
Input:nums = [1,1,1], k = 2
Output: 2
```

#### Note:
The length of the array is in range [1, 20,000].
The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].


#### Solutions

Given `sum[:i]` and `sum[:j]` st `j > i` we can quickly calculate the sum between i and j: `sum[i: j] = sum[:j] - sum[:i]`

1. ##### prefix sum O(n2)

- Store the aggregated sum for each position, and scan the sum before each position to check if there any contigous subarray with the required sum using the formula above.

2. ##### prefix sum with hash map

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m {{0, 1}};
        int sum = 0, res = 0;
        for (auto n : nums) {
            sum += n;
            if (m.count(sum - k))
                res += m[sum - k];
            m[sum]++;
        }
        return res;
    }
};
```

or store expected_sums in the hash map

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m; m[k]++;
        int count = 0, sum = 0;
        for (auto & num : nums) {
            sum += num;
            if (m.find(sum) != m.end())
                count += m[sum];
            m[k + sum]++;
        }
        return count;
    }
};
```