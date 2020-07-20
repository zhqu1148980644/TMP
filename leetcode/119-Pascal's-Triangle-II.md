#### Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.

#### Note that the row index starts from 0.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

![](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

```
Example:

Input: 3
Output: [1,3,3,1]
```

#### Follow up:

Could you optimize your algorithm to use only O(k) extra space?

#### Solutions

1. ##### dynamic programming

- To save the space used for recording the overriten pascal number in the last layer, we calculate from the end to the beginning.
- Only a half of a certain layer needs to be calculated since numbers in each layer are symmetric.

```c++
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex + 1, 1);
        int mid;
        // backward
        for (int i = 1; i <= rowIndex; i++) {
            mid = i - i / 2;
            for (int j = i - 1; j > 0 ; j--)
                // only calculate the second half of the row
                if (j >= mid)
                    res[j] += res[j - 1];
                else
                    res[j] = res[i - j];
        }

        return res;
    }
};
```

2. ##### math formula

- reference: https://leetcode-cn.com/problems/pascals-triangle-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--28/