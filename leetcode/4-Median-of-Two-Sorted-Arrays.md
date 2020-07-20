There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

```
Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
```

#### Solutions


2. ##### merge O(n1 + n2)

- Merge two sorted arrays.

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        int mid = (len1 + len2 - 1) / 2;
        int i = 0, j = 0;
        double cur;
        while (i + j <= mid) {
            if (i < len1 && (j >= len2 || nums1[i] <= nums2[j]))
                cur = nums1[i++];
            else
                cur = nums2[j++];
        }
        if ((len1 + len2) % 2)
            return cur;
        else {
            if (i < len1 && (j >= len2 || nums1[i] <= nums2[j]))
                return (cur + nums1[i]) / 2;
            else
                return (cur + nums2[j]) / 2;
        }
    }
};
```


2. ##### binary search  O(log(min(n1, n2)))


- reference: https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2471/Very-concise-O(log(min(MN)))-iterative-solution-with-detailed-explanation
- See reference for details.
- The idea is to use imaginary cutting positions to prevent handling edge cases and even/odd situations.
- For a given string, insert `#` into the string, thus the total number of cuts is `2 * N + 1` which is always a odd number.
    - By this way, we do not need to treat arrays with odd/even length in different ways. Each array will be assigned to single cut.
- To make the cutted two parts(actually 4 parts(l1 + l2 and r1 and r2)) have the same length, suppose we cut at `c1` in `array 1`, the cut position in array 2 must be `c2 = n1 + n2 - c1`.
- To make the cut right, we need to ensure `l1 < r2 && l2 < r1`.
- Finally, since there `2n + 1` possible cut positions in array 1`(0 ... 2n)`, we use binary search to find this cut position `c1` such that the relation mentioned above satisfies.

```s
     0                   10
A1: [# 1 # 2 # 3 # 4 # 5 #]    (N1 = 5, N1_positions = 11)
       c1                      left to c1: 1 positions      right to c1: 9 positions
A2: [# 1 # 1 # 1 # 1 #]        (N2 = 4, N2_positions = 9)
                     c2        left to c2: 8 positions      right to c2: 0 positions

totoal positions: 2 * 5 + 2 * 4 + 2 = 20
left to two cuts: 1 + 8   = 9   positions
right to two cuts: 9 + 0 = 9   positions
And the relation satisfies: numbers in left part <= numbers in right part
```



```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // why we choose the shorter one as num1?
        // When num1(the longer one) becomes way longer, cut2 will be negative, which is not permitted.
        if (nums2.size() < nums1.size())
            return findMedianSortedArrays(nums2, nums1);
        
        int len1 = nums1.size(), len2 = nums2.size();
        int lo = 0, hi = 2 * len1;
        while (lo <= hi) {
            int cut1 = lo + ((hi - lo) >> 1);
            int cut2 = len1 + len2 - cut1;

            double l1 = cut1 > 0 ? nums1[(cut1 - 1) >> 1] : INT_MIN;
            double l2 = cut2 > 0 ? nums2[(cut2 - 1) >> 1] : INT_MIN;
            double r1 = cut1 < 2 * len1 ? nums1[cut1 >> 1] : INT_MAX;
            double r2 = cut2 < 2 * len2 ? nums2[cut2 >> 1] : INT_MAX;

            if (l2 > r1)
                lo = cut1 + 1;
            else if (l1 > r2)
                hi = cut1 - 1;
            else
                return (max(l1, l2) + min(r1, r2)) / 2;
        }
        return -1;
    }
};
```