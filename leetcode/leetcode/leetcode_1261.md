---
title: Find Elements in a Contaminated Binary Tree
date: 2021-01-04
---
Given a binary tree with the following rules:

root.val == 0
If treeNode.val == x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
If treeNode.val == x and treeNode.right != null, then treeNode.right.val == 2 * x + 2
Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.

You need to first recover the binary tree and then implement the FindElements class:

FindElements(TreeNode* root) Initializes the object with a contamined binary tree, you need to recover it first.
bool find(int target) Return if the target value exists in the recovered binary tree.
 

Example 1:



Input
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
Output
[null,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1]); 
findElements.find(1); // return False 
findElements.find(2); // return True 
Example 2:



Input
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
Output
[null,true,true,false]
Explanation
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False
Example 3:



Input
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
Output
[null,true,false,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True
 

Constraints:

TreeNode.val == -1
The height of the binary tree is less than or equal to 20
The total number of nodes is between [1, 10^4]
Total calls of find() is between [1, 10^4]
0 <= target <= 10^6

#### Solutions

1. ##### hash map

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class FindElements {
public:
    unordered_set<int> m;
    FindElements(TreeNode* root) {
        build(root, 0);
    }
    void build(TreeNode * root, int val) {
        if (!root) return;
        m.insert(root->val = val);
        build(root->left, 2 * val + 1);
        build(root->right, 2 * val + 2);
    }
    bool find(int target) {
        return m.count(target);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
```

2. ##### bit operations

- reference: https://leetcode-cn.com/problems/find-elements-in-a-contaminated-binary-tree/solution/bu-yong-setde-findfang-fa-by-cyanflxy/
- When all node values have been plused by `1`, from the example show below, we can see that the direction of child is determined by the second most significant bit, the third .....
    - 5 as example, his bit representation is `101`, the second most significant bit is 0, goes into the left tree, then the third bit is 1, goes into the right tree.

```
                1
            2       3
         4    5   6   7
       8  9 10 11 ...

                1
        10              11
    100     101    110      111
1000  1001  ...

```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class FindElements {
public:
    TreeNode * root;
    FindElements(TreeNode* root) : root(root) {

    }
    
    bool find(int target) {
        target++;
        // get the second most significant bit
        int tmp = target, n = 0;
        while (tmp) {
            tmp >>= 1; n++;
        }
        int bit = (1 << (n - 1)) >> 1;
        TreeNode * p = root;
        // searching path based on MSB to LSB
        while (bit > 0 && p) {
            if ((bit & target) == 0)
                p = p->left;
            else
                p = p->right;
            bit >>= 1;
        }
        return p;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
```