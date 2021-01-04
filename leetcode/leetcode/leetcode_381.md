---
title: Insert Delete GetRandom O(1) Duplicates allowe
date: 2021-01-04
---
Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();

#### Solutions

1. ##### hash map

- Similar to previous problem.

```cpp
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    unordered_map<int, unordered_set<int>> indexes;
    vector<int> v;
    RandomizedCollection() {}
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool exist = indexes.count(val);
        v.push_back(val);
        indexes[val].insert(v.size() - 1);
        return !exist;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (indexes.count(val)) {
            if (v.back() == val)
                indexes[val].erase(v.size() - 1);
            else {
                int rmindex = *(indexes[val].begin());
                indexes[v.back()].erase(v.size() - 1);
                indexes[v.back()].insert(rmindex);
                swap(v[rmindex], v.back());
                indexes[val].erase(rmindex);
            }
            if (indexes[val].empty())
                indexes.erase(val);
            v.pop_back();
            return true;
        }
        return false;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return v.size() ? v[rand() % v.size()] : 0;
    }
};
```