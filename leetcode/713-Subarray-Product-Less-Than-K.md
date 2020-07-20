Your are given an array of positive integers nums.

Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Note:

0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.

#### Solutions

1. ##### sliding window O(n)

- count the number of subarrays starting at `i`, `i` is the left boundary of the valid window.

```c++
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        double pro = 1, res = 0;
        int i = 0, j = 0;        
        // as we are counting substrings starting at i, we need to forward i tiil the end in the last for loop.
        nums.push_back(INT_MAX / 2);
        while (j < nums.size()) {
            if ((pro *= nums[j++]) >= k) {
                // must add i < j in case like: 5 4 6, k = 1, other wise i will move over j
                while (pro >= k && i < j) {
                    pro /= nums[i++];
                    res += j - i;
                }
            }
        }
        return res;
    }
};
```

or

```c++
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        double pro = 1, res = 0;
        int i = 0, j = 0;

        nums.push_back(INT_MAX / 2);
        while (j < nums.size()) {
            if ((pro *= nums[j++]) >= k) {
                while (pro >= k) {
                    pro /= nums[i++];
                    res += j - i;
                }
            }
        }
        return res;
    }
};
```

or count the number of subarrys ending at `j - 1`


```c++
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        int pro = 1, res = 0;
        int i = 0, j = 0;
        while (j < nums.size()) {
            if ((pro *= nums[j++]) >= k)
                while (pro >= k)
                    pro /= nums[i++];
            res += j - i;
        }
        return res;
    }
};

```

2. ##### binary search O(nlog(n))

- Transform product into log sum to aoid the product gets too large. Then the problem equals to find the number of subarrays with sum slower than log(k).

```c++


```