Design your implementation of the linked list. You can choose to use the singly linked list or the doubly linked list. A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node. If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement these functions in your linked list class:

get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.
addAtHead(val) : Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
addAtTail(val) : Append a node of value val to the last element of the linked list.
addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
 

Example:

Input: 
["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
[[],[1],[3],[1,2],[1],[1],[1]]
Output:  
[null,null,null,null,2,null,3]

Explanation:
MyLinkedList linkedList = new MyLinkedList(); // Initialize empty LinkedList
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3
 

Constraints:

0 <= index,val <= 1000
Please do not use the built-in LinkedList library.
At most 2000 calls will be made to get, addAtHead, addAtTail,  addAtIndex and deleteAtIndex.

#### Solutions

1. ##### doubled linked list

- circular double linked list. ie: `end->next == begin` and `end->prev == back`

```c++
template <typename T>
class List {
private:
    struct Node {
        T val;
        Node * prev, * next;
        Node (T val, Node * prev = nullptr, Node * next = nullptr)
            : val(val), prev(prev), next(next) {}
    };
    struct iterator {
        Node * pnode = nullptr;
        // used for type_traits
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = uint32_t;
        using pointer = T*;
        using reference = T&;
        iterator(Node * pnode) : pnode(pnode) {}
        // ++/-- is needed for next/advance
        iterator & operator++() {
            pnode = pnode->next;
            return *this;
        }
        iterator & operator--() {
            pnode = pnode->prev;
            return *this;
        }
        bool operator==(const iterator & it2) {
            return pnode == it2.pnode;
        }
        bool operator!=(const iterator & it2) {
            return !operator==(it2);
        }
        // simulate naive pointer
        T & operator*() {
            return pnode->val;
        }
        Node * operator->() const {
            return pnode;
        }
    };
    Node _end {0};
    int _size = 0;
public:
    List() {
        _end.next = _end.prev = &_end;
    }
    iterator end() {
        return iterator(&_end);
    }
    iterator begin() {
        return iterator(_end.next);
    }
    int size() const {
        return _size;
    }
    // return the inserted element
    iterator insert(const iterator & it, const T & val) {
        it->prev->next = new Node(val, it->prev, it.pnode);
        it->prev = it->prev->next;
        _size++;
        return iterator(it->prev);
    }
    // return the next node of the deleted node
    iterator erase(const iterator & it) {
        it->prev->next = it->next;
        it->next->prev = it->prev;
        _size--;
        iterator next(it->next);
        delete it.pnode;
        return next;
    }
};

class MyLinkedList {
public:
    /** Initialize your data structure here. */
    List<int> list;
    MyLinkedList() {

    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index >= list.size())
            return -1;
        return *next(list.begin(), index);
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        list.insert(list.begin(), val);
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        list.insert(list.end(), val);
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        // can not be if >=
        if (index > list.size()) return;
        if (list.size() - index < index) {
            auto rit = make_reverse_iterator(list.end());
            list.insert(next(rit, list.size() - index).base(), val);
        }
        else
            list.insert(next(list.begin(), index), val);
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index < list.size())
            list.erase(next(list.begin(), index));
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```