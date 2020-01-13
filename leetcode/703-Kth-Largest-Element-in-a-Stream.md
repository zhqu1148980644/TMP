#### Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Your KthLargest class will have a constructor which accepts an integer k and an integer array nums, which contains initial elements from the stream. For each call to the method KthLargest.add, return the element representing the kth largest element in the stream.

```
Example:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8
```

#### Note:
You may assume that nums' length ≥ k-1 and k ≥ 1.

#### Solutions

1. ##### min stack push/pop O(log(n))

```c++
class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> pq;
    int maxsize;
public:
    KthLargest(int k, vector<int>& nums) : maxsize(k) {
        for (auto & num : nums) {
            pq.push(num);
            if (pq.size() > maxsize)
                pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if (pq.size() > maxsize)
            pq.pop();
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
```


2. ##### multiset insert/delete O(log(n))

- reference: https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/solution/703-shu-ju-liu-zhong-de-di-kda-yuan-su-liang-chong/

```c++
class KthLargest {
private:
    multiset<int> m;
    int maxsize;
public:
    KthLargest(int k, vector<int>& nums) : maxsize(k) {
        for (auto & num : nums) {
            m.insert(num);
            if (m.size() > maxsize)
                m.erase(m.begin());
        }
    }
    
    int add(int val) {
        m.insert(val);
        if (m.size() > maxsize)
            m.erase(m.begin());
        return *m.begin();
    }
};

```