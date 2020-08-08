Given a binary tree root and a linked list with head as the first node. 

Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.

In this context downward path means a path that starts at some node and goes downwards.

 

```
Example 1:

Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Explanation: Nodes in blue form a subpath in the binary Tree.  

Example 2:

Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true

Example 3:

Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: false
Explanation: There is no path in the binary tree that contains all the elements of the linked list from head.
```

 

#### Constraints:

-    1 <= node.val <= 100 for each node in the linked list and binary tree.
-    The given linked list will contain between 1 and 100 nodes.
-    The given binary tree will contain between 1 and 2500 nodes.


#### Solutions

1. ##### dfs

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
    bool find(ListNode * head, TreeNode * root) {
        if (!head)
            return true;
        if (!root || head->val != root->val)
            return false;
        return find(head->next, root->left) || find(head->next, root->right);
    }

    bool isSubPath(ListNode* head, TreeNode* root) {
        stack<TreeNode *> s;
        while (!s.empty() || root) {
            if (root) {
                if (root->val == head->val)
                    if (find(head, root))
                        return true;
                if (root->right)
                    s.push(root->right);
                root = root->left;
            }
            else {
                root = s.top();
                s.pop();
            }
        }
        
        return false;
    }
};
```

or

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
    bool find(ListNode * head, TreeNode * root) {
        if (!head) return true;
        if (!root || head->val != root->val)
            return false;
        return find(head->next, root->left) || find(head->next, root->right);
    }
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!root) return false;
        if (root->val == head->val && find(head, root))
            return true;
        return isSubPath(head, root->left) || isSubPath(head, root->right);
    }
};
```