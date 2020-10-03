Given a binary tree

```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
```

Initially, all next pointers are set to NULL.

 

#### Follow up:

You may only use constant extra space.
Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
 

#### Example 1:

![](https://assets.leetcode.com/uploads/2019/02/15/117_sample.png)

```
Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
```
 

#### Constraints:

- The number of nodes in the given tree is less than 6000.
- -100 <= node.val <= 100

#### Solutions

- Be carefull that trees in this problem may be any type while trees in the previous problem are always perfect binary trees.

1. ##### bfs with queue O(n) S(n)

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
        if (root) q.push(root);

        while (!q.empty()) {
            int size = q.size();
            Node * prev = nullptr;
            while (size--) {
                Node * cur = q.front(); q.pop();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                if (prev) prev->next = cur;
                prev = cur;
            }
        }
        return root;
    }
};
```

2. ##### Recursion O(n) S(1)/S(log(n))

- Because nodes in one level is fully linked after multiple recursive call, the right tree must be linked before the left tree. 

```c++
class Solution {
public:
    Node* connect(Node* root) {
        if (!root || (!root->left && !root->right))
            return root;

        // Search for the first node with valid child in the current level.
        Node * right = nullptr, * next = root->next;
        // trys to find the next node in the same level
        while (next && (!next->left && !next->right))
            next = next->next;
        if (next) right = next->left ? next->left : next->right;

        if (root->left)
            root->left->next = root->right ? root->right : right;
        if (root->right)
            root->right->next = right;

        // Connectting the right child at first is indispensable.
        // Otherwise the searching step would fails in future steps.
        // Because root->right may not contain children, root->left's will skip root-right and search for another node with children through the link of root->right->next.
        connect(root->right);
        connect(root->left);

        return root;
    }
};
```

The iteration one can be much more complicated and many edge cases need to be considered.

3. ##### level by level

- Borrowed from others.
- This method seems like the standard answer applys to any kind of binary tree.
- The complexity lies in the existance of nodes with no children.
- In the first solution with queue, since we push children into queue only if they exist, the problem we encountered in solution 2 will be naturally ignored.
    - Find the first non-null item is O(1), find the previous non-null item is O(1);
- Inspired by the queue solution, we can use a `container` to maintain nodes founded in the current level and link them one by one. Here we use a `dummy node` as the container.

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
        Node * head = root;
        while (root) {
            Node dummy, * tail = &dummy;
            while (root) {
                if (root->left) {
                    tail = tail->next = root->left;
                }
                if (root->right) {
                    tail = tail->next = root->right;
                }
                root = root->next;
            }
            root = dummy.next;    // the first iem in the next level
        }
        return head;
    }
};
```
