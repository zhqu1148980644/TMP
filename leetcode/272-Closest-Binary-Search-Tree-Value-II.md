Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Example:

Input: root = [4,2,5,1,3], target = 3.714286, and k = 2

    4
   / \
  2   5
 / \
1   3

Output: [4,3]
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

#### Solutions

1. ##### find k-nearst in inorder traversal sequence

Possible solutions:
1. Pushing items into priority queue while traversing. `O(nlog(k))`
2. Use binary search for the required range after fetched the inorder traversal sequence. `O(n + log(n))`
    - `problem 658`


```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> v;
    void dfs(TreeNode * root) {
        if (!root) return;
        dfs(root->left);
        v.push_back(root->val);
        dfs(root->right);
    }
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        dfs(root);
        int lo = 0, hi = v.size() - k;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (target - v[mid] > v[mid + k] - target)
                lo = mid + 1;
            else
                hi = mid;
        }
        
        return {v.begin() + lo, v.begin() + lo + k};
    }
};
```

2. ##### precursor and successor O(log(n) + O(k)) S(log(n))


```c++
class Solution {
public:
    int successor(stack<TreeNode *> & s) {
        if (s.empty()) return INT_MAX;
        TreeNode * root = s.top();
        if (root->right) {
            root = root->right;
            while (root) {
                s.push(root);
                root = root->left;
            }
        }
        else {
            s.pop();
            while (!s.empty() && s.top()->right == root) {
                root = s.top(); s.pop();
            }
        }
        return s.empty() ? INT_MAX : s.top()->val;
    };
    int precursor(stack<TreeNode *> & s) {
        if (s.empty()) return INT_MIN;
        TreeNode *root = s.top();
        if (root->left) {
            root = root->left;
            while (root) {
                s.push(root);
                root = root->right;
            }
        }
        else {
            s.pop();
            while (!s.empty() && s.top()->left == root) {
                root = s.top(); s.pop();
            }
        }

        return s.empty() ? INT_MIN : s.top()->val;
    }
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        stack<TreeNode *> s;
        TreeNode * l = root, * r = root;
        while (root) {
            if (target < root->val) {
                s.push(root);
                r = root; root = root->left;
            }
            else {
                s.push(root);
                l = root; root = root->right;
            }
        }
        root = abs(l->val - target) < abs(r->val - target) ? l : r;
        while (s.top() != root)
            s.pop();
        stack<TreeNode *> pres(s), sucs(move(s));

        vector<int> res(k, root->val);
        int i = 1, succ = INT_MAX, prec = INT_MIN;
        while (i < res.size()) {
            if (succ == INT_MAX)
                succ = successor(sucs);
            if (prec == INT_MIN)
                prec = precursor(pres);
            if (target - (double)prec <  (double)succ - target) {
                res[i++] = prec; prec = INT_MIN;
            }
            else {
                res[i++] = succ; succ = INT_MAX;
            }
        }

        return res;
    }
};
```