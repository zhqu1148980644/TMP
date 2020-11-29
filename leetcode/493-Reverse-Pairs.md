Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].

You need to return the number of important reverse pairs in the given array.

Example1:

Input: [1,3,2,3,1]
Output: 2
Example2:

Input: [2,4,3,5,1]
Output: 3
Note:
The length of the given array will not exceed 50,000.
All the numbers in the input array are in the range of 32-bit integer.


#### Solutions

- Check `problem 315`


1. ##### binary search tree wort O(n2) avg O(nlog(n))

- Time limit exceed.

```c++
struct Node {
    int val, cnt = 1;
    Node * left = 0, * right = 0;
    Node (int val) : val(val) {}
};
class Solution {
public:
    Node * root = nullptr;
    int search(Node * root, long val) {
        if (!root)
            return 0;
        else if (val == root->val)
            return root->cnt;
        else if (val < root->val)
            return root->cnt + search(root->left, val);
        else
            return search(root->right, val);
    }
    Node * insert(Node * root, int val) {
        if (!root)
            return new Node(val);
        else if (val == root->val)
            root->cnt++;
        else if (val < root->val)
            root->left = insert(root->left, val);
        else {
            root->cnt++;
            root->right = insert(root->right, val);
        }
        return root;
    }
    int reversePairs(vector<int>& nums) {
        int len = nums.size(), res = 0;
        
        for (int i = 0; i < len; i++) {
            res += search(root, 2 * nums[i] + 1);
            root = insert(root, nums[i]);
        }
        return res;
    }
};
```

2. ##### merge sort

```c++
class Solution {
public:
    int res = 0;
    vector<int> tmp; // a tmporary array used for storing the first half of array when merging
    int reversePairs(vector<int>& nums) {
        tmp = vector<int>(nums.size() / 2 + 1);
        merge_sort(nums, 0, nums.size());
        return res;
    }
    void merge_sort(vector<int> & nums, int lo, int hi) {
        if (hi - lo < 2)
            return;
        int mid = lo + ((hi - lo) >> 1);
        merge_sort(nums, lo, mid);
        merge_sort(nums, mid, hi);
        int j = mid;
        // could count in merge function, though it would be much more complicated
        for (int i = lo; i < mid; i++) {
            while (j < hi && nums[i] > 2l * nums[j]) j++;
            res += j - mid;
        }
        merge(nums, lo, mid, hi);
    }
    void merge(vector<int> & nums, int lo, int mid, int hi) {
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


3. ##### binary index tree

- Since we need to count the number of reverse pairs with `i > 2 * j`. Inserting elements from the start of the array would not be possible(Traditional binary index tree can only query prefix sum). (see https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22 for details)
- If we choose to insert elements backwards, the query parameter should be changed to `nums[i] / 2`.
- Unlike `problem 315`, the queried numbers would not always be within the original array, instead of using a hashset to record the indexes of all elements, we can use binary search to find the index of a given number even if it doestn't exist.

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
    static inline int lowbit(int x) {
        return x & (-x);
    }
};

class Solution {
public:
    int index(vector<int> & nums, double target) {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            // lower bound
            if (target > nums[mid])
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
    int reversePairs(vector<int>& nums) {
        vector<int> clone(nums);
        sort(clone.begin(), clone.end());
        int res = 0;
        FenwickTree ft(clone.size());
        for (int i = nums.size() - 1; i >= 0; i--) {
            // Here comes the trick. the returned index would be of the first greater/equal number(lower bound).
            // if num[i] / 2 exist in the original array, return the index of that number, then the query would not include that number.
            // if num[i] / 2 does not exist, return the index of the first greater one, then the query again would not include it.
            // in both cases, the requirements i > 2 * j is satisfied.
            int tmp = ft.query(index(clone, ((double)nums[i] / 2)));
            res += tmp;
            ft.update(index(clone, nums[i]) + 1, 1);
        }
        return res;
    }
};
```


or


```c++
struct FenwickTree {
    vector<int> sums;
    FenwickTree(int num) : sums(num + 1) {}
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

    static inline int lowbit(int n) {
        return n & -n;
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        // long long for handling 2 * n > INT_MAX
        vector<long long> sorted(nums.size());
        for (int i = 0; i < nums.size(); i++)
            sorted[i] = nums[i];
        sort(sorted.begin(), sorted.end());
        // add index by 1 to cater for the requirement for FenwickTree
        auto index = [&](long long n) {
            return lower_bound(sorted.begin(), sorted.end(), n) - sorted.begin() + 1;
        };
        int res = 0;
        int ftsize = nums.size() + 1;
        FenwickTree ft(ftsize);
        for (auto n : nums) {
            // search lowerbound index of 2 * n + 1
            int min_index = index(2ll * n + 1);
            res += ft.query(ftsize) - ft.query(min_index - 1);
            ft.update(index(n), 1);
        }

        return res;
    }
};
```

4. ##### segment tree

```c++
class Solution {
public:
    int n;
    vector<int> tree;
    int reversePairs(vector<int>& nums) {
        vector<int> clone(nums);
        sort(clone.begin(), clone.end());
        n = nums.size();
        tree = vector<int>(2 * nums.size());

        int res = 0;
        for (int i = nums.size() - 1; i >= 0; i--) {
            // only count numbers smaller than ceil(nums[i] / 2)
            res += query(0, index(clone, (double)nums[i] / 2) - 1);
            update(index(clone, nums[i]), 1);
        }
        return res;
    }
    int index(vector<int> & nums, double target) {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (target > nums[mid])
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
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