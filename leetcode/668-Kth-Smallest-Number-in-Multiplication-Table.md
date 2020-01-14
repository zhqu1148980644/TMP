#### Nearly every one have used the Multiplication Table. But could you find out the k-th smallest number quickly from the multiplication table?

Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.

```
Example 1:

Input: m = 3, n = 3, k = 5
Output: 
Explanation: 
The Multiplication Table:
1	2	3
2	4	6
3	6	9

The 5-th smallest number is 3 (1, 2, 2, 3, 3).

Example 2:

Input: m = 2, n = 3, k = 6
Output: 
Explanation: 
The Multiplication Table:
1	2	3
2	4	6

The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
```

#### Note:

-    The m and n will be in the range [1, 30000].
-    The k will be in the range [1, m * n]


#### Solutions

1. ##### binary search

- As m and n will be in the range(1, 300000), directly calculate all elements in the table could cause MLE.
- We can use binarySearch to speed up the search process because every row are in an ascending order.
- For each row, the number of elements smaller than `num` can be calculated by `num // row_index` where row_index is 1-based.



```c++
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int lo = 1, hi = m * n;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            int count = 0;
            for (int i = 1; i <= m; i++)
                count += min(mid / i, n);
            if (count < k)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
};
```