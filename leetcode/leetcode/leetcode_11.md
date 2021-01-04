---
title: Container With Most Water
date: 2021-01-04
---
### Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

### Note: 
You may not slant the container and n is at least 2.

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg)


### Solutions

1. #### Brute force O(n2)

```python
class Solution:
    def maxArea(self, height: List[int]) -> int:
        max_v = 0;
        for i in range(len(height)):
            for j in range(i + 1, len(height)):
                cur_v = min(height[i], height[j]) * (j - i)
                max_v = cur_v if cur_v > max_v else max_v
        return max_v
```


2. #### two pointer or greedy method O(n)

- One pointer start from 0, another pointer start from the end.
- In each step, calculate the current valid volumn of water, then move the shoter one forward one step towards center.
    - TODO: Proof of correctness. Shrink the solution space.


```cpp
#define max(x, y) ((x > y) ? (x) : (y))
int maxArea(int* height, int heightSize){
    int max_size = 0;
    int left = 0, right = heightSize - 1;
    while (left < right) {
        if (height[left] > height[right]) {
            max_size = max((right - left) * height[right], max_size);
            right--;
        } else {
            max_size = max((right - left) * height[left], max_size);
            left++;
        }
    }
    return max_size;
}
```