---
title: Find the Duplicate Number
date: 2021-01-04
---
#### Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

```
Example 1:

Input: [1,3,4,2,2]
Output: 2

Example 2:

Input: [3,1,3,4,2]
Output: 3
```

#### Note:

-    You must not modify the array (assume the array is read only).
-    You must use only constant, O(1) extra space.
-    Your runtime complexity should be less than O(n2).
-    There is only one duplicate number in the array, but it could be repeated more than once.


#### Solutions


1. ##### sort  O(nlog(n)) S(1)

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1])
                return nums[i];
        }
        return nums[0];
    }
};
```

2. ##### set O(n) S(n)

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_set<int> s;

        for (auto & num : nums) {
            if (s.count(num))
                return num;
            else
                s.insert(num);
        }

        return nums[0];
    }
};
```

3. ##### bucket sort

- Though the problem said we can not modify the array.

```cpp

```

4. ##### floyd method

- Think the array as a linked list.
- For example: `1 3 4 2 2`, starting from the first node wiht index 0:
    - `0(1) -> 1(3) -> 3(2) -> 2(4) -> 4(2)`. The cycle is `4 -> 2`.
- Check `problem 142` for detailed explanation.

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0], fast = nums[nums[0]];
        // the meeting node may not be the intersection node of the loop
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        // slow starting at zero
        int finder = 0;
        while (finder != slow) {
            finder = nums[finder];
            slow = nums[slow];
        }

        return finder;
    }
};
```