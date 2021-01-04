---
title: Minimum Operations to Make a Subsequence
date: 2021-01-04
---
You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.

In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.

Return the minimum number of operations needed to make target a subsequence of arr.

A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.

 

Example 1:

Input: target = [5,1,3], arr = [9,4,2,3,4]
Output: 2
Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
Example 2:

Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
Output: 3
 

Constraints:

1 <= target.length, arr.length <= 105
1 <= target[i], arr[i] <= 109
target contains no duplicates.


#### Solutions

1. ##### longest common subsequence O(n2)

- The answer equals to `len(target) - len(LCS(target, arr))`
- Gets TLE.

```cpp

```

2. ##### longest increasing subsequence O(nlog(n))


- Since the `target` array consists of distinct elements, we can can convert numbers in `arr` into the corresponding unique indexes in `target`, than the LCS problem equals to the LIS problem.

```cpp
class Solution {
public:
    int lis(vector<int> & nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (res.empty() || nums[i] > res.back())
                res.push_back(nums[i]);
            else {
                auto it = lower_bound(res.begin(), res.end(), nums[i]);
                *it = nums[i];
            }
        }
        return res.size();
    }

    int minOperations(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> m;
        for (int i = 0; i < target.size(); i++)
            m[target[i]] = i;
        
        vector<int> indexes;
        for (auto n : arr) {
            if (m.count(n))
                indexes.push_back(m[n]);
        }

        return target.size() - lis(indexes);
    }
};
```