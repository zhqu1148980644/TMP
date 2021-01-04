---
title: Max Chunks To Make Sorte
date: 2021-01-04
---
Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

```
Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.

Example 2:

Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.
```

#### Note:

-    arr will have length in range [1, 10].
-    arr[i] will be a permutation of [0, 1, ..., arr.length - 1].


#### Solutions

1. ##### straight forward


- As the given array is a permutation of `[0, 1, ..., arr.length - 1]`, elements in sorted array is the same as their corresponding index. For example:
- `1 0 2 3 4`  sorted:  `0 1 2 3 4`
- To make a given chunk a part of the final sorted array, the maximum number within the chunk must equals to the index of the last element in this chunk. ie. maximum number in `1 0` is `1` and the index of the last element is `1`.
- The more general rule is: 
    - If `max(array[i, j]) <= arr[j + 1:]`, then `array[i:j]` is a valid chunk that the sorted chunk will be exactly the same as this chunk in sorted array.

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int max = -1, chunks = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] > max)
                max = arr[i];
            if (i == max) {
                chunks++;
                max = -1;
            }
        }
        
        return chunks;
    }
};
```


2. ##### mono stack

- As we can see, a valid chunk is determined by the maximum number within it, thus we use a monotonically increasing stack to record and update these maximum numbers in each chunk.
- If `array[i]` is bigger than the top of the stack, push it into the stack.
- Else, store the current top of stack as the maximum number of this chunk, and pop every items in stack that are larger than `array[i]`. Finally, push the stored maximum number into the stack.
- At the last, the stack only conatains maximum numbers of each chunks.

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> s;

        for (int i = 0; i < arr.size(); i++) {
            if (s.empty() || arr[i] > s.top())
                s.push(arr[i]); 
            else {
                int curmax = s.top(); s.pop();
                // pop all element in this chunk
                while (s.size() && arr[i] < s.top())
                    s.pop();
                s.push(curmax);
            }
        }

        return s.size();
    }
};
```