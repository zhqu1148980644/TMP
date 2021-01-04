---
title: Search in a Sorted Array of Unknown Size
date: 2021-01-04
---
Given an integer array sorted in ascending order, write a function to search target in nums.  If target exists, then return its index, otherwise return -1. However, the array size is unknown to you. You may only access the array using an ArrayReader interface, where ArrayReader.get(k) returns the element of the array at index k (0-indexed).

You may assume all integers in the array are less than 10000, and if you access the array out of bounds, ArrayReader.get will return 2147483647.

 

Example 1:

Input: array = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4
Example 2:

Input: array = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
 

Constraints:

You may assume that all elements in the array are unique.
The value of each element in the array will be in the range [-9999, 9999].
The length of the array will be in the range [1, 10^4].

#### Solutions

1. ##### binary search

- As out of boundary elements are all bigger than elements in the array, the searching space will always be correctly shrinked.

```cpp
/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int lo = 0, hi = 1e4;
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (target > reader.get(mid))
                lo = mid + 1;
            else
                hi = mid;
        }
        return reader.get(lo) == target ? lo : -1;
    }
};
```

or firsly find a valid upper bound.

```cpp
class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int lo = 0, hi = 1;
        while (reader.get(hi - 1) < target) hi <<= 1;
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (target > reader.get(mid))
                lo = mid + 1;
            else
                hi = mid;
        }
        return reader.get(lo) == target ? lo : -1;
    }
};
```