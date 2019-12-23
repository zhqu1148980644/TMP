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

1. ##### straight forward O(n2)

- Store the aggregated sum for each position, and scan the sum before each position to check if there any contigous subarray with the required sum using the formula above.

1. ##### hash map

- The idea is the same to `two-sum` problem, use a hash map to store candidate values.
- Here I saved the `expected_sum` in hash map. you can store the original sum in each position too.
    - `cur_sum - old_sum = k` ie: `cur_sum = k + old_sum`.

```c++
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
