---
title: Convert Binary Search Tree to Sorted Doubly Linked List
date: 2021-01-04
---
Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.

You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

We want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.



```
Example 1:

Input: root = [4,2,5,1,3]


Output: [1,2,3,4,5]

Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

Example 2:

Input: root = [2,1,3]
Output: [1,2,3]

Example 3:

Input: root = []
Output: []
Explanation: Input is an empty tree. Output is also an empty Linked List.

Example 4:

Input: root = [1]
Output: [1]
```


#### Constraints:

-    -1000 <= Node.val <= 1000
-    Node.left.val < Node.val < Node.right.val
-    All values of Node.val are unique.
-    0 <= Number of Nodes <= 2000


#### Solutions

1. ##### inorder traversal with recursion

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node * head = nullptr;
    Node * prev = nullptr;
    void inorder(Node * root) {
        if (!root) return;
        inorder(root->left);
        if (!head)
            head = root;
        else {
            prev->right = root;
            root->left = prev;
        }
        prev = root;
        inorder(root->right);
    }

    Node* treeToDoublyList(Node* root) {
        if (root) {
            inorder(root);
            head->left = prev;
            prev->right = head;
        }
        return head;    
    }
};
```


2. ##### inorder traversal with stack

```cpp
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        stack<Node *> s;
        Node * prev = nullptr, * head = nullptr;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            if (!head)
                head = root;
            else {
                prev->right = root;
                root->left = prev;
            }
            prev = root;
            root = root->right;
        }

        if (head) {
            head->left = prev;
            prev->right = head;
        }

        return head;
    }
};
```

3. ##### morris method

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        Node * head, * prev, * rdeep;
        head = prev = rdeep = nullptr;

        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right != root) {
                    rdeep->right = root;
                    root = root->left;
                    continue;
                }
                else
                    rdeep->right = nullptr;
            }
            if (!head)
                head = root;
            else {
                prev->right = root;
                root->left = prev;
            }
            prev = root;
            root = root->right;
        }

        if (prev) {
            head->left = prev;
            prev->right = head;
        }

        return head;
    }
};
```