Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.
Note:
1 <= k <= n <= 10,000.
Elements of the given array will be in range [-10,000, 10,000].
The answer with the calculation error less than 10-5 will be accepted.

#### Solutions

1. ##### two for loops O(n2)

2. ##### binary search O(nlog(n))

- borrowed from the official answer
- Use binary search to search for the meanvalue.

```c++
class Solution {
public:
    bool greater(vector<int> & nums, double expmean, int k) {
        // diff > 0 means that mean(nums[:k]) > expmean.
        double diff = 0;
        for (int i = 0; i < k; i++)
            diff += nums[i] - expmean;
        
        if (diff >= 0) return true;
        // Why the largest (mindiff, curdiff) is not the answer?
        // It's because that the diff is additive and larger diff with much more numbers may have smaller avg diff, only avg diff matters. This leads back to the original problem, how to find the maximum average value.
        // however, as long as there is a subarray has >=0 diff, we can ensure that the expmean is being underestimated.
        double prediff = 0, mindiff = 0;
        for (int i = k; i < nums.size(); i++) {
            diff += nums[i] - expmean;
            prediff += nums[i - k] - expmean;
            mindiff = min(mindiff, prediff);
            if (diff > mindiff)
                return true;
        }
        return false;

    }
    double findMaxAverage(vector<int>& nums, int k) {
        double minv = INT_MAX, maxv = INT_MIN;
        for (double n : nums) {
            minv = min(minv, n);
            maxv = max(maxv, n);
        }

        while (maxv - minv > 1e-5) {
            double mid = minv + (maxv - minv) / 2;
            if (greater(nums, mid, k))
                minv = mid;
            else
                maxv = mid;
        }

        return minv;
    }
};
```
