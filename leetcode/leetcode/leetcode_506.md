---
title: Relative Ranks
date: 2021-01-04
---
Given scores of N athletes, find their relative ranks and the people with the top three highest scores, who will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

Example 1:
Input: [5, 4, 3, 2, 1]
Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and "Bronze Medal". 
For the left two athletes, you just need to output their relative ranks according to their scores.
Note:
N is a positive integer and won't exceed 10,000.
All the scores of athletes are guaranteed to be unique.


#### Solutions

1. ##### sort

```cpp
class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        vector<int> indexes(nums.size());
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&nums](int i1, int i2) {
            return nums[i1] > nums[i2];
        });

        int rank = 1;
        vector<string> res(nums.size());
        for (auto i : indexes) {
            switch (rank) {
                case 1: res[i] = "Gold Medal"; break;
                case 2: res[i] = "Silver Medal"; break;
                case 3: res[i] = "Bronze Medal"; break;
                default: res[i] = to_string(rank);
            }
            rank++;
        }
        return res;
    }
};
```