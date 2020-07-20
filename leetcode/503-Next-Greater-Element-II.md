Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element. The Next Greater Number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, output -1 for this number.

Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number; 
The second 1's next greater number needs to search circularly, which is also 2.
Note: The length of given array won't exceed 10000.



#### Solutions

- check problem 496 for details.

1. ##### mono stack

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> s;
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!s.empty() && nums[i] >= s.top())
                s.pop();
            s.push(nums[i]);
        }
        vector<int> res(nums.size());
        int w = res.size() - 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!s.empty() && nums[i] >= s.top())
                s.pop();
            res[w--] = s.empty() ? -1 : s.top();
            s.push(nums[i]);
        }

        return res;
    }
};
```


- or use mod to simulate the double-sized rounded array.
- In this way, numbers didn't find the next greater in the first round(last half) has the chance to find it's next greater in the second round.

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> s;
        int len = nums.size(), w = 2 * len - 1;
        vector<int> res(len);
        for (int i = 2 * len - 1; i >= 0; i--) {
            while (!s.empty() && s.top() <= nums[i % len])
                s.pop();
            res[w-- % len] = s.empty() ? -1 : s.top();
            s.push(nums[i % len]);
        }
        return res;
    }
};
```

or decreasing stack

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int len = nums.size();
        stack<int> s;
        vector<int> res(nums.size(), INT_MAX);
        for (int i = 0; i < 2 * len; i++) {
            while (!s.empty() && nums[i % len] > nums[s.top()]) {
                res[s.top()] = nums[i % len];
                s.pop();
            }
            s.push(i % len);
        }
        for (auto & n : res)
            if (n == INT_MAX) n = -1;
        return res;
    }
};
```