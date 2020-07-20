#### Given an n-ary tree, return the postorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

 

#### Follow up:

Recursive solution is trivial, could you do it iteratively?

 

```
Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: [5,6,3,2,4,1]

Example 2:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
```

 

#### Constraints:

-    The height of the n-ary tree is less than or equal to 1000
-    The total number of nodes is between [0, 10^4]


#### Solutions

1. ##### recursion

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    void traverse(Node * root, vector<int> & res) {
        for (auto & child : root->children)
            if (child) traverse(child, res);
        res.push_back(root->val);
    }

    vector<int> postorder(Node* root) {
        vector<int> res;
        if (root) traverse(root, res);
        return res;
    }
};
```


2. ##### preorder with stack

- The most intuitive and easy way is traversing in a mirror-inversed preorder strategy and reversing the result at the end.
- `root right left`
- However it's actually not a real postorder traversal.

```c++
class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<Node *> s;
        if (root) s.push(root);

        vector<int> res;
        while (!s.empty()) {
            root = s.top(); s.pop();
            res.push_back(root->val);
            for (auto child : root->children)
                if (child) s.push(child);
        }

        return {res.rbegin(), res.rend()};
    }
};
```


3. ##### postorder with stack

- Use pair to record the visiting history of child nodes.
- Pop the current node(visiting upside) only if there are no other child left.
- `last` represent the last child visited before.

```c++
class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<pair<Node *, int>> s;

        vector<int> res;
        while (root || !s.empty()) {
            while (root) {
                s.push({root, 0});
                if (root->children.size())
                    root = root->children[0];
                else
                    root = nullptr;
            }
            root = s.top().first;
            auto & last = s.top().second;
            if (last + 1 < root->children.size())
                root = root->children[++last];
            else {
                s.pop();
                res.push_back(root->val);
                root = nullptr;
            }
        }
        return res;
    }
};
```