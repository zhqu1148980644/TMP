---
title: All O(1) Data Structure
date: 2021-01-04
---
Implement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
Challenge: Perform all these in O(1) time complexity.

#### Solutions

1. ##### list and hash map with stl iterators


```cpp
class AllOne {
public:
    /** Initialize your data structure here. */
    using keys = list<string>;
    using val_keys = pair<int, keys>;
    using val_keys_it = list<val_keys>::iterator;
    list<val_keys> vals = {{0, {}}};
    unordered_map<string, pair<list<val_keys>::iterator, keys::iterator>> m;
    list<val_keys>::iterator begin;

    AllOne() {
        begin = vals.begin();
    }
    void moveitem(val_keys_it & val_it, keys::iterator & key_it, 
            const val_keys_it & new_val_it, string & key) {
        auto & keys = val_it->second;
        auto & newkeys = new_val_it->second;
        auto new_key_it = newkeys.insert(newkeys.end(), key);
        keys.erase(key_it); if (keys.empty()) vals.erase(val_it);
        val_it = new_val_it, key_it = new_key_it;
    }
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (m.count(key)) {
            auto & [val_it, key_it] = m[key];
            auto & [val, keys] = *val_it;
            if (next(val_it) == vals.end() || next(val_it)->first != val + 1) {
                if (keys.size() == 1) {
                    val += 1; return;
                }
                vals.insert(next(val_it), {val + 1, {}});
            }
            moveitem(val_it, key_it, next(val_it), key);
        }
        else {
            auto nextit = next(begin);
            if (nextit == vals.end() || nextit->first != 1)
                vals.insert(nextit, {1, {}});
            auto val_it = next(begin);
            auto & [val, keys] = *val_it;
            auto key_it = keys.insert(keys.end(), key);
            m[key] = {val_it, key_it};
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (!m.count(key)) return;
        auto & [val_it, key_it] = m[key];
        auto & [val, keys] = *val_it;
        if (val == 1) {
            keys.erase(key_it);
            if (keys.empty()) vals.erase(val_it);
            m.erase(key);
        }
        else {
            if (prev(val_it) == begin || prev(val_it)->first != val - 1) {
                if (keys.size() == 1) {
                    val -= 1; return;
                }
                vals.insert(val_it, {val - 1, {}});
            }
            moveitem(val_it, key_it, prev(val_it), key);
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        auto maxit = prev(vals.end());
        return maxit != begin ? maxit->second.back() : "";
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        auto minit = next(begin);
        return minit != vals.end() ? minit->second.back() : "";
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
```


or

```cpp
class AllOne {
public:
    /** Initialize your data structure here. */
    using keys = list<string>;
    using val_keys = pair<int, keys>;
    using val_keys_it = list<val_keys>::iterator;
    list<val_keys> vals = {{0, {""}}};
    unordered_map<string, pair<list<val_keys>::iterator, keys::iterator>> m;
    list<val_keys>::iterator begin;

    AllOne() {
        begin = vals.begin();
    }
    void moveitem(val_keys_it & val_it, keys::iterator & key_it, 
            const val_keys_it & new_val_it, string & key) {
        auto & keys = val_it->second;
        auto & newkeys = new_val_it->second;
        auto new_key_it = newkeys.insert(newkeys.end(), key);
        keys.erase(key_it); if (keys.empty()) vals.erase(val_it);
        val_it = new_val_it, key_it = new_key_it;
    }
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (!m.count(key))
            m[key] = {begin, begin->second.insert(begin->second.end(), key)};
        auto & [val_it, key_it] = m[key];
        auto & [val, keys] = *val_it;
        if (next(val_it) == vals.end() || next(val_it)->first != val + 1) {
            if (keys.size() == 1) {
                val += 1; return;
            }
            vals.insert(next(val_it), {val + 1, {}});
        }
        moveitem(val_it, key_it, next(val_it), key);
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (!m.count(key)) return;
        auto & [val_it, key_it] = m[key];
        auto & [val, keys] = *val_it;
        if (val == 1) {
            keys.erase(key_it);
            if (keys.empty()) vals.erase(val_it);
            m.erase(key);
        }
        else {
            if (prev(val_it) == begin || prev(val_it)->first != val - 1) {
                if (keys.size() == 1) {
                    val -= 1; return;
                }
                vals.insert(val_it, {val - 1, {}});
            }
            moveitem(val_it, key_it, prev(val_it), key);
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        auto maxit = prev(vals.end());
        return maxit != begin ? maxit->second.back() : "";
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        auto minit = next(begin);
        return minit != vals.end() ? minit->second.back() : "";
    }
};
```