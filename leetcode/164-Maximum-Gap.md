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
        if (nums.size() < 2) return 0;
        int maxval = *max_element(nums.begin(), nums.end());
        int exp = 1, radix = 10;
        // use virtual 1d buckets
        // buckets are represented as continuous regions in the array.
        vector<int> sorted(nums.size());
        // sort by the last(least significant) digit to the first(most significant) digit.
        while (maxval / exp > 0) {
            vector<int> count(radix, 0);
            for (auto n : nums)
                count[(n / exp) % 10]++;
            for (int i = 1; i < count.size(); i++)
                count[i] += count[i - 1];
            // must start from the back, otherwise the order sorted in the last step will be reversed
            for (int i = nums.size() - 1; i >= 0; i--)
                sorted[--count[(nums[i] / exp) % 10]] = nums[i];
            swap(nums, sorted);
            exp *= 10;
        }

        int maxgap = 0;
        for (int i = 0; i < (int)nums.size() - 1; i++)
            maxgap = max(maxgap, nums[i + 1] - nums[i]);
        
        return maxgap;
    }
};

```

3. ##### bucket

- Similar to bucket sort.
- When n items are putted into `m(m < n)` buckets, there must be at least one bucket contains more than one item.
- In this problem, buckets can be seen as intervals with the same width equally layed out in `[min, max)`, thus each item can be putted into buckets based on which interval the item belongs to. Afther all items are putted correctly, values in the `(i - 1)'th` bucket is smaller than the `i'th` bucket.
- The maxinum interval can be find by seaching for the maximum interval between two ajacent non-empty buckets.
    - ie. the minimum number in the current bucket deduct the maximum number in the first non-empty bucket afterwards. 
    - Proof of correctness: `maxgap >= (w = (hi - lo) / (n - 1))`, `w` is the average interval of all adjaccent nodes, this eq means that the boundary of the mapgap must be within two diffenrent buckets, and all buckest between these two buckests are empty.
    - `maxpgap == w` is true only when all nodes are evenly separated.
- Instead of creating buckets to collect items, we can simply use two arrays to record the minimum and maximum number in each bucket.

```c++
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) return 0;
        auto mm = minmax_element(nums.begin(), nums.end());
        int minn = *mm.first, maxn = *mm.second;
        int gap = max(1ul, (maxn - minn) / (nums.size() - 1));
        int numb = (maxn - minn) / gap + 1;
        // record the minimum and maximum number in each interval
        vector<int> bmin(numb, INT_MAX), bmax(numb, INT_MIN);
        for (auto n : nums) {
            int bi = (n - minn) / gap;
            bmin[bi] = min(bmin[bi], n);
            bmax[bi] = max(bmax[bi], n);
        }
        // find the maximum gap between numbers in two nonempty intervals
        int i = 0, j = 1, maxgap = 0;
        while (j < numb) {
            // may has multiple empty intervals between two nonempty intervals 
            while (j < numb && bmin[j] == INT_MAX) j++;
            if (j < numb) {
                maxgap = max(maxgap, bmin[j] - bmax[i]);
                i = j++;
            }
        }

        return maxgap;
    }
};
```