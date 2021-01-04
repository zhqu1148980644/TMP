---
title: Design HashSet
date: 2021-01-04
---
Design a HashSet without using any built-in hash table libraries.

To be specific, your design should include these functions:

add(value): Insert a value into the HashSet. 
contains(value) : Return whether the value exists in the HashSet or not.
remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.

Example:

MyHashSet hashSet = new MyHashSet();
hashSet.add(1);         
hashSet.add(2);         
hashSet.contains(1);    // returns true
hashSet.contains(3);    // returns false (not found)
hashSet.add(2);          
hashSet.contains(2);    // returns true
hashSet.remove(2);          
hashSet.contains(2);    // returns false (already removed)

Note:

All values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashSet library.

#### Solutions

1. ##### separate chaining

```cpp
class MyHashSet {
public:
    /** Initialize your data structure here. */
    struct Node {
        int value;
        Node * next;
        Node(int key, Node * next= nullptr) : value(key), next(next) {}
    };
    vector<Node *> buckets{13, nullptr};
    int num = 0, size = 13;

    MyHashSet() {

    }
    void rehash(int size) {
        vector<Node *> oldbuckets(size, nullptr);
        swap(oldbuckets, buckets);
        // must put before find
        this->size = size;
        for (auto p : oldbuckets) {
            if (p) {
                Node * next;
                while (p) {
                    next = p->next;
                    add(p->value);
                    delete p;
                    p = next;
                }
            }
        }
    }
    Node ** find(int key) {
        Node * root = buckets[key % buckets.size()];
        if (!root || root->value == key)
            return &buckets[key % buckets.size()];
        while (root->next && root->next->value != key)
            root = root->next;
        
        return &(root->next);
    }
    void add(int key) {
        Node ** proot = find(key);
        if (!*proot) {
            *proot = new Node(key);
            num++;
            if (num == size)
            // or averaging the time complexity into multiple operations
                rehash(2 * size);
        }
    }
    
    void remove(int key) {
        Node ** proot = find(key);
        if (*proot) {
            Node * next = (*proot)->next;
            delete *proot;
            *proot = next;
            num--;
            if (size > 13 && num < size / 3)
                rehash(size / 2);
        }
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return *find(key);
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
```

2. ##### bit set

- Each bit represents a single number, for numbers range from 0 to 1000000, `1000000 / 32`'s int32 should be sufficient.

```cpp
class MyHashSet {
public:
    /** Initialize your data structure here. */
    uint32_t buckets[31251] = {0};
    MyHashSet() {}
    
    void add(int key) {
        // buckets[key / 32] |= (1 << (key % 32))
        buckets[key >> 5] |= (1 << (key & 0b11111));
    }
    
    void remove(int key) {
        buckets[key >> 5] &= ~(1 << (key & 0b11111));
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return buckets[key >> 5] & (1 << (key & 0b11111));
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
```