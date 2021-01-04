---
title: Next Greater Element I
date: 2021-01-04
---
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.


#### Solutions


1. ##### mono stack

- Traversing `nums2` backwards and use a monotonically increasing stack to record the first greater number of each element.

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        if (!nums2.size()) return {};
        stack<int> s;
        unordered_map<int, int> m;
        for (int i = nums2.size() - 1; i >= 0; i--) {
            while (!s.empty() && s.top() < nums2[i])
                s.pop();
            if (!s.empty())
                m[nums2[i]] = s.top();
            s.push(nums2[i]);
        }

        vector<int> res(nums1.size());
        int w = 0;
        for (auto n : nums1)
            res[w++] = m.count(n) ? m[n] : -1;
        
        return res;
    }
};
```


or traversing nums2 forwards from the start with monotonically decreasing stack

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        if (!nums2.size()) return {};
        stack<int> s;
        unordered_map<int, int> m;

        for (auto n : nums2) {
            while (!s.empty() && s.top() < n) {
                m[s.top()] = n; s.pop();
            }
            s.push(n);
        }

        vector<int> res(nums1.size());
        int w = 0;
        for (auto n : nums1)
            res[w++] = m.count(n) ? m[n] : -1;

        return res;
    }
};
```