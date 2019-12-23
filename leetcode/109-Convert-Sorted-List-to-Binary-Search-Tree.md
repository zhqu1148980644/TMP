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
- Another option is to set the middle node's next pointer to `NULL`, then the inorder function can works only with the root parameter. However, this will change the structure of the original linked list which may be unchangebal in real world.

```c++
class Solution {
private:
    TreeNode * inorder(ListNode * head, ListNode * tail) {
        // head->next == null will be handled by in the next iteration
        if (head == tail) return NULL;
        ListNode * mid = head, * fast = head;
        while (fast != tail && fast->next != tail) {
            mid = mid->next;
            fast = fast->next->next;
        }
        fast = mid->next;

        TreeNode * root = new TreeNode(mid->val);
        root->left = inorder(head, mid);
        root->right = inorder(mid->next, tail);

        return root;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return inorder(head, NULL);
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


4. ##### emulate inorder traversal by recursion


- borrowed from others.
- The idea is that the sorted list equals to the sequence of elements visited by inorder traversal.
- The first element in the sorted list is the first child will be visited by inorder traversal, and the second element is the second child be visited by inorder traversal and so on.
- Through a recursive inorder traversal, we can recursively link each item and build the tree in one pass.
    - Whenever the left tree has been created from a recursive call, we will move the node one step further to match the process of inorder traversal.
    - To terminate the recursive inorder traversal in the right point, we need to fetch the total length of the linked list.

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
    ListNode * head;
    TreeNode * convertBst(int lo, int hi) {
        if (lo >= hi) return nullptr;
        int mid = lo + ((hi - lo) >> 1);

        TreeNode * left = convertBst(lo, mid);
        TreeNode * node = new TreeNode(head->val);
        node->left = left;
        // move one step further
        this->head = this->head->next;
        TreeNode * right = convertBst(mid + 1, hi);
        node->right = right;

        return node;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        int count = 0;
        ListNode * cur = head;
        while (cur) {
            cur = cur->next;
            count++;
        }
        this->head = head;

        return convertBst(0, count);
    }
};
```