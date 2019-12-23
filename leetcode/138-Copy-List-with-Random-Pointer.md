#### A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

The Linked List is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

- val: an integer representing Node.val
- random_index: the index of the node (range from 0 to n-1) where random pointer points to, or null if it does not point to any node.
 

```
Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:



Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
Example 4:

Input: head = []
Output: []
Explanation: Given linked list is empty (null pointer), so return null.
```
 

#### Constraints:

- -10000 <= Node.val <= 10000
- Node.random is null or pointing to a node in the linked list.
- Number of Nodes will not exceed 1000.


#### Solutions


1. ##### recusion with hashmap O(n) S(n) 

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
private:
    unordered_map<Node *, Node *> his;
public:
    Node * cloneNode(Node * head) {
        if (!head) return nullptr;
        if (his.find(head) != his.end())
            return his[head];
        else {
            Node * cur = his[head] = new Node(head->val);
            cur->next = cloneNode(head->next);
            cur->random = cloneNode(head->random);
            return cur;
        }

    }

    Node* copyRandomList(Node* head) {
        return cloneNode(head);
    }
};
```

2. ##### iteration with hashmap O(n) S(n)

- clone node one by one.

```c++
class Solution {
private:
    unordered_map<Node *, Node *> his;

public:
    Node * getNode(Node * oldnode) {
        if (!oldnode) return nullptr;
        if (his.find(oldnode) == his.end())
            his[oldnode] = new Node(oldnode->val);
        return his[oldnode];
    }
    void clone(Node * head) {
        Node * newhead;
        while (head) {
            newhead = getNode(head);
            newhead->next = getNode(head->next);
            newhead->random = getNode(head->random);
            head = head->next;
            newhead = newhead->next;
        }
    }
    Node* copyRandomList(Node* head) {
        clone(head);
        return getNode(head);
    }
};
```


3. ##### inplace O(n) S(1)

- borrowed from official answer.
- Insert the copy of code after each node.
- This can be seen as a hashmap based on the original linked list, the copy of each node can be find in O(1) time.
- steps:
    - insert new duplicate node after each node.
    - set each new node's random pointer.
    - relink the original linked list and link new nodes together into a new linked list.

```c++
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        Node * cur = head, * newhead;
        while (cur) {
            Node * next = cur->next;
            Node * newnode = new Node(cur->val);
            cur->next = newnode;
            newnode->next = next;
            cur = next;
        }

        cur = head;
        while (cur) {
            cur->next->random = cur->random ? cur->random->next : nullptr;
            cur = cur->next->next;
        }

        cur = head;
        newhead = head->next;
        while (cur) {
            Node * tmp = cur->next;
            cur->next = cur->next->next;
            tmp->next = cur->next ? cur->next->next : nullptr;
            cur = cur->next;
        }

        return newhead;
    }
};
```