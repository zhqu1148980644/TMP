Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
 

Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.

##### Solutions

1. ##### recursion O(len(s) * len(t))

- For each node in s, check if tree `t` is the same as this subtree.

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool issame(TreeNode * s, TreeNode * t) {
        if (!s && !t)
            return true;
        if (!s || !t)
            return false;
        return s->val == t->val && issame(s->left, t->left) && issame(s->right, t->right);
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (!s) return false;
        return issame(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};
```

2. ##### subsequence searching O(len(s) + len(t))

- Only preorder and postorder traversal plus additional null nodes can represent a tree uniquely. https://stackoverflow.com/questions/45871284/uniqueness-of-inorder-preorder-and-postorder-traversal-with-null-elements
- No need to treat left and right null nodes differently.
- After converted two trees into traversal sequence, use pattern matching algorithm to speed up the search. ie: kmp, rabin-karp ...


```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int nullval = INT_MAX;
    void postorder(vector<int> & v, TreeNode * root) {
        if (!root)
            v.push_back(nullval);
        else {
            postorder(v, root->left);
            postorder(v, root->right);
            v.push_back(root->val);
        }
    }

    int strstr(vector<int> & s, vector<int> & pattern) {
        // build next table
        vector<int> next(pattern.size());
        int t = next[0] = -1, i = 0, j = 0;
        while (j < next.size() - 1) {
            if (t < 0 || pattern[t] == pattern[j]) {
                j++; t++;
                next[j] = pattern[j] != pattern[t] ? t : next[t];
            } else
                t = next[t];
        }
        // start matching
        i = j = 0;
        int m = s.size(), n = pattern.size();
        while (i < m && j < n) {
            if (j < 0 || pattern[j] == s[i]) {
                i++; j++;
            } else
                j = next[j];
        }
        return j == n ? i - j : -1;
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        vector<int> sseq, tseq;
        postorder(sseq, s);
        postorder(tseq, t);
        return strstr(sseq, tseq) != -1;
    }
};
```



3. ##### tree hash O(n)

- Encode each substree into a unique hash key.
- `hash(root) = root->val + 97 * hash(root->left) * primes[size(left)] + 137 * hash(root->right) * primes[size(right)]`
    - `97` and `137` are two randomly chosen primes for differentiating left and right trees.
- How to handle collisions.

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> primes;
    static const int MOD = 1e9 + 7;
    // euler seive, check problem 204
    vector<int> getprimes(int n) {
        int maxn = 15 * n;
        vector<int> primes(n); vector<bool> vis(maxn);
        vis[0] = vis[1] = true;
        int cnt = 0;
        for (int i = 2; cnt < n; i++) {
            if (!vis[i])
                primes[cnt++] = i;
            for (int j = 0; j < cnt && i * primes[j] < maxn; j++) {
                vis[i * primes[j]] = false;
                if (i % primes[j] == 0)
                    break;
            }
        }
        return primes;
    }

    pair<long, int> hash(TreeNode * root, const pair<long, TreeNode *> & target, bool & find) {
        if (!root || find) return {1, 0};
        auto [hl, sl] = hash(root->left, target, find);
        auto [hr, sr] = hash(root->right, target, find);
        int curh = (root->val + 31 * hl * primes[sl] + 179 * hr * primes[sr]) % MOD;
        // the pair also contains the target tree, could be used for collision checking
        if (target.second && target.first == curh)
            find = true;

        return {curh, sl + sr + 1};
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        function<int(TreeNode *)> size = [&size](TreeNode * root) {
            if (!root) return 0;
            return 1 + size(root->left) + size(root->right);
        };

        int num1 = size(s), num2 = size(t);
        if (num2 > num1) return false;
        primes = getprimes(num1);
        bool find = false;
        auto [hash2, s2] = hash(t, {-1, nullptr}, find);
        auto [hash1, s1] = hash(s, {hash2, t}, find);

        return find;
    }
};
```

or simply use string hash, though it's much slower than integer hash.

```c++
class Solution {
public:
    hash<string> hasher;
    char buff[100];
    size_t hash(TreeNode * root, const pair<size_t, TreeNode *> & target, bool & find) {
        if (!root || find) return 1;
        auto hl = hash(root->left, target, find);
        auto hr = hash(root->right, target, find);
        sprintf(buff, "%d,%d|%d", root->val, hl, hr);
        size_t curh = hasher(buff);
        // the pair also contains the target tree, could be used for collision checking
        if (target.second && target.first == curh)
            find = true;

        return curh;
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        bool find = false;
        auto hash2 = hash(t, {-1, nullptr}, find);
        auto hash1 = hash(s, {hash2, t}, find);

        return find;
    }
};
```