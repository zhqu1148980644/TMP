#### Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

```
Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5

Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
```

#### Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.

#### Solutions

1. ##### brute force  O(nlog(n))  S(1)

- sorting

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
```

2. ##### quick sort based partition  O(n) S(1)

- time complexity: O(n) + O(n/2) + O(n/4)... worst case: O(n2)

```c++
#include <experimental/random>
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // k largest equals to size - k smallest
        k = nums.size() - k;
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            // use random to prevent deterioration of complexity to O(n2)
            swap(nums[lo], nums[std::experimental::randint(lo, hi)]);
            // be carefull, the pivot is not nums[0]
            int pivot = nums[lo];
            int i = lo, j = hi;
            while (i < j) {
                while (i < j && nums[j] >= pivot) j--;
                nums[i] = nums[j];
                while (i < j && nums[i] <= pivot) i++;
                nums[j] = nums[i];
            }
            nums[i] = pivot;
            // you can also check if i equals k
            if (i <= k) lo = i + 1;
            if (i >= k) hi = i - 1;
        }

        return nums[k];
    }
};
```


3. ##### heap O(n) + nlog(k)  S(k)

- Maintaing a min heap with k largest elements.
- Other heap based selection algorithm also works.

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>>  heap;
        for (int i = 0; i < k; i++)
            heap.push(nums[i]);
        for (int i = k; i < nums.size(); i++) {
            heap.push(nums[i]);
            heap.pop();
        }

        return heap.top();
    }
};
```

Or a manually built heap.

```c++

```

4. #### bucket sort O(n) S(max - min + 1)

- reference: https://leetcode-cn.com/problems/kth-largest-element-in-an-array/comments/105522

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        auto min_max = minmax_element(nums.begin(), nums.end());
        int min = *min_max.first, max = *min_max.second;
        vector<int> bucket(max - min + 1, 0);
        for (auto & num : nums)
            bucket[num - min]++;
        int count = 0;
        for (int i = max - min; i >= 0; i--) {
            count += bucket[i];
            if (count >= k)
                return min + i;
        }
        return -1;
    }
};
```

5. ##### Iteratively remove the smallest element  O(kn) S(k)

- reference: https://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/
- The complexity equals to iteratively find the largest element k times.

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        vector<int> store(nums.begin(), nums.begin() + k);
        auto pmin =  min_element(store.begin(), store.end());

        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > *pmin) {
                *pmin = nums[i];
                pmin = min_element(store.begin(), store.end());
            }
        }
        return *pmin;
    }
};
```

6. ##### introselect



7. ##### binary search

- Speculate the target number in the range of 32bit interger by counting the number of elements slower than it. For the target k'th larget number, numbers in the array <= it should be at least k.

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if (k > nums.size()) return -1;
        k = nums.size() - k + 1;
        long lo = INT_MIN, hi = INT_MAX;
        while (lo < hi) {
            long mid = lo + ((hi - lo) >> 1);
            int less = 0;
            for (auto n : nums) less += n <= mid;
            // for the target, numbers less(<=) should be at least k(may have duplicates).
            // if not satisfy, we can ensure the target is at least mid + 1
            if (less < k)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
};
```