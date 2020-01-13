#### Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

```
Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]
```

#### Solutions


1. ##### inplace hasmap

```c++
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (auto num : nums) {
            num = num < 0 ? -num : num;
            if (nums[num - 1] < 0)
                res.push_back(num);
            nums[num - 1] *= -1;
        }
        // -1 - > 1  or  1 - > -1
        return res;
    }
};
```

2. ##### Pigeonhole principle

```c++
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1)
                res.push_back(nums[i]);
        }
        return res;
    }
};
```