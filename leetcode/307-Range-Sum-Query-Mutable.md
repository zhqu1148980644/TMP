Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

```
Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
```

#### Note:

-    The array is only modifiable by the update function.
-    You may assume the number of calls to update and sumRange function is distributed evenly.


#### Solutions

1. ##### Fenwick Tree

- Initialization: `O(nlog(n))`
- Update/Query: `O(log(n))`

```c++
struct FenwickTree {
    vector<int> sums;
    FenwickTree(int n) : sums(n + 1) {}

    void update(int i, int delta) {
        while (i < sums.size()) {
            sums[i] += delta;
            i += lowbit(i);
        }
    }

    int query(int i) const {
        int sum = 0;
        while (i > 0) {
            sum += sums[i];
            i -= lowbit(i);
        }
        return sum;
    }

    static inline int lowbit(int x) {
        return x & (-x);
    }
};

class NumArray {
public:
    FenwickTree ft;
    vector<int> nums;

    NumArray(vector<int>& nums) : ft(nums.size()), nums(nums) {
        for (int i = 0; i < nums.size(); i++)
            ft.update(i + 1, nums[i]);
    }
    
    void update(int i, int val) {
        ft.update(i + 1, val - nums[i]);
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        return ft.query(j + 1) - ft.query(i);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
```


2. ##### Segment Tree

- BuildTree: `O(n)`
- Update: `O(log(n))`
- Query: `O(log(n) + k)`
- Segment tree can be used to solve aggregation problems like `min/max..` in a similar way.

```c++
class NumArray {
public:
    struct STNode {
        int start;
        int end;
        int sum;
        STNode * left;
        STNode * right;
        STNode(int start, int end, int sum, STNode * left, STNode * right) :
            start(start), end(end), sum(sum), left(left), right(right) {}
    };

    STNode * tree = nullptr;

    STNode * buildTree(vector<int> & nums, int st, int ed) {
        // buildTree will must return Node with sum data member
        if (st == ed)
            return new STNode(st, ed, nums[st], nullptr, nullptr);
        int mid = st + ((ed - st) >> 1);
        STNode * left = buildTree(nums, st, mid);
        STNode * right = buildTree(nums, mid + 1, ed);
        return new STNode(st, ed, left->sum + right->sum, left, right);    
    }

    int sumQuery(STNode * root, int st, int ed) {
        if (root->start == st && root->end == ed)
            return root->sum;
        int start = root->start, end = root->end;
        int mid = start + ((end - start) >> 1);
        if (ed <= mid)
            return sumQuery(root->left, st, ed);
        else if (st > mid)
            return sumQuery(root->right, st, ed);
        else
            return sumQuery(root->left, st, mid) + sumQuery(root->right, mid + 1, ed);
    }

    void update(STNode * root, int index, int val) {
        if (root->start == root->end && root->start == index)
            root->sum = val;
        else {
            int start = root->start, end = root->end;
            int mid = start + ((end - start) >> 1);
            if (index <= mid)
                update(root->left, index, val);
            else
                update(root->right, index, val);
            root->sum = root->left->sum + root->right->sum;
        }
    }
    
    NumArray(vector<int>& nums) {
        if (nums.size())
            tree = buildTree(nums, 0, nums.size() - 1);
    }
    
    void update(int i, int val) {
        if (tree)
            update(tree, i, val);
    }
    
    int sumRange(int i, int j) {
        return tree ? sumQuery(tree, i, j) : 0;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
```

- Since the tree is a complete binary tree, we can embed the tree into a single array.
- For simplicity, the code below treat the root node as `tree[1]` and `tree[0]` is merely a placeholder.
- Reference: the official answer

```c++
class NumArray {
public:
    int * tree;
    int n;

    NumArray(vector<int>& nums) : n(nums.size()) {
        // complete binary tree has 2*n - 1(when there are no nodes with 1 degree) nodes in total.
        // tree[0] is a placeholder, the root node is tree[1]
        tree = new int[2 * n];
        for (int i = n, j = 0; i < 2 * n; i++, j++)
            tree[i] = nums[j];
        // fill tree in a bottom-up way
        for (int i = n - 1; i > 0; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
    
    void update(int i, int val) {
        i += n;
        tree[i] = val;
        // update tree in a bottom-up way
        while (i > 0) {
            int left = i, right = i;
            // if current node is a left child
            if (i % 2 == 0)
                right = i + 1;
            else
                left = i - 1;
            i /= 2;
            tree[i] = tree[left] + tree[right];
        }
    }

    int sumRange(int l, int r) {
        l += n;
        r += n;
        int sum = 0;
        // when l == r, will do another sum, then only one of l and r will change, thus the loop ends
        while (l <= r) {
            // if l boundary is a right child, plus and jump to parent's next brother in next loop
            if (l % 2 == 1) {
                sum += tree[l];
                l++;
            }
            // if r boundary is a left child, plus and jump to parent's prev brother in next loop
            if (r % 2 == 0) {
                sum += tree[r];
                r--;
            }
            l /= 2;
            r /= 2;
        }

        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
```

3. ##### block sum

```c++

```