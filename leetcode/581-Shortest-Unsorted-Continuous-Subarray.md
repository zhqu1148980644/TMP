#### Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

```
Example 1:

Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
```

#### Note:

-    Then length of the input array is in range [1, 10,000].
-    The input array may contain duplicates, so ascending order here means <=. 

#### Solutions

1. ##### sort O(nlog(n))

- Sort the original array and find the first and last element that are different in two arrays.

```c++
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> snums(nums);
        sort(snums.begin(), snums.end());
        int mini = nums.size() - 1, maxi = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != snums[i]) {
                mini = min(i, mini);
                maxi = max(i, maxi);
            }
        }
        return maxi - mini > 0 ? maxi - mini + 1 : 0; 
    }
};
```

Python version:

```python
class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        diff = [i for i, (a, b)
                  in enumerate(zip(nums, sorted(nums))) if a != b]
        return len(diff) and max(diff) - min(diff) + 1
```


2. ##### two pass O(n)

- The idea is to find the minimum value and maximum value in the unordered subarray, then the shorted subarray containing all numbers wihthin this range(open) is the required subarray that can make the whole array sorted in ascending order when itself is sorted.
    - For finding the peak value of the subarray for example:
    - Finding all ajcant number pairs, whenever meet a pair with the second number smaller than the first number, update the peak value if the first number is larger it.


```c++
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        int valley = INT_MAX, peak = INT_MIN;
        for (int i = 0; i < nums.size() - 1; i++)
            if (nums[i + 1] < nums[i])
                peak = max(peak, nums[i]);
        for (int i = nums.size() - 1; i > 0; i--)
            if (nums[i - 1] > nums[i])
                valley = min(valley, nums[i]);
        int i, j;
        // this must be >/<>, can bot be >=/<=
        for (i = 0; i < nums.size(); i++)
            if (valley < nums[i]) break;
        for (j = nums.size() - 1; j >= 0; j--)
            if (peak > nums[j]) break;

        return max(j - i + 1, 0);
    }
};
```

3. ##### mono stack

- Use mono stack to find the smallest valley and largest peak.
- Elements in stack are always in ascending/desending order.

```c++
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        stack<int> s;
        int valley = nums.size() - 1, peak = 0;
        for (int i = 0; i < nums.size(); i++) {
            while (!s.empty() && nums[s.top()] > nums[i]) {
                valley = min(valley, s.top()); s.pop();
            }
            s.push(i);
        }
        s = stack<int>();
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!s.empty() && nums[s.top()] < nums[i]) {
                peak = max(peak, s.top()); s.pop();
            }
            s.push(i);
        }
        return peak - valley > 0 ? peak - valley + 1 : 0;
    }
};
```