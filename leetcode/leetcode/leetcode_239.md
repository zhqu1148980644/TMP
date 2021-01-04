---
title: Sliding Window Maximu
date: 2021-01-04
---
#### Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

```
Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
 ```

#### Note:
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

#### Follow up:
Could you solve it in linear time?

#### Solutions

1. ##### straight forward O(nk)

- Time Limit Exceed

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (!nums.size()) return {};
        vector<int> res;
        for (int i = 0; i <= nums.size() - k; i++)
            res.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
        return res;
    }
};
using namespace std;
#include <iostream>
```

2. ##### Mono stack

- Any data structure with O(1) time complexity for push/pop both at front and back could be used as a momo stack.
- Here we use deque.
- A momo stack maintains a monotonically increasing sequence and keeps ordering of the pushed items.
    - Whenever pushed an item, check item at the back of queue which should be the minimum item of the queue, pop items till the back is not smaller than the current item. Thus ensure the queue follows an decreasing order from the front to the back.
    - To pop an item doesn't belong to the current window, we just need to check the front of the queue and remove it if it's the target.


```cpp
class MomoQueue {
public:
    deque<int> q;
    void push(int item) {
        while (!q.empty() && q.back() < item)
            q.pop_back();
        q.push_back(item);
    }
    int max() {
        return q.front();
    }
    bool pop(int item) {
        if (!q.empty() && q.front() == item) {
            q.pop_front();
            return true;
        } else
            return false;
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (!nums.size()) return {};
        MomoQueue mq;
        for (int i = 0; i < k; i++)
            mq.push(nums[i]);
        vector<int> res;
        res.push_back(mq.max());
        for (int i = k; i < nums.size(); i++) {
            // here we pop back the item outside the current window.
            mq.pop(nums[i - k]);
            mq.push(nums[i]);
            res.push_back(mq.max());
        }
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> q;
        vector<int> res;

        for (int i = 0; i < nums.size(); i++) {
            if (q.size() && q.front() <= i - k)
                q.pop_front();
            while (q.size() && nums[i] >= nums[q.back()])
                q.pop_back();
            q.push_back(i);
            if (i >= k - 1)
                res.push_back(nums[q.front()]);
        }

        return res;

    }
};
```

or

```rust
use std::collections::VecDeque;

impl Solution {
    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let mut res = vec![];
        let mut q = VecDeque::new();
        for (i, n) in nums.iter().enumerate() {
            if !q.is_empty() {
                if q[0] + k as usize - 1 < i {
                    q.pop_front();
                }
                while let Some(qi) = q.back() {
                    if *n > nums[*qi] {
                        q.pop_back();
                    }
                    else {
                        break;
                    }
                }
            }
            q.push_back(i);
            if i >= (k - 1) as usize {
                res.push(nums[q[0]]);
            }
        }
        res
    }
}
```


3. ##### dynamic programming O(n) S(n)

- See official answer in https://leetcode-cn.com/problems/sliding-window-maximum/solution/hua-dong-chuang-kou-zui-da-zhi-by-leetcode-3/

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        if (!nums.size())
            return {};
        if (nums.size() <= k)
            return {*max_element(nums.begin(), nums.end())};

        int left[len], right[len];
        left[0] = nums[0];
        right[len - 1] = nums[len - 1];


        for (int i = 1; i < len; i++) {
            if (i % k == 0)
                left[i] = nums[i];
            else
                left[i] = max(left[i - 1], nums[i]);

            int j = len - i - 1;
            if ((j + 1) % k == 0)
                right[j] = nums[j];
            else
                right[j] = max(right[j + 1], nums[j]);
        }

        vector<int> res;
        for (int i = 0; i <= len - k; i++) {
            res.push_back(max(left[i + k - 1], right[i]));
        }

        return res;
    }
};
```