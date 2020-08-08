(This problem is an interactive problem.)

You may recall that an array A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]
Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.

You can't access the mountain array directly.  You may only access the array using a MountainArray interface:

MountainArray.get(k) returns the element of the array at index k (0-indexed).
MountainArray.length() returns the length of the array.
Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.

 

Example 1:

Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
Example 2:

Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.
 

Constraints:

3 <= mountain_arr.length() <= 10000
0 <= target <= 10^9
0 <= mountain_arr.get(index) <= 10^9

#### Solutions

1. ##### binary search

```c++
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    template <typename Cmp>
    int bisearch(int lo, int hi, Cmp cmp) {
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            // moves only when 100% sure
            if (cmp(mid))
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
    int findInMountainArray(int target, MountainArray &mountainArr) {
        auto findpivot = [&](int mid) {
            return mountainArr.get(mid) < mountainArr.get(mid + 1);
        };
        auto findleft = [&](int mid) {
            return target > mountainArr.get(mid);
        };
        auto findright = [&](int mid) {
            return target < mountainArr.get(mid);
        };
        // find mountain peak
        int n = mountainArr.length();
        int maxi = bisearch(0, n - 1, findpivot);
        // try to search in the left part
        int lefti = bisearch(0, maxi, findleft);
        if (mountainArr.get(lefti) == target)
            return lefti;
        // try to search in the right part
        int righti = bisearch(maxi + 1, n - 1, findright);
        return mountainArr.get(righti) == target ? righti : -1;
    }
};
````