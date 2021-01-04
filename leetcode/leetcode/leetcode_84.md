---
title: Largest Rectangle in Histogra
date: 2021-01-04
---
#### Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.


![](https://assets.leetcode.com/uploads/2018/10/12/histogram.png)

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

![](https://assets.leetcode.com/uploads/2018/10/12/histogram_area.png)

The largest rectangle is shown in the shaded area, which has area = 10 unit.


```
Example:

Input: [2,1,5,6,2,3]
Output: 10
```

#### Solutions

1. ##### straight forward O(n2)

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxaera = 0;
        for (int i = 0; i < heights.size(); i++) {
            int minh = INT_MAX;
            for (int j = i; j < heights.size(); j++) {
                minh = min(minh, heights[j]);
                maxaera = max(maxaera, (j - i + 1) * minh);
            }
        }
        return maxaera;
    }
};
```

2. ##### expanding O(n)

- For a certain bar `k`, the maximum area can be achieved by extending to both sides, the area is bounded only by the height of itself denoted as `h[k]`. Thus we need to get the maximum region it can be extended to.
    - The first bar left to the current bar whose height is less than or equal to `h[k]` is `i`.
    - The right boundary bar denoted as `j` with the same rule as above.
    - Them maximum area can be calculated as `h[k] * (j - i)`
- Codes below find the first bar with height lower than the center bar, thus the fomulation has changed to `h[k] * (j - i - 1)`.
```cpp

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if (!heights.size()) return 0;
        int leftless[heights.size()];
        int rightless[heights.size()];
        int maxarea = 0;

        leftless[0] = -1;
        for (int j = 0; j < heights.size(); j++) {
            int i = j - 1;
            while (i >= 0 && heights[i] >= heights[j])
                i = leftless[i];
            leftless[j] = i;
        }

        rightless[heights.size() - 1] = heights.size();
        for (int i = heights.size() - 1; i >= 0; i--) {
            int j = i + 1;
            while (j < heights.size() && heights[j] >= heights[i])
                j = rightless[j];
            rightless[i] = j;
        }

        for (int i = 0; i < heights.size(); i++) {
            int area = heights[i] * (rightless[i] - leftless[i] - 1);
            if (area > maxarea)
                maxarea = area;
        }

        return maxarea;
    }
};
```

3. ##### optimized version with stack O(n)
- Bars are stored in monotonically increasing order, `s[i - 1]` is the first bar shorter than `s[i]` in the left side.
- Push `-1` into the `stack` as a left guard.
- Push `-1` into the `heights` as the imaginary right boundary.

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        stack<int> s; s.push(-1);
        heights.push_back(-1);
        for (int cur = 0; cur < heights.size(); cur++) {
            // as it's mono stack, all bars between s.top() and cur are greater than or equal to  height[s.top()].
            while (s.top() != - 1 && heights[s.top()] > heights[cur]) {
                auto h = heights[s.top()]; s.pop();
                res = max(res, (cur - s.top() - 1) * h);
            }
            s.push(cur);
        }

        return res;
    }
};
```