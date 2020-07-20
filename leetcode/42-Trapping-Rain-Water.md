### Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

![t](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

```
Example:

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
```

### Solutions

For a certain position the final water level equals to the smaller one between the highest bar in the left and the highest bar in the right.

- Similar to problem 11 Container with most water.
- Use two pointer way can reduce(prune) the time complexity to O(n).

1. #### Calculate the left's heighest and right's highest for every position. O(3n) S(2n)/S(n)

- Use dynamic programming(or we can say greedy method) to calculate each bins left-heighest and right-heighest. O(2n)
- Sum up the difference between water level and bar height for each position. O(n)
- Another version O(2n):
    - Only maitain the left-heights array.
    - After we get the left-heights array, loop start from the end to left and sum up the volumn.

```c++
#define max(x, y) ( x > y ? x : y)
#define min(x, y) ( x < y ? x : y)

int trap(int* height, int heightSize){
    if (heightSize <= 2) return 0;
    int leftHeight[heightSize];
    int rightHeight[heightSize];
    leftHeight[0] = 0;
    for (int i = 1; i < heightSize; i++)
        leftHeight[i] = max(leftHeight[i - 1], height[i - 1]);
    rightHeight[heightSize - 1] = 0;
    for (int i = heightSize - 2; i >= 0; i--)
        rightHeight[i] = max(rightHeight[i + 1], height[i + 1]);
    int res;
    for (int i = 0; i < heightSize; i++) {
        int sum = min(leftHeight[i], rightHeight[i]) - height[i];
        res += sum > 0 ? sum : 0;
    }
    return res;
}
```

2. #### Find the highest bar then loop from both the start and the end. O(2n) S(1)

```python
class Solution:
    def trap(self, height: List[int]) -> int:
        max_i = 0
        max_h = 0
        for i, h in enumerate(height):
            if h > max_h:
                max_i = i
                max_h = h
        res = 0;
        cur_max = 0;
        for i in range(max_i):
            res += max(min(cur_max, max_h) - height[i], 0)
            cur_max = max(cur_max, height[i])
        cur_max = 0;
        for i in range(len(height) - 1, max_i, -1):
            res += max(min(cur_max, max_h) - height[i], 0)
            cur_max = max(cur_max, height[i])

        return res
```

3. #### two pointers. O(n)

- Use two value to record the left-heighest and right-heighest. 
- Move the lower one forward to ensure that all bars in the lower side is smaller than the current higher bar. Thus the water level of lower one is solely constrained by this side's highest bar.

```c++
class Solution {
public:
    int trap(vector<int> & height) {
        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int ans = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (left_max > height[left])
                    ans += left_max - height[left];
                else
                    left_max = height[left];
                left++;
            } else {
                if (right_max > height[right])
                    ans += right_max - height[right];
                else
                    right_max = height[right];
                right--;
            }
        }
        return ans;
    }
};
```

4. #### Optimized two pointer version. O(n)

- borrowed from stephan.
- only maintain the smallest height(water level) between left-heighest and right-heighest.

```c++
class Solution {
public:
    int trap(vector<int> & height) {
        int level = 0;
        int l = 0, r = height.size() - 1;
        int ans = 0;
        while (l < r) {
            int low = height[height[l] < height[r] ? l++ : r--];
            level = max(low, level);
            ans += level - low;
        }
        return ans;
    }
};
```

5. #### stack version.


```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        stack<int> s;
        for (int i = 0; i < height.size(); i++) {
            while (!s.empty() && height[s.top()] < height[i]) {
                int curh = height[s.top()]; s.pop();
                if (s.empty()) break;
                int l = s.top(), r = i;
                // each level will be counted only once.
                // for multibar with the same height, only the first bar will acounts(others as 0 diff).
                res += (min(height[l], height[r]) - curh) * (i - s.top() - 1);
            }
            s.push(i);
        }

        return res;
    }
};
```