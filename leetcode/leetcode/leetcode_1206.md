---
title: Design Skiplist
date: 2021-01-04
---
Design a Skiplist without using any built-in libraries.

A Skiplist is a data structure that takes O(log(n)) time to add, erase and search. Comparing with treap and red-black tree which has the same function and performance, the code length of Skiplist can be comparatively short and the idea behind Skiplists are just simple linked lists.

For example: we have a Skiplist containing [30,40,50,60,70,90] and we want to add 80 and 45 into it. The Skiplist works this way:


Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons

You can see there are many layers in the Skiplist. Each layer is a sorted linked list. With the help of the top layers, add , erase and search can be faster than O(n). It can be proven that the average time complexity for each operation is O(log(n)) and space complexity is O(n).

To be specific, your design should include these functions:

bool search(int target) : Return whether the target exists in the Skiplist or not.
void add(int num): Insert a value into the SkipList. 
bool erase(int num): Remove a value in the Skiplist. If num does not exist in the Skiplist, do nothing and return false. If there exists multiple num values, removing any one of them is fine.
See more about Skiplist : https://en.wikipedia.org/wiki/Skip_list

Note that duplicates may exist in the Skiplist, your code needs to handle this situation.

 

Example:

Skiplist skiplist = new Skiplist();

skiplist.add(1);
skiplist.add(2);
skiplist.add(3);
skiplist.search(0);   // return false.
skiplist.add(4);
skiplist.search(1);   // return true.
skiplist.erase(0);    // return false, 0 is not in skiplist.
skiplist.erase(1);    // return true.
skiplist.search(1);   // return false, 1 has already been erased.
 

Constraints:

0 <= num, target <= 20000
At most 50000 calls will be made to search, add, and erase.


#### Solutions

1. ##### redis like skiplist

- reference: http://zhangtielei.com/posts/blog-redis-skiplist.html
![schema](http://zhangtielei.com/assets/photos_redis/skiplist/redis_skiplist_example.png)
- Basically, a `skiplistNode` only needs `two` data member, one is the `key` data which is used for comparison, the other one is an array of pointers with length equals to the height of the current node(bar in the figure).
    - The height of each bar is randomly selected with probability of `(1 - p), p * (1 - p), p^2 * (1 - p) ...` for heights `1, 2, 3, 4 ...`.
    - Different `p` can change the number of elements in each level and further infulence the space costs/time complexity.
- (Not implemented) In order to support rank/rankrange selection, each zskiplistNode has another member named `span`, represents the number of nodes acrossed. `span` need to be updated during the insertion and erasion.

```cpp
static const int SKIPLIST_P_VAL = RAND_MAX / 2, MAX_LEVEL = 16;

class Skiplist {
public:
    struct Node {
        int val;
        vector<Node *> level;
        Node(int val, int size = MAX_LEVEL) : val(val), level(size) {}
    };

    Node head;
    int maxlevel = 1;
    Skiplist() : head(INT_MIN, MAX_LEVEL) {}

    ~Skiplist() {
        Node * cur = head.level[0];
        while (cur) {
            Node * next = cur->level[0];
            delete cur; cur = next;
        }
    }

    bool empty() {
        return !head.level[0];
    }
    // essentially the same as _search
    bool search(int target) {
        Node * cur = &head;
        for (int i = maxlevel - 1; i >= 0; i--)
            while (cur->level[i] && cur->level[i]->val < target)
                cur = cur->level[i];
        return cur->level[0] && cur->level[0]->val == target;
    }

    vector<Node *> _search(int key) {
        Node * cur = &head;
        vector<Node *> prevs(MAX_LEVEL);
        // through every level, from top to bottom
        for (int i = maxlevel - 1; i >= 0; i--) {
            // through elements in the current level with smaller value
            while (cur->level[i] && cur->level[i]->val < key)
                cur = cur->level[i];
            prevs[i] = cur;
        }

        return prevs;
    }

    void add(int num) {
        auto prevs = _search(num);
        int level = random_level();
        // update maxlevel and prevs
        if (level > maxlevel) {
            for (int i = maxlevel; i < level; i++)
                prevs[i] = &head;
            maxlevel = level;
        }
        Node * cur = new Node(num, level);
        // from prev->next   to   prev->cur->next
        for (int i = level - 1; i >= 0; i--) {
            cur->level[i] = prevs[i]->level[i];
            prevs[i]->level[i] = cur;
        }
        // if there is backward pointer, need to set both cur and cur.next 's back pointer
        // Note that the back poinet of the first valid node is nullptr instead of head
    }
    
    bool erase(int num) {
        auto prevs = _search(num);
        if (!prevs[0]->level[0] || prevs[0]->level[0]->val != num)
            return false;
        Node * cur = prevs[0]->level[0];
        // from prev->cur->next to prev->next
        for (int i = 0; i < maxlevel; i++)
            if (prevs[i]->level[i] == cur)
                prevs[i]->level[i] = cur->level[i];
        delete cur;
        // update maxlevel.
        while (maxlevel > 1 && !head.level[maxlevel - 1])
            maxlevel--;
        // if there is backward poinet, need to set cur.next.back to cur.back
        return true;
    }

    static int random_level() {
        int level = 1;
        while (rand() < SKIPLIST_P_VAL && level < MAX_LEVEL) level++;
        return level;
    }
};
```


