---
title: Max Chunks To Make Sorted II
date: 2021-01-04
---
This question is the same as "Max Chunks to Make Sorted" except the integers of the given array are not necessarily distinct, the input array could be up to length 2000, and the elements could be up to 10**8.

Given an array arr of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

```
Example 1:

Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.

Example 2:

Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
```

#### Note:

-    arr will have length in range [1, 2000].
-    arr[i] will be an integer in range [0, 10**8].


#### Solutions

1. ##### sort with prefix sum  O(nlog(n)) S(n)

- reference: https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii/comments/28236
- The sum of a chunk in sorted array must be equal to the sum of the same chunk in permutated array.

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<int> sarr = arr;
        sort(sarr.begin(), sarr.end());

        long sumx = 0, sumy = 0, chunks = 0;

        for (int i = 0; i < arr.size(); i++) {
            sumx += arr[i]; sumy += sarr[i];
            if (sumx == sumy) {
                chunks++;
                sumx = sumy = 0;
            }
        }

        return chunks;
    }
};
```
- Another similar approach is to count the number elements occurred in sorted array and unsorted array within a given chunk, The chunks is valid only if these two counts are the same.
- See official answer for details.

2. ##### mono stack O(n) S(n)

- See previous problem 768.
- Maintains a stack storing the maximum number of each chunks and iteratively update(merge) chunks when traversing the permutated array.

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> s;

        for (int i = 0; i < arr.size(); i++) {
            // here is the difference compared to previous problem. Add chunks eagerly.
            if (s.empty() || arr[i] >= s.top())
                s.push(arr[i]);
            else {
                int lastmax = s.top(); s.pop();
                while (s.size() && s.top() > arr[i])
                    s.pop();
                s.push(lastmax);
            }
        }

        return s.size();
    }
};
```