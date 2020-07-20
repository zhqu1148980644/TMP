Given a binary tree, return the postorder traversal of its nodes' values.

#### Example:

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
```

#### Follow up: 
Recursive solution is trivial, could you do it iteratively?

##### Solutions

1. ##### recursion

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
private:
    vector<int> res;

    void postorder(TreeNode * root) {
        if (root->left) postorder(root->left);
        if (root->right) postorder(root->right);
        res.push_back(root->val);
    }

public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root) postorder(root);
        return this->res;
    }
};
```


2. ##### iteration with stack use hashset marker

- The inorder traversal is similar to postorder traversal:
`left root right` -> `left right root`. We can reuse this pattern but with some alteration to comply the postorder requirement.
- In inorder traversal, whenever we come back to the root node, we will visit it then go to the right child. To make it postorder, we can just peek the top root node and directly visit the right child and we will come back to the node again in the future as we didn't pop this root node.
- Thus we need a marker to record if we have visited the right child because we could visit the root node twice and the first time we just peek it.
    - Use a hashet to record this information, when there is no record in hashset, that means it's the first time come to the root node and need to go right.

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        // or use another stack
        unordered_set<TreeNode *> seen;

        vector<int> res;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (seen.find(root) == seen.end()) {
                seen.insert(root);
                root = root->right;
            } else {
                seen.erase(root); s.pop();
                res.push_back(root->val);
                root = NULL;
            }
        }
        return res;
    }
};
```

3. ##### iteration with stack use prev marker

- It turns out that the previous node of the current root node is either the left child or the right child, we could simply use a variable to record the previous node.


```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int> res;

        TreeNode * prev = NULL;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && prev != root->right)
                root = root->right;
            else {
                res.push_back(root->val);
                prev = root; s.pop();
                root = NULL;
            }
        }
        return res;
    }
};
```

3. ##### Iteration with stack. use duplicate marker

- borrowed from others.
- As metioned above, the difficulty lies in figuring out wheather the current node comes from after visiting the left tree or the right tree.
- Instead of using additional marker, we can mark this information right in the stack by pushing the same node twice onto the stack, the first time we come back to the left tree, there must be two duplicate nodes on the top of the stack(otherwise we comes from the right tree).

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int> res;

        while (root || !s.empty()) {
            while (root) {
                // always push two times.
                if (root->right) s.push(root);
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            // there may not be item left
            if (!s.empty() && root == s.top())
                root = root->right;
            else {
                res.push_back(root->val);
                root = NULL;
            }
        }
        return res;
    }
};
```


4. ##### iteration with stack without marker

- The idea is directly go visit the root node when we get to the right-most child instead of visiting the root node in the next pop operation and use some marker to tell if we have visited the right child.
- reference: comments in https://leetcode.com/problems/binary-tree-postorder-traversal/discuss/45551/Preorder-Inorder-and-Postorder-Iteratively-Summarization
- I choose to set the root to `NULL` so that the next visit will pop a new one instead of continuing visit the left tree.

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int> res;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right) {
                root = root->right;
            } else {
                // we get to the rightmost node. start backtracking.
                s.pop();
                res.push_back(root->val);
                while (!s.empty() && s.top()->right == root) {
                    root = s.top(); s.pop();
                    res.push_back(root->val);
                }
                // this is compulsory.
                root = NULL;
            }
        }
        return res;
    }
};
```


5. ##### treat postorder as reversed preorder(node->right->left)

- When we traverse the binary tree in an altered version of preorder traversal: `root right left` and put each node's value into an `array`, then the sequence fetched by postorder traversal is the same as the revsered `array`.
- Another options is to inseart the new node into the head of visited nodes, then we can save the revsering process. This method requires fast O(1) insertion, thus a linked list would be good.
- Knowing this relation between preorder and postorder, we can use morris method of preorder traversal to reduce the problem's space complexity to O(1).

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int> res;

        while (root || !s.empty()) {
            if (root) {
                res.push_back(root->val);
                if (root->left)
                    // push left child in to stack
                    s.push(root->left);
                // we first visit the right child
                root = root->right;
            } else {
                root = s.top(); s.pop();
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

Morris version.


```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode * ldeep;

        while (root) {
            if (root->right) {
                ldeep = root->right;
                while (ldeep->left && ldeep->left != root)
                    ldeep = ldeep->left;
                if (ldeep->left != root) {
                    res.push_back(root->val);
                    ldeep->left = root;
                    root = root->right;
                } else {
                    ldeep->left = NULL;
                    root = root->left;
                }

            } else {
                res.push_back(root->val);
                root = root->left;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```


6. ##### morris  O(n) S(1)

- Check for detail if you can not understand. https://leetcode-cn.com/problems/binary-tree-postorder-traversal/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--34/
- In preorder/inorder morris method, we will visit the root node twice, and by checking if the precursor node's right child is `NULL` to determine if we have visited the left tree.
- Whenever we have visited the left tree and come back to the root node, we iteratively and `reversely` add `root node's left child`, `left child's right child`, `left child's right child' right child` ... into the result array.
- Reversely adding nodes can be done by reversing the `linked list` first and then reversing it back.

![](https://pic.leetcode-cn.com/5a136b884028d63dbc037994bf441debcc923960bfc69299cf8e2db23bc4abdb.jpg)

```c++
typedef TreeNode node;
class Solution {
public:
    node * reverse(node * head) {
        node * next = head->right;
        head->right = NULL;
        while (next) {
            node * tmp = next->right;
            next->right = head;
            head = next;
            next = tmp;
        }
        return head;
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode dummy(0);
        // Must set this dummy node. otherwise there is no way come back to root
        dummy.left = root; root = &dummy;
        node * rdeep, * head;

        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right == root) {
                    // Set NULL to make reverse terminate at the right point.
                    rdeep->right = NULL;
                    // reverse
                    head = reverse(root->left);
                    while (head) {
                        res.push_back(head->val);
                        head = head->right;
                    }
                    // reverse back and link as left child
                    root->left = reverse(rdeep);
                    root = root->right;
                } else {
                    rdeep->right = root;
                    root = root->left;
                }
            } else
                root = root->right;
        }
        return res;
    }
};
```

Or use a temporary array to store the reversed node values.

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode dummy(0);
        dummy.left = root; root = &dummy;
        TreeNode * rdeep, * head;
        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right == root) {
                    rdeep->right = nullptr;
                    vector<int> rev;
                    head = root->left;
                    while (head) {
                        rev.push_back(head->val);
                        head = head->right;
                    }
                    res.insert(res.end(), rev.rbegin(), rev.rend());
                    root = root->right;
                }
                else {
                    rdeep->right = root;
                    root = root->left;
                }
            }
            else
                root = root->right;
        }

        return res;
    }
};

```

Or reversed assignment.

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode dummy(0);
        dummy.left = root; root = &dummy;
        TreeNode * rdeep, * head;
        while (root) {
            if (root->left) {
                rdeep = root->left;
                int size = 1;
                while (rdeep->right && rdeep->right != root) {
                    rdeep = rdeep->right;
                    size++;
                }
                if (rdeep->right == root) {
                    rdeep->right = nullptr;
                    head = root->left;
                    res.resize(res.size() + size);
                    int end = res.size();
                    while (head) {
                        res[--end] = head->val;
                        head = head->right;
                    }
                    root = root->right;
                }
                else {
                    rdeep->right = root;
                    root = root->left;
                }
            }
            else
                root = root->right;
        }

        return res;
    }
};
```