---
title: Sort an Array
date: 2021-01-04
---
#### Given an array of integers nums, sort the array in ascending order.



```
Example 1:

Input: nums = [5,2,3,1]
Output: [1,2,3,5]

Example 2:

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
```

 

#### Constraints:

    1 <= nums.length <= 50000
    -50000 <= nums[i] <= 50000


#### Solutions

1. ##### sort

- stable: the order of elements with the same value are reserved as their initial order.
- adaptable: the method should run faster in cases when parts of elements are already sorted.

- bubble sort: `O(n2) S(1) stable adaptable`
    - iteratively reversing reversed pairs.
- selection sort: `O(n2) S(1) stable inadaptable`
    - iteratively put the maximum/minimum element at the front/back of the sorted suffix/prefix.
- Inertion sort: `O(n2) S(1) stable adaptable`
    - Maintaining a sorted prefix and insert elements at the right position of the sorted array.
- Shell sort: `worst O(n ** 4/3) S(1) unstable adaptable`
    - Insersion sort multiple subgroups.
- merge sort: `O(nlog(n)) S(n) stable inadaptable`
    - Bipartition the array into small arrays then merge these sorted arrays into larger array till the whole array is merged.
- quick sort: `O(nlog(n)) S(1) unstable inadaptable`
    - Recursively put a random element at the right position util all elements are positioned correctly.
- heap sort: `O(nlog(n)) S(1) untable inadaptable`
    - Use heap to find the smallest/largest element and accumulate sorted array in a manner similar to selection sort.
- bucket sort/count sort: `O(n) S(n) stable inadaptable`
    - Map elements to naturally sorted indexes.

```cpp
#include <experimental/random>
class Solution {
public:
    void bubble_sort(vector<int> & nums, int lo, int hi) {
        int start = lo;
        while (lo < hi) {
            int last = lo;
            while (++lo < hi) {
                if (nums[lo] < nums[lo - 1]) {
                    last = lo;
                    swap(nums[lo], nums[lo - 1]);
                }
            }
            hi = last;
            lo = start;
        }
    }
    
    void selection_sort(vector<int> & nums, int lo, int hi) {
        while (lo < hi) {
            // find the maximum one
            int maxi = lo;
            for (int i = 0; i < hi; i++)
                if (nums[i] >= nums[maxi])
                    maxi = i;
            // concatinate at the front of sorted tail
            swap(nums[--hi], nums[maxi]);
        }
    }

    void selection_sort_stable(vector<int> & nums, int lo, int hi) {
        while (lo < hi) {
            int maxi = lo;
            for (int i = 0; i < hi; i++)
                if (nums[i] >= nums[maxi])
                    maxi = i;
            int maxe = nums[maxi];
            // move unsorted items after maxe one step leftwards
            for (int i = maxi; i < hi - 1; i++)
                nums[i] = nums[i + 1];
            nums[--hi] = maxe;
        }
    }

    void insertion_sort(vector<int> & nums, int lo, int hi) {
        // binary search for the insertion pos
        // or use lower_bound
        auto binary_search = [&](int lo, int hi, int target) {
            if (target >= nums[hi])
                return hi + 1;
            while (lo < hi) {
                int mid = lo + ((hi - lo) >> 1);
                if (nums[mid] < target)
                    lo = mid + 1;
                else
                    hi = mid;
            }
            return lo;
        };
        int start = lo++;
        while (lo < hi) {
            int cur = nums[lo];
            size_t pos = binary_search(start, lo - 1, cur);
            // move sorted items after insertion point one step rightwards
            for (int i = lo; i > pos; i--)
                nums[i] = nums[i - 1];
            nums[pos] =  cur;
            lo++;
        }
    }

    void shell_sort(vector<int> & nums, int lo, int hi) {
        // 1 2 4 8 16                 worst O(n2)
        // for (int gap = hi - lo; gap > 0; gap /= 2) {
        //     for (int j = lo + gap; j < hi; j++)
        //         for (int i = j; i - gap >= 0 && nums[i - gap] > nums[i]; i -= gap)
        //             swap(nums[i - gap], nums[i]);
        // }

        /// 1 3 7 15 31              worst(n ** 3/2)
        int gap = 1;
        while (gap < (hi - lo) / 3)
            gap = gap * 3 + 1;
        while (gap) {
            for (int j = lo + gap; j < hi; j++)
                for (int i = j; i - gap >= 0 && nums[i - gap] > nums[i]; i -= gap)
                    swap(nums[i - gap], nums[i]);
            gap /= 3;
        }
    }

    void merge(vector<int> & nums, int lo, int mid, int hi) {
        int lenb = mid - lo;
        // use a temporary space to store the first part.
        int * tmp = new int[lenb];
        for (int i = 0; i < lenb; i++)
            tmp[i] = nums[lo + i];
        int w = lo, i = 0, j = mid, maxj = hi;
        // Another way
        // while (i < lenb) {
        //     if (j < maxj && nums[j] < tmp[i])
        //         nums[w++] = nums[j++];
        //     if (j >= maxj || nums[j] >= tmp[i])
        //         nums[w++] = tmp[i++];
        // }
        while (i < lenb && j < maxj)
            nums[w++] = nums[j] < tmp[i] ? nums[j++] : tmp[i++];
        while (i < lenb)
            nums[w++] = tmp[i++];

        delete [] tmp;
    }

    void merge_sort(vector<int> & nums, int lo, int hi) {
        if (hi - lo < 2)
            return;
        int mid = lo + ((hi - lo) >> 1);
        // sort left part
        merge_sort(nums, lo, mid);
        // sort right part
        merge_sort(nums, mid, hi);
        // merge these two sorted parts
        merge(nums, lo, mid, hi);
    }

    void quick_sort2(vector<int> & nums, int lo, int hi) {
        // Invariance: 
        // nums[start:i) <= pivot <= nums(j:end]  end = hi - 1
        if (hi - lo < 2)
            return;
        int i = lo, j = hi - 1;
        swap(nums[i], nums[std::experimental::randint(i, j)]);
        int pivot = nums[i];
        while (i < j) {
            while (i < j && nums[j] >= pivot) j--;
            nums[i] = nums[j];
            while (i < j && nums[i] <= pivot) i++;
            nums[j] = nums[i];
        }

        nums[i] = pivot;
        quick_sort2(nums, lo, i);
        quick_sort2(nums, i + 1, hi);
    }

    void quick_sort(vector<int> & nums, int lo, int hi) {
        // the first version will swap too often if the pivot contains multiple duplicates.
        // In this version, we maintain three regions: Invariance:
        // nums[start:i) < pivot < nums(j:end]  end = hi - 1
        // nums[i:cur) == pivot
        if (hi - lo < 2)
            return;
        int i = lo, cur = lo, j = hi - 1;
        swap(nums[i], nums[std::experimental::randint(i, j)]);
        int pivot = nums[i];
        // Cautious. We need to visit cur after switched with j.
        while (cur <= j) {
            if (nums[cur] < pivot)
                swap(nums[i++], nums[cur++]);
            else if (nums[cur] > pivot)
                swap(nums[j--], nums[cur]);
            else
                cur++;
        }
        // Cautious, we can ignore the duplicate region.
        quick_sort(nums, lo, i);
        quick_sort(nums, cur, hi);
    }

    void percolate_down(vector<int> & nums, int lo, int hi, int cur) {
        int curnum = nums[cur];
        while (cur < hi) {
            int max = curnum, maxi = cur;
            int lc = 2 * cur + 1, rc = 2 * cur + 2;
            if (lc < hi && nums[lc] > max)
                max = nums[maxi = lc];
            if (rc < hi && nums[rc] > max)
                max = nums[maxi = rc];
            if (maxi != cur) {
                nums[cur] = max;
                cur = maxi;
            }
            else {
                nums[cur] = curnum;
                break;
            }
        }
    }

    void heapify(vector<int> & nums, int lo, int hi) {
        // O(n)
        for (int i = hi - 1; i >= lo; i--) {
            percolate_down(nums, lo, hi, i);
        }
    }

    void heap_sort(vector<int> & nums, int lo, int hi) {
        // O(n)
        heapify(nums, lo, hi);
        int front = hi - 1;
        // O(nlog(n))
        while (front) {
            swap(nums[0], nums[front]);
            percolate_down(nums, lo, front--, 0);
        }
    }


    void count_sort(vector<int> & nums, int lo, int hi) {
        auto minmax = minmax_element(nums.begin() + lo, nums.begin() + hi);
        int min = *minmax.first, max = *minmax.second;
        int buckets[max - min + 1];
        memset(buckets, 0, (max - min + 1) * sizeof(int));
        for (int i = lo; i < hi; i++)
            buckets[nums[i] - min]++;
        for (int i = 0; i < max - min + 1; i++) {
            while (buckets[i]-- > 0)
                nums[lo++] = i + min;
        }
    }

    void bucket_sort(vector<int> & nums, int lo, int hi, int n) {
        vector<vector<int>> buckets(n, vector<int>());
        auto mm = minmax_element(nums.begin() + lo, nums.begin() + hi);
        int min = *mm.first, max = *mm.second;
        int step = (max - min + 1) / n + 1;
        for (int i = lo; i < hi; i++) {
            int cur = nums[i];
            auto & bucket = buckets[(cur - min) / step];
            bucket.push_back(cur);
            if (buckets.size() < 2) continue;
            int j = bucket.size() - 2;
            while (j >= 0 && bucket[j] > cur) {
                bucket[j + 1] = bucket[j];
                j--;
            }
            // cautious, it's j + 1 not j
            bucket[j + 1] = cur;
        }
        for (auto & bucket : buckets)
            for (auto n : bucket)
                nums[lo++] = n;
    }

    vector<int> sortArray(vector<int>& nums) {
        // bubble_sort(nums, 0, nums.size());
        // selection_sort(nums, 0, nums.size());
        // selection_sort_stable(nums, 0, nums.size());
        // insertion_sort(nums, 0, nums.size());
        // shell_sort(nums, 0, nums.size());
        // merge_sort(nums, 0, nums.size());
        // quick_sort2(nums, 0, nums.size());
        // quick_sort(nums, 0, nums.size());
        // heap_sort(nums, 0, nums.size());
        // bucket_sort(nums, 0, nums.size(), 1000);
        count_sort(nums, 0, nums.size());
        return nums;
    }
};
```