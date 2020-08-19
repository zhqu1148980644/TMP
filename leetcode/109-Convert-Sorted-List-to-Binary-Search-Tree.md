#### Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

```
Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```


#### Solutions


1. ##### recursion, find mid point O(nlog(n)) S(log(n))

- This method is similar to `problem 108`. Since linked list does not support efficient indexing, we need to find the middle node in a linked list in each subproblem.
- Another option is to set the middle node's next pointer to `NULL`, then the inorder function can works only with the root parameter. However, this will change the structure of the original linked list which may be unacceptable in real world.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode * preorder(ListNode * head, ListNode * tail) {
        if (head == tail) return nullptr;
        ListNode * mid = head, * fast = head;
        while (fast != tail && fast->next != tail) { 
            mid = mid->next;
            fast = fast->next->next;
        }
        TreeNode * root = new TreeNode(mid->val);
        root->left = preorder(head, mid);
        root->right = preorder(mid->next, tail);
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        return preorder(head, nullptr);
    }
};
```

or

```c++
class Solution {
public:
    TreeNode * build(ListNode * head, int len) {
        if (!head || !len) return nullptr;
        if (len == 1) return new TreeNode(head->val);
        ListNode * mid = head;
        int l = 0;
        while (l++ < len / 2)
            mid = mid->next;
        TreeNode *root = new TreeNode(mid->val);
        root->left  = build(head, len / 2);
        root->right = build(mid->next, len - len / 2 - 1);
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        int len = 0;
        ListNode * cur = head;
        while (cur && ++len) cur = cur->next;

        return build(head, len);
    }
};
```


3. ##### trade space for time with array

- Store the ordered list into a vector, then apply the same method used above.

```c++
class Solution {
private:
    TreeNode * inorder(vector<int *> & nums, int lo, int hi) {
        if (lo >= hi) return NULL;
        int mid = lo + ((hi - lo) >> 1);
        TreeNode * root = new TreeNode(*nums[mid]);
        root->left = inorder(nums, lo, mid);
        root->right = inorder(nums, mid + 1, hi);

        return root;
    }

public:
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int *> vtree;
        while (head) {
            vtree.push_back(&head->val);
            head = head->next;
        }
        return inorder(vtree, 0, vtree.size());
    }
};
```


4. ##### emulate inorder traversal by recursion O(n) S(log(n))


- borrowed from others.
- The idea is that the sorted list equals to the sequence of elements visited by inorder traversal.
- The first element in the sorted list is the first child will be visited by inorder traversal, and the second element is the second child be visited by inorder traversal and so on.
- Through a recursive inorder traversal, we can recursively link each item and build the tree in one pass.
    - Whenever the left tree has been created from a recursive call, we will move the node one step further to match the process of inorder traversal.
    - To terminate the recursive inorder traversal in the right point, we need to fetch the total length of the linked list.

```c++
class Solution {
public:
    ListNode * head;

    TreeNode* convertBst(int lo, int hi) {
        if (lo >= hi) return nullptr;
        int mid = lo + (hi - lo) / 2;

        TreeNode * left = convertBst(lo, mid);
        TreeNode * root = new TreeNode(head->val);
        root->left = left;
        head = head->next;
        TreeNode * right = convertBst(mid + 1, hi);
        root->right = right;
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        int len = 0;
        ListNode * cur = head;
        while (cur) {
            len++; cur = cur->next;
        }
        this->head = head;
        return convertBst(0, len);
    }
};
```