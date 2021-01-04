---
title: Two Sum III Data structure design
date: 2021-01-04
---
#### Design and implement a TwoSum class. It should support the following operations: add and find.

- add - Add the number to an internal data structure.
- find - Find if there exists any pair of numbers which sum is equal to the value.

```
Example 1:

add(1); add(3); add(5);
find(4) -> true
find(7) -> false

Example 2:

add(3); add(1); add(2);
find(3) -> true
find(6) -> false
```

#### Solutions

1. ##### hashmap

```cpp
class TwoSum {
    unordered_map<int, int> m;
public:
    /** Initialize your data structure here. */
    TwoSum() { }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        m[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for (auto & kv : m) {
            int remain = value - kv.first;
            if (remain == kv.first && kv.second > 1)
                return true;
            if (remain != kv.first && m.find(remain) != m.end())
                return true;
        }
    
        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */
```