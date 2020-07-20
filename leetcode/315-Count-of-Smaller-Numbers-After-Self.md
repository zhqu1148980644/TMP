You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0] 
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

#### Solutions

- reference: https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22
- similar to `problem 493` and `面试题51-数组中的逆序对`

1. ##### count in merge sort O(nlog(n))

```c++
class Solution {
public:
    vector<int> res;
    vector<int> indexes;
    vector<int> tmp; // a tmporary array used for storing the first half of array when merging
    vector<int> countSmaller(vector<int>& nums) {
        tmp = vector<int>(nums.size() / 2);
        indexes = vector<int>(nums.size());
        iota(indexes.begin(), indexes.end(), 0);
        res = vector<int>(nums.size());
        merge_sort(nums, 0, nums.size());
    
        return res;
    }
    void merge_sort(vector<int> & nums, int lo, int hi) {
        if (hi - lo < 2)
            return;
        int mid = lo + ((hi - lo) >> 1);
        merge_sort(nums, lo, mid);
        merge_sort(nums, mid, hi);
        // pre-exit
        if (nums[indexes[mid]] < nums[indexes[mid - 1]])
            merge(nums, lo, mid, hi);
    }
    void merge(vector<int> & nums, int lo, int mid, int hi) {
        int leni = mid - lo;
        for (int i = 0; i < leni; i++)
            tmp[i] = indexes[lo + i];
        int w = lo, i = 0, j = mid;
        while (i < leni && j < hi) {
            if (nums[indexes[j]] < nums[tmp[i]])
                indexes[w++] = indexes[j++];
            else {
                // is not w - lo
                res[tmp[i]] += j - mid;
                indexes[w++] = tmp[i++];
            }
        }
        while (i < leni) {
            res[tmp[i]] += j - mid;
            indexes[w++] = tmp[i++];
        }
    }
};
```


2. ##### FenwickTree O(2nlog(n))

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
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> clone(nums);
        // or just use a treemap 
        sort(clone.begin(), clone.end());
        unordered_map<int, int> m;
        int i = 0;
        for (auto n : clone) 
            if (!m.count(n))
                m[n] = i++;

        FenwickTree ft(m.size());
        vector<int> res(nums.size());
        for (int i = nums.size() - 1; i >= 0; i--) {
            // caution, count the number of nums slower than self, self's index is m[nums[i]] + 1
            res[i] = ft.query(m[nums[i]]);
            ft.update(m[nums[i]] + 1, 1);
        }

        return res;
    }
};
```

3. ##### segment tree

- Array version

```c++
class Solution {
public:
    int n;
    vector<int> tree;
    vector<int> countSmaller(vector<int>& nums) {
        // discretization, map num to index(in sorted array)
        vector<int> clone(nums);
        sort(clone.begin(), clone.end());
        int i = 0;
        unordered_map<int, int> m;
        for (auto n : clone)
            if (!m.count(n))
                m[n] = i++;
        // build empty tree
        n = m.size();
        tree = vector<int>(2 * n);

        vector<int> res(nums.size());
        for (int i = nums.size() - 1; i >= 0; i--) {
            // only count numbers smaller than self
            res[i] = query(0, m[nums[i]] - 1);
            update(m[nums[i]], 1);
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

4. ##### binary search tree avg O(nlog(n)) worst O(n2)

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
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res(nums.size());
        int len = nums.size();
        for (int i = len - 1; i >= 0; i--) {
            // num of inserted nodes minus the num of nodes with gt/eq val
            res[i] = len - i - 1 - search(root, nums[i]);
            root = insert(root, nums[i]);
        }
        return res;
    }
};
```
