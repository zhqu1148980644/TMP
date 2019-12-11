#### Given a binary tree, return all root-to-leaf paths.

#### Note: 
A leaf is a node with no children.

```
Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3
```

#### Solutions

1. ##### recursive(dfs)

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def binaryTreePaths(self, root):
        """
        :type root: TreeNode
        :rtype: List[str]
        """
        if not root: return []
        return [root.val + '->' + subpath
                for kid in (root.left, root.right) if kid
                for subpath in self.binaryTreePaths(kid)
                ] or [ str(root.val) ]
```