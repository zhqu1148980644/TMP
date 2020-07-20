#### Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

#### Note:
If n is the length of array, assume the following constraints are satisfied:

-    1 ≤ n ≤ 1000
-    1 ≤ m ≤ min(50, n)

```
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18
```

#### Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.

#### Solutions

1. ##### binary search O(nlog(sum - max))

- Use binary search to find the largest sum among these m subarrays.
- To determine the shrinking direction, we count the number of subarrays denoted as `n` with lagest sum smaller than or equal to `mid(largest sum)` amongst these `n` subarrays. ie, Suppose `mid(larget sum)` is the answer, how many subarrays will be splited.
    - If `n > m`, `mid` must be underestimated, thus we search in the upper range `[mid + 1, hi]`.
    - Else search in `[lo, mid]`

```c++
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int maxe = nums[0];
        long sum = 0;
        for (auto & num : nums) {
            maxe = max(maxe, num);
            sum += num;
        }

        long lo = maxe, hi = sum;
        while (lo < hi) {
            long mid = lo + ((hi - lo) >> 1);
            int count = 1;
            long s = 0;
            for (auto & num : nums) {
                s += num;
                // make sure every subarrays satisfy the requirements. i.e. will not be greater than mid.
                if (s > mid) {
                    s = num;
                    count++;
                }
            }
            if (count > m)
                lo = mid + 1;
            else
                hi = mid;
        }

        return lo;
    }
};
```

2. ##### dynamic programming

- `dp[j][k]` represents the last subarray sum when `array[:j]` has been divided into `k` parts.
- `j` is 0-based.

```c++
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int len = nums.size();
        vector<vector<long>> dp(len, vector<long>(m + 1, INT_MAX));
        dp[0][1] = nums[0];
        for (int i = 1; i < len; i++)
            dp[i][1] = dp[i - 1][1] + nums[i];
        
        for (int j = 1; j < len; j++)
            for (int k = min(m, j + 1); k > 1; k--)
                for (int i = j - 1; i >= 0; i--)
                    dp[j][k] = min(dp[j][k], max(dp[i][k - 1], dp[j][1] - dp[i][1]));
        
        return dp[len - 1][m];
    }
};
```

- Or we can just use a 1-d array by filling the dp table column by column.

```c++
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int len = nums.size();
        vector<long> sums(len); sums[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
            sums[i] = sums[i - 1] + nums[i];
        
        vector<long> dp(sums);

        for (int k = 2; k <= m; k++)
            for (int j = len - 1; j >= k - 1; j--) {
                long minsum = INT_MAX;
                for (int i = j - 1; i >= 0; i--)
                    minsum = min(minsum, max(dp[i], sums[j] - sums[i]));
                dp[j] = minsum;
            }
        
        return dp[len - 1];
    }
};
```