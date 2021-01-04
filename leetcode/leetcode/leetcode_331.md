---
title: Verify Preorder Serialization of a Binary Tree
date: 2021-01-04
---
One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:

Input: "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
Example 2:

Input: "1,#"
Output: false
Example 3:

Input: "9,#,#,1"
Output: false

#### Solutions

1. ##### dfs

- Simulate the process of traversing the binary tree in preorder.

```cpp
class Solution {
public:
    bool dfs(const string & s, int & st) {
        if (st < s.size() && s[st] == ',') st++;
        // make sure the current node exists.
        if (st >= s.size()) return false;
        auto curc = s[st];
        while (st < s.size() && s[st] != ',') st++;
        return curc == '#' || (dfs(s, st) && dfs(s, st));
        
    }
    bool isValidSerialization(string preorder) {
        int st = 0;
        // Make sure no nodes remained.
        return dfs(preorder, st) && st == preorder.size();
    }
};
```

2. ##### binary tree property

- From the official answer
- Every non-empty node has two chidren nodes.

```cpp
class Solution {
public:
    vector<int> split(const string & s) {
        string w;
        vector<int> res;
        istringstream ss(s);
        while (getline(ss, w, ','))
            res.push_back(w != "#"); // node == 1 represents non-empty node

        return res;
    }
    bool isValidSerialization(string preorder) {
        int num = 1, i = 0;
        vector<int> nodes = split(preorder);
        for (i = 0; i < nodes.size() && num > 0; i++) {
            num--;
            if (nodes[i] == 1) // non-empty node has two children
                num += 2;
        }

        return num == 0 && i == nodes.size();
    }
};
```

or

```cpp
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int num = 1;
        string node;
        stringstream ss(preorder);
        
        while (num > 0 && getline(ss, node, ',')) {
            num--;
            if (node != "#")
                num += 2;
        }
        // eof means all characters have been consumed.
        return num == 0 && ss.eof(); 
    }
};
```