#### Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Note that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

 

#### Follow up:
Could you do both operations in O(1) time complexity?

 

```
Example:

LFUCache cache = new LFUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```


#### Solutions

1. ##### hashmap with double linked list


- Use hashmap for O(1) get/put.
- Use double linked list for O(1) updating frequency and evict least frequently used item.
- Caution: In STL's list, after adjacent items of an iterator has been removed or changed, the behavior of this iterator would change(Not as expected). So do not use `++/--` after the next/previous item is removed/changed(because of inserion).
- Graph demonstration:

![](https://ieftimov.com/golang-lfu-cache/lfu-backbone-linked-lists.png)

```
freq.begin()  frequency   key nodes
freq.begin() + 1 <5> <12, 123 ,1 12312, 1 34123>
...              <4> < 123, 123 ,4212>
...              <2> <123, 1234, 1,31>
...              <1> <35, 34, 12, 45, 12>
freq.end();
```

```c++
using Freq = list<pair<int, list<int>>>;
struct Node {
    int key, value;
    Freq::iterator freq_it;
    list<int>::iterator pos_it;
    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

class LFUCache {
public:
    Freq freq;
    unordered_map<int, Node> cache;
    const int capacity;
    LFUCache(int capacity) : capacity(capacity) {

    }
    
    int get(int key) {
        if (!cache.count(key))
            return -1;
        int res = cache[key].value;
        update(key, res);
        return res;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            if (freq.size() && cache.size() == capacity) {
                auto & items = freq.back().second;
                cache.erase(*items.begin());
                items.pop_front();
                if (items.empty())
                    freq.pop_back();
            }
            // insert a new element but with no space
            if (cache.size() >= capacity)
                return;
        }
        update(key, value);
    }
    void update(int key, int value) {
        Freq::iterator fit;
        int newfreq;
        if (cache.count(key)) {
            cache[key].value = value;
            fit = cache[key].freq_it;
            newfreq = fit->first + 1;
            fit->second.erase(cache[key].pos_it);
            if (fit->second.empty())
                // return the next iterator of the removed element
                fit = freq.erase(fit);
        }
        else {
            cache[key] = Node(key, value);
            fit = freq.end();
            newfreq = 1;
        }
        if (fit == freq.begin() || prev(fit)->first != newfreq)
            // return the iterator of the inserted element
            fit = freq.insert(fit, {newfreq, {}});
        else
            --fit;
        cache[key].freq_it = fit;
        cache[key].pos_it = fit->second.insert(fit->second.end(), key);
    }

};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```


or

```c++


```

2. ##### OrderedDict in python

- Use OrderedDict to represent double linked list to maintain the visiting order of items.

```python
from collections import OrderedDict, defaultdict
class LFUCache(dict):
    def __init__(self, capacity: int):
        self.cap = capacity
        self.freq = defaultdict(Node)
        self.start = Node(1000000000)
        self.end = Node(0, self.start)
        self.start.next = self.end

    def get(self, key: int) -> int:
        if key not in self:
            return -1
        self.update(key, self.freq[self[key]][key])

        return self.freq[self[key]][key]

    def put(self, key: int, value: int) -> None:
        if key not in self:
            if len(self) == self.cap and len(self) > 0:
                last = self.end.prev
                kv = last.popitem(last=False)
                del self[kv[0]]                
                if not last:
                    del self.freq[last.freq]
                    last.delete()
            if len(self) >= self.cap:
                return

        self.update(key, value)

    def update(self, key: int, value: int = None) -> None:
        if key in self:
            cur = self.freq[self[key]]
            nextcount = self[key] + 1
            del cur[key]
            if not cur:
                del self.freq[cur.freq]
                cur = cur.delete()
        else:
            cur = self.end
            nextcount = 1
        if cur.prev == self.start or cur.prev.freq != nextcount:
            cur = cur.insert(nextcount)
            self.freq[nextcount] = cur
        else:
            cur = cur.prev
        cur[key] = value
        self[key] = nextcount

class Node(OrderedDict):
    def __init__(self, freq, prev=None, next=None):
        self.freq = freq
        self.prev = prev
        self.next = next
    
    def delete(self):
        self.prev.next = self.next
        self.next.prev = self.prev
        return self.next

    def insert(self, freq: int):
        self.prev.next = Node(freq, self.prev, self)
        self.prev = self.prev.next
        return self.prev



# Your LFUCache object will be instantiated and called as such:
# obj = LFUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
```