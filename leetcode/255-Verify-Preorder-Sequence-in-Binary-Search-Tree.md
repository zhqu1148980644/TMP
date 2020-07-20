Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Consider the following binary search tree: 

     5
    / \
   2   6
  / \
 1   3
Example 1:

Input: [5,2,6,1,3]
Output: false
Example 2:

Input: [5,2,1,3,6]
Output: true
Follow up:
Could you do it using only constant space complexity?


#### Solutions

1. ##### stack

- The traversal sequence of the left subtree is monotonically decreasing. And the root node is the lower bound of the right subtree.

```c++
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> s;
        int lo = INT_MIN;
        for (int i = 0; i < preorder.size(); i++) {
            if (preorder[i] <= lo) return false;
            while (!s.empty() && s.top() < preorder[i]) {
                lo = s.top(); s.pop();
            }
            s.push(preorder[i]);
        }
        return true;
    }
};
```