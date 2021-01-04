---
title: 132 Pattern
date: 2021-01-04
---
Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

Note: n will be less than 15,000.

Example 1:
Input: [1, 2, 3, 4]

Output: False

Explanation: There is no 132 pattern in the sequence.
Example 2:
Input: [3, 1, 4, 2]

Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:
Input: [-1, 3, 2, 0]

Output: True

Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].


#### Solutions

1. ##### stack

- Maitaining a `minl` vector which records the minimum value before each element. and start checking from the last element, in the meantime, use a stack to record elements bigger than `minl[i]` after `element[i]`. if `current[i] > minl[i] and current[i] > s.top()`, return true.
- Popping out the top of the stack if it's smaller than `minl[i]` would not interfere with future comparisons, it's due to the fact that `minl[:i - 1] >= minl[i]`, if the current top is smaller/eq than `minl[i]`, it must be smaller/eq than `minl[:i-1]`.
- Although the stack is a monotonically decreasing stack, it's not intend to be used. If the current number is bigger than the top of the stack, the loop ends and returns true.

```cpp
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) return false;
        vector<int> minl(nums.size(), INT_MAX);
        for (int i = 1; i < nums.size(); i++)
            minl[i] = min(minl[i - 1], nums[i - 1]);
        
        stack<int> s; s.push(INT_MAX);
        for (int i = nums.size() - 1; i > 0; i--) {
            if (nums[i] > minl[i]) {
                while (s.top() <= minl[i])
                    s.pop();
                if (s.top() < nums[i])
                    return true;
                s.push(nums[i]);
            }
            // since minl[:i - 1] is >= minl[i], push (nums[i] < minl[i]) into stack is pointless. Though push at the top don't change the result
        }

        return false;
    }
};
```

2. ##### stack

- borrowed from others
- For a given element, `min` represents the larget element smaller than self after this element.
- `nums[i] < nums[k] < nums[j]` satisfies when `nums[i] < min` when traversing the array backwards.
- Since we only used one `min` variable, how to prove that there are no other `min`s being missed after the loop ends?
    - Suppose the current number is `i` and `minold > i` is missed because of some other number is greater than the corresponding `maxold` related to `minold`, then `mini(the min setted before meeting i)` must be greater than `maxold` which also leads to a valid `132` pair.

```cpp
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        stack<int> s; s.push(INT_MAX);
        int min = INT_MIN;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] < min)
                return true;
            while (nums[i] > s.top()) {
                min = s.top(); s.pop();
            }
            s.push(nums[i]);
        }
        return false;
    }
};
```