Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?


#### Solutions

1. ##### sliding window

```c++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int i = 0, j = 0, zero = 0, res = 0;
        while (j < nums.size()) {
            if (nums[j++] == 0)
                zero++;
            if (zero > 1) {
                // record when the window is corrupted
                res = max(res, j - i - 1);
                while(nums[i++] != 0);
                zero--;
            }
        }
        // the last valid window may not be recorded
        res = max(res, j - i);
        return res;
    }
};
```

or

```c++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int i = 0, j = 0, zero = 0, res = 0;
        queue<int> q;
        while (j < nums.size()) {
            if (nums[j++] == 0) {
                q.push(j - 1);
                zero++;
            }
            if (zero > 1) {
                res = max(res, j - i - 1);
                i = q.front() + 1; q.pop();
                zero--;
            }
        }
        res = max(res, j - i);
        return res;
    }
};
```

2. ##### dynamic programming

- dp0 represents the number of consecutive 1s ends at the previous position with no 0 flipped.
- dp1 represents the number of consecutive 1s ends at the previous position with `1` 0 flipped.

```c++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int dp0 = 0, dp1 = 0, res = 0;
        for (auto n : nums) {
            if (n == 0) {
                // be careful about the assignment order
                dp1 = dp0 + 1;
                dp0 = 0;
            }
            else {
                dp0 = dp0 + 1;
                dp1 = dp1 + 1;
            }

            res = max(res, max(dp0, dp1));
        }

        return res;
    }
};
```