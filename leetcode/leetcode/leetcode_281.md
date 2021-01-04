---
title: Zigzag Iterator
date: 2021-01-04
---
#### Given two 1d vectors, implement an iterator to return their elements alternately.

 

```
Example:

Input:
v1 = [1,2]
v2 = [3,4,5,6] 
Output: [1,3,2,4,5,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,3,2,4,5,6].
```
 

#### Follow up:

What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question:
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example:

```
Input:
[1,2,3]
[4,5,6,7]
[8,9]

Output: [1,4,8,2,5,9,3,6,7].
```

#### Solutions

1. ##### STL's iterator

- Using the abstraction of STL's iterator, this strategy can be simply extended to any number of vectors.

```cpp
typedef vector<int>::iterator It;
class ZigzagIterator {
    list<pair<It, It>> iters;
    list<pair<It, It>>::iterator cur;

public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        int k = 2;
        iters.push_back(make_pair(v1.begin(), v1.end()));
        iters.push_back(make_pair(v2.begin(), v2.end()));
        cur = iters.begin();
        remove_empty();
    }

    int next() {
        int res = *cur->first;
        cur->first++; cur++;
        remove_empty();
        return res;
    }

    bool hasNext() {
        return cur != iters.end();
    }

    void remove_empty() {
        if (cur == iters.end() && iters.size())
            cur = iters.begin();
        while (cur != iters.end() && cur->first == cur->second) {
            auto next = std::next(cur);
            iters.erase(cur);
            cur = next;
            if (cur == iters.end() && iters.size())
                cur = iters.begin();
        }
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
```

or

```cpp
class ZigzagIterator {
public:
    vector<vector<int>> vs;
    vector<int> indexes;
    int curi = 0;
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        vs.push_back(v1);
        vs.push_back(v2);
        indexes = {0, 0};
    }

    int next() {
        if (hasNext()) {
            int res  = vs[curi][indexes[curi]++];
            curi = (curi + 1) % vs.size();
            return res;
        }
        else
            return -1;
    }

    bool hasNext() {
        int previ = curi;
        while (indexes[curi] == vs[curi].size()) {
            curi = (curi + 1) % vs.size();
            if (curi == previ) return false;
        }
        return true;
    }
};
```