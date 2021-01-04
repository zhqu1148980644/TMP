---
title: Sum of Mutated Array Closest to Target
date: 2021-01-04
---
#### Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from arr.

 

```
Example 1:

Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
Example 2:

Input: arr = [2,3,5], target = 10
Output: 5
Example 3:

Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361
```
 

#### Constraints:

- 1 <= arr.length <= 10^4
- 1 <= arr[i], target <= 10^5



#### Solutions

1. ##### binary search


- Use binary search to search for the minimum threshold value that may generate a sumvalue larger than the target value.

```cpp
class Solution {
public:
    int sum(vector<int> & arr, int maxv) {
        int s = 0;
        for (auto n : arr)
            s += min(n, maxv);
        return s;
    }
    int findBestValue(vector<int>& arr, int target) {
        int lo = 1, hi = *max_element(arr.begin(), arr.end());
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (sum(arr, mid) < target)
                lo = mid + 1;
            else
                hi = mid;
        }
        return abs(target - sum(arr, lo)) < abs(target - sum(arr, lo - 1)) ? lo : lo - 1;
    }
};
```



- or also use binary search to speed up summing based on prefix sum.

```cpp
class Solution {
public:

    int sumscore(vector<int> & arr, int * sumarray, int target) {
        int i = 0, j = arr.size();
        while (i < j) {
            int mid = i + (j - i) / 2;
            if (target < arr[mid])
                j = mid;
            else
                i = mid + 1;
        }
        --i;
        if (i < 0)
            return arr.size() * target;
        else
            return sumarray[i] + (arr.size() - i - 1) * target;
    }


    int findBestValue(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        auto diff = [target](int num) {return abs(num - target);};

        int len = arr.size();
        int accum[arr.size()]; accum[0] = arr[0];
        for (int i = 1; i < arr.size(); i++)
            accum[i] = accum[i - 1] + arr[i];

        int lo = min(target / len, arr[0]);
        int hi = arr[len - 1] + 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (sumscore(arr, accum, mid) < target)
                lo = mid + 1;
            else
                hi = mid;
        }

        int sumleft = sumscore(arr, accum, lo - 1);
        int sumright = sumscore(arr, accum, lo);

        return diff(sumleft) <= diff(sumright) ? lo - 1 : lo;
    }
};
```