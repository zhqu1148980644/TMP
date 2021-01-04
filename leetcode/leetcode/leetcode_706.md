---
title: Design HashMap
date: 2021-01-04
---
Design a HashMap without using any built-in hash table libraries.

To be specific, your design should include these functions:

put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.

Example:

MyHashMap hashMap = new MyHashMap();
hashMap.put(1, 1);          
hashMap.put(2, 2);         
hashMap.get(1);            // returns 1
hashMap.get(3);            // returns -1 (not found)
hashMap.put(2, 1);          // update the existing value
hashMap.get(2);            // returns 1 
hashMap.remove(2);          // remove the mapping for 2
hashMap.get(2);            // returns -1 (not found) 

Note:

All keys and values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashMap library.

#### Solutions

1. ##### separate chaining

- The same as `problem 705`, similar to `unorderd_map` in stl, use `pair<Key, Val>` as the Node value type.

```cpp
class MyHashMap {
public:
    /** Initialize your data structure here. */
    struct Node {
        pair<int, int> value;
        Node * next;
        Node (int key, int value, Node * next = nullptr) 
            : value(key, value), next(next) {}
    };
    vector<Node *> buckets{13, nullptr};
    int num = 0, size = 13;
    MyHashMap() {

    }
    
    void rehash(int size) {
        vector<Node *> oldbuckets(size, nullptr);
        swap(oldbuckets, buckets);
        // must set befor find
        this->size = size;
        for (auto & p : oldbuckets) {
            if (p) {
                Node * next;
                while (p) {
                    next = p->next;
                    // must set next pointer to null.
                    p->next = nullptr;
                    put(p);
                    p = next;
                }
            }
        }
    }
    Node ** find(int key) {
        Node * root = buckets[key % size];
        if (!root || root->value.first == key)
            return &buckets[key % size];
        while (root->next && root->next->value.first != key)
            root = root->next;
        return &(root->next);
    }
    /** value will always be non-negative. */
    void put(int key, int value) {
        Node ** proot = find(key);
        if (!*proot) {
            *proot = new Node(key, value);
            num++;
            if (num == size)
                rehash(2 * size);
        }
        else
            (*proot)->value.second = value;
    }
    void put(Node * p) {
        *find(p->value.first) = p;
    }
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        Node ** proot = find(key);
        return (*proot) ? (*proot)->value.second : -1;
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
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
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
```