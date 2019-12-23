#### Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into sets of k consecutive numbers
Return True if its possible otherwise return False.

 

```
Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
Example 3:

Input: nums = [3,3,2,2,1,1], k = 3
Output: true
Example 4:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.
```
 

#### Constraints:

- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 1 <= k <= nums.length


#### Solutions


1. ##### hashmap

- borrowed from others.
- Put each item in an ordered hashmap, at each iteration:
    - staring from the minimum number, trying to find k consecutive numbers and deduce the corresponding count, return false when the search fails.

```c++
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        map<int, int> count;
        for (auto & num : nums)
            count[num]++;
        auto start = count.begin();
        int prev;
        while (start != count.end()) {
            for (int i = 0; i < k; i++, start++) {
                if (i == 0)
                    prev = start->first;
                else {
                    if (!start->second  || start->first != prev + 1)
                        return false;
                    prev = start->first;
                }
                start->second--;
            }
            start = count.begin();
            // move to the next mininum number with count larger than 0
            while (start != count.end() && !start->second) start++;
        }
        return true;
    }
};
```


2. ##### heap