#### You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

 

#### Follow up:

![](https://assets.leetcode.com/uploads/2019/02/14/116_sample.png)

You may only use constant extra space.
Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
 

#### Example 1:



```
Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
```
 

#### Constraints:

- The number of nodes in the given tree is less than 4096.
- -1000 <= node.val <= 1000

#### Solutions

1. ##### recursion

- Link nodes in the right side of the left tree to nodes in the left side of the right tree.
- besides the code of the link part, The link function is actually a recursive preorder traversal function.

```c++
class Solution {
public:
    void link(Node * root) {
        if (!root) return;
        // links happens here
        Node * left = root->left;
        Node * right = root->right;
        while (left) {
            left->next = right;
            left = left->right;
            right = right->left;
        }
        link(root->left);
        link(root->right);
    }

    Node* connect(Node* root) {
        link(root);
        return root;
    }
};
```

2. ##### level order traversal with queue  O(n) S(log(n))

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        queue<Node *> q;
        if(root) q.push(root);
        while (!q.empty()) {
            int size = q.size();
            Node * prev = nullptr;
            while (size--) {
                Node * cur = q.front(); q.pop();
                if (cur->left) {
                    q.push(cur->left);
                    q.push(cur->right);
                }
                if (prev) prev->next = cur;
                prev =  cur;
            }
        }
        return root;
    }
};
```


3. ##### morris O(n) S(1)

- Similar to the first recursive version.

```c++
class Solution {
public:
    Node* connect(Node* root) {
        Node * rdeep, * ldeep, * head = root;
        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right == root) {
                    rdeep->right = nullptr;
                    root = root->right;
                } else {
                    // link happens here
                    ldeep = root->right;
                    rdeep = root->left;
                    rdeep->next = ldeep;
                    while (rdeep->right) {
                        rdeep = rdeep->right;
                        ldeep = ldeep->left;
                        rdeep->next = ldeep;
                    }
                    rdeep->right = root;
                    root = root->left;
                }
            } else
                root = root->right;
        }
        return head;
    }
};
```

4. ##### level by level

- borrowed from others.
- This method seems like the standard answer.
- Traverse all nodes linked by `next` pointer in the current level and link nodes in the next level.

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
"""
class Solution:
    def connect(self, root: 'Node') -> 'Node':
        r = root
        while root and root.left:
            nextlevel = root.left
            while root:
                root.left.next = root.right
                root.right.next = root.next.left if root.next else None
                root = root.next
            root = nextlevel
        return r
```

5. ##### recursion

- Note that this verison links one level across multiple recursive call. 

```c++
class Solution {
public:
    Node* connect(Node* root) {
        if (!root || !root->left)
            return root;
        else {
            root->left->next = root->right;
            root->right->next = root->next ? root->next->left : nullptr;
            connect(root->left);
            connect(root->right);

            return root;
        }
    }
};
```