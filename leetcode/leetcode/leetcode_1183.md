---
title: Maximum Number of Ones
date: 2021-01-04
---
Consider a matrix M with dimensions width * height, such that every cell has value 0 or 1, and any square sub-matrix of M of size sideLength * sideLength has at most maxOnes ones.

Return the maximum possible number of ones that the matrix M can have.

 

```
Example 1:

Input: width = 3, height = 3, sideLength = 2, maxOnes = 1
Output: 4
Explanation:
In a 3*3 matrix, no 2*2 sub-matrix can have more than 1 one.
The best solution that has 4 ones is:
[1,0,1]
[0,0,0]
[1,0,1]

Example 2:

Input: width = 3, height = 3, sideLength = 2, maxOnes = 2
Output: 6
Explanation:
[1,0,1]
[1,0,1]
[1,0,1]
```

 

#### Constraints:

-    1 <= width, height <= 100
-    1 <= sideLength <= width, height
-    0 <= maxOnes <= sideLength * sideLength


#### Solutions

- For the best case, we can divide the whole matix into multiple square with width  of sideLength and all `1`s in each square are in the same positions.
- How to prove ?

1. ##### priority queue O(nlog(maxOnes))

- In order to count the maximum possible ones, we use priority queue to store the number of `1` for each possible position such that the total number of `1` is the heighest.
- reference: https://leetcode-cn.com/problems/maximum-number-of-ones/solution/java-osidelength2-by-gaaakki/

```cpp
class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        priority_queue<int, vector<int>, greater<int>> pq;
        // try to set subsquare[i][j] to 1
        for (int i = 0; i < sideLength; i++)
            for (int j = 0; j < sideLength; j++) {
                // count the number of 1 in the final matrix for each position
                // you can also use ceil operation instead of using -1 + 1
                // ie: ceil((double)(width - i) / sideLength)
                int numw = (width - 1 - i) / sideLength + 1;
                int numh = (height - 1 - j) / sideLength + 1;
                pq.push(numw * numh);
                // pop the position with the minimum number of ones
                if (pq.size() > maxOnes)
                    pq.pop();
            }
        int res = 0;
        while (!pq.empty()) {
            res += pq.top();
            pq.pop();
        }

        return res;
    }
};
```


2. ##### sort O(nlog(n))

- Though the time complexity is higher than the first version, this solution is much faster than the first one in test cases.

```cpp
class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        vector<int> nums(sideLength * sideLength);
        int k = 0;
        for (int i = 0; i < sideLength; i++)
            for (int j = 0; j < sideLength; j++) {
                int numw = (width - 1 - i) / sideLength + 1;
                int numh = (height - 1 - j) / sideLength + 1;
                nums[k++] = numw * numh;
            }
        sort(nums.begin(), nums.end(), greater<int>());

        return accumulate(nums.begin(), nums.begin() + maxOnes, 0);
    }
};
```