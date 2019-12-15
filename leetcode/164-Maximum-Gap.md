#### Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Return 0 if the array contains less than 2 elements.

```
Example 1:

Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
```

#### Note:

- You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
- Try to solve it in linear time/space.


#### Solutions

1. ##### sort O(nlog(n))

```c++
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        sort(nums.begin(), nums.end());
        int maxd  = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] - nums[i - 1] > maxd)
                maxd = nums[i] - nums[i - 1];
        }
        return maxd;
    }
};
```


2. ##### raidix sort O(n) S(n)

```c++
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.empty() || nums.size() < 2) return 0;
        int maxVal  = *max_element(nums.begin(), nums.end());

        int exp = 1;
        int radix = 10;

        vector<int> aux(nums.size());

        while (maxVal / exp > 0) {
            vector<int> count(radix, 0);
            for (int i = 0; i < nums.size(); i++)
                count[(nums[i] / exp) % 10]++;

            for (int i = 1; i < count.size(); i++)
                count[i] += count[i - 1];

            for (int i = nums.size() - 1; i >= 0; i--)
                aux[--count[(nums[i] / exp) % 10]] = nums[i];

            for (int i = 0; i < nums.size(); i++)
                nums[i] = aux[i];

            exp *= 10;
        }

        int maxGap = 0;
        for (int i = 0; i < nums.size() - 1; i++)
            maxGap = max(nums[i + 1] - nums[i], maxGap);
        return maxGap;
    }
};
```

3. ##### bucket

- Similar to bucket sort.
- When n items are putted into `m(m < n)` buckets, there must be at least one bucket contains more than one item.
- In this problem, buckets can be sesed as intervals with the same width equally layed out in `[min, max)`, thus each item can be putted in to buckets base on which interval the item belongs to.
- The complexity of the sorting problem reduces to O(n).
    - ie. values in the `(i - 1)'th` bucket is smaller than the `i'th` bucket.
- The maxinum interval can be find by seaching for the maximum interval between two ajacent non-empty buckets.
    - ie. the minimum number in the current bucket deduct the maximum number in the last bucket.
- Instead of creating buckets to collect items, we can simply use two arrays to record the minimum and maximum number in each bucket.

```c++
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        auto mm = minmax_element(nums.begin(), nums.end());
        int mi = *mm.first, ma = *mm.second;
        int gap = (ma - mi) / (nums.size() - 1);
        gap = gap < 1 ? 1 : gap;
        int m = (ma - mi) / gap + 1;
        // bmin contain the minimum number droped into each bucket.
        // bmax contain the maximum number dropped into each bucket.
        vector<int> bmin(m, INT_MAX);
        vector<int> bmax(m, INT_MIN);
        for (auto num : nums) {
            int bi = (num - mi) / gap;
            if (num < bmin[bi]) bmin[bi] = num;
            if (num > bmax[bi]) bmax[bi] = num;
        }
        int i = 0, j = 1, maxd = 0;
        while (j < m) {
            // Some buckets may contain no items.
            while (j < m && bmin[j] == INT_MAX) j++;
            if (j < m) {
                maxd = max(maxd, bmin[j] - bmax[i]);
                i = j++;
            }
        }
        return maxd;
    }
};
```