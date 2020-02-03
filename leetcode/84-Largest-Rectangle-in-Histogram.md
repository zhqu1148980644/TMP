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

```c++
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

- For a certain bar `k`, the maximum area can be achieved by extending to both sides is bounded only by the height of itself denoted as `h[k]`. Thus we need to get the maximum region it can be extended to.
    - The leftmost bar left to the current bar whose height is less than or equal to `h[k]` is `i`.
    - The rightmost bar is `j` following the same rule as above.
    - Them maximum area can be calculated as `h[k] * (j - i)`
- Codes below find the first bar with height lower than the center bar, thus the fomulation has changed to `h[k] * (j - i - 1)`.
```c++

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

- Use a stack to record the leftmost smaller element.
- Invariant: elements in the stack are always in ascending order and the former element is the first smaller element left to the next element.
- Push `-1` into the stack as a left guard.

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s; s.push(-1);
        int maxarea = 0, len = heights.size();

        for (int cur = 0; cur < len; cur++) {
            // left is secure
            while (s.top() != -1 &&  heights[s.top()] >= heights[cur]) {
                auto top = s.top(); s.pop();
                maxarea = max((cur - s.top() - 1) * heights[top], maxarea);
            }
            s.push(cur);
        }
        // right is secure
        while (s.top() != -1) {
            auto top = s.top(); s.pop();
            maxarea = max((len - s.top() - 1) * heights[top], maxarea);
        }
        return maxarea;
    }
};
```