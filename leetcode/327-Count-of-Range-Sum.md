Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:

Input: nums = [-2,5,-1], lower = -2, upper = 2,
Output: 3 
Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.


#### Solutions

- check `problem 493`

1. ##### binary index tree

- Find the number of range sums lies in `[lower, upper]` equals to find the number of prefix sum has been inserted before with value lies in `[curprefixsum - upper, curprefixsum - lower]`.
- use binary search to find the index within the sorted array. `O(6nlog(n))`

```c++
struct FenwickTree {
    vector<int> sums;
    FenwickTree(int size) : sums(size + 1) {}
    void update(int n, int delta) {
        while (n < sums.size()) {
            sums[n] += delta;
            n += lowbit(n);
        }
    }
    int query(int n) {
        int sum = 0;
        while (n > 0) {
            sum += sums[n];
            n -= lowbit(n);
        }
        return sum;
    }
    inline int lowbit(int x) {
        return x & (-x);
    }
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> presum(nums.size() + 1);
        // must insert zero as the begin of presum
        vector<long> sortedsum(nums.size() + 1);
        long sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sortedsum[i + 1] = presum[i + 1] = sum += nums[i];

        sort(sortedsum.begin(), sortedsum.end());
        sortedsum.erase(unique(sortedsum.begin(), sortedsum.end()), sortedsum.end());
        FenwickTree ft(sortedsum.size());
        int res = 0;
        for (auto psum : presum) {
            int ed = upper_bound(sortedsum.begin(), sortedsum.end(), psum - lower) - sortedsum.begin() - 1;
            int st = lower_bound(sortedsum.begin(), sortedsum.end(), psum - upper) - sortedsum.begin();
            // here the st should not be queried.
            res += ft.query(ed + 1) - ft.query(st);
            ft.update(lower_bound(sortedsum.begin(), sortedsum.end(), psum) - sortedsum.begin() + 1, 1);
        }
        return res;
    }
};
```

- Or map items to index.

```c++
struct FenwickTree {
    vector<int> sums;
    FenwickTree(int size) : sums(size + 1) {}
    void update(int n, int delta) {
        while (n < sums.size()) {
            sums[n] += delta;
            n += lowbit(n);
        }
    }
    int query(int n) {
        int sum = 0;
        while (n > 0) {
            sum += sums[n];
            n -= lowbit(n);
        }
        return sum;
    }
    inline int lowbit(int x) {
        return x & (-x);
    }
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> presum(nums.size() + 1);
        // must insert zero as the begin of presum
        vector<long> sortedsum = {0};
        sortedsum.reserve(3 * nums.size());
        long sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            presum[i + 1] = sum += nums[i];
            sortedsum.push_back(sum);
            sortedsum.push_back(sum - (long)lower);
            sortedsum.push_back(sum - (long)upper - 1);
        }
        // map items to index int sorted array
        sort(sortedsum.begin(), sortedsum.end());
        unordered_map<long, int> indexes;
        int i = 0;
        for (auto p : sortedsum)
            if (!indexes.count(p))
                indexes[p] = i++;

        FenwickTree ft(indexes.size());
        int res = 0;
        for (auto psum : presum) {
            res += ft.query(indexes[psum - lower] + 1) 
                - ft.query(indexes[psum - upper - 1] + 1);
            ft.update(indexes[psum] + 1, 1);
        }

        return res;
    }
};
```


2. ##### segment tree

```c++
class Solution {
public:
    int n;
    vector<int> tree;
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> presum(nums.size() + 1);
        // must insert zero as the begin of presum
        vector<long> sortedsum(nums.size() + 1);
        long sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sortedsum[i + 1] = presum[i + 1] = sum += nums[i];

        sort(sortedsum.begin(), sortedsum.end());
        sortedsum.erase(unique(sortedsum.begin(), sortedsum.end()), sortedsum.end());
        n = sortedsum.size();
        tree = vector<int>(2 * sortedsum.size());

        int res = 0;
        for (auto psum : presum) {
            int ed = upper_bound(sortedsum.begin(), sortedsum.end(), psum - lower) - sortedsum.begin() - 1;
            int st = lower_bound(sortedsum.begin(), sortedsum.end(), psum - upper) - sortedsum.begin();
            res += query(st, ed);
            update(lower_bound(sortedsum.begin(), sortedsum.end(), psum) - sortedsum.begin(), 1);
        }
        return res;
    }
    void update(int i, int val) {
        i += n;
        tree[i] += val;
        while (i > 0) {
            int left = i, right = i;
            if (i % 2)
                left = i - 1;
            else
                right = i + 1;
            i /= 2;
            tree[i] = tree[left] + tree[right];
        }
    }
    int query(int l, int r) {
        l += n; r += n;
        int sum = 0;
        while (l <= r) {
            if (l % 2)
                sum += tree[l++];
            if (r % 2 == 0) 
                sum += tree[r--];
            l /= 2; r /= 2;
        }
        return sum;
    }
};
```



3. ##### binary search tree O(nlog(n))

- `distance` function in `STL` costs `O(n)` time. Thus the time complexity is actually `O(n2)`. However, a home made avl/rbtree can achieve `O(1)` complexity for computing the distance between two nodes.

```c++
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        multiset<long> s;
        s.insert(0);
        long sum = 0; int res = 0;
        for (auto num : nums) {
            sum += num;
            res += distance(s.lower_bound(sum - upper), s.upper_bound(sum - lower));
            s.insert(sum);
        }
        return res;
    }
};
```

4. #####  merge sort O(nlog(n))

```c++
class Solution {
public:
    vector<long> tmp;
    int lower, upper, res = 0;
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        this->lower = lower, this->upper = upper;
        vector<long> presum(nums.size() + 1);
        long sum = 0;
        for (int i = 0; i < nums.size(); i++)
            presum[i + 1] = sum += nums[i];
        
        tmp = vector<long>(presum.size() / 2 + 1);
        merge_sort(presum, 0, presum.size());
        return res;
    }
    void merge_sort(vector<long> & nums, int lo, int hi) {
        if (hi - lo < 2)
            return;
        int mid = lo + ((hi - lo) >> 1);
        merge_sort(nums, lo, mid);
        merge_sort(nums, mid, hi);
        int i = lo, l = mid, r = mid;

        while (i < mid) {
            while (l < hi && nums[l] - nums[i] < lower)
                l++;
            while (r < hi && nums[r] - nums[i] <= upper)
                r++;
            res += r - l;
            i++;
        }
        merge(nums, lo, mid, hi);
    }
    void merge(vector<long> & nums, int lo, int mid, int hi) {
        int leni = mid - lo;
        for (int i = 0; i < leni; i++)
            tmp[i] = nums[lo + i];
        int w = lo, i = 0, j = mid;
        while (i < leni && j < hi) {
            if (nums[j] < tmp[i])
                nums[w++] = nums[j++];
            else
                nums[w++] = tmp[i++];
        }
        while (i < leni)
            nums[w++] = tmp[i++];
    }
};
```