#### Given a non-empty array of integers, return the k most frequent elements.

```
Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]
```

#### Note:

-    You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
-    Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

#### Solutions

1. ##### hashmap with priority queue

```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counter;
        for (auto & num : nums)
            counter[num]++;

        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        auto it = counter.begin();
        for (int i = 0; i < k; it++, i++)
            pq.emplace(it->second, it->first);
        for (; it != counter.end(); it++) {
            pq.emplace(it->second, it->first);
            pq.pop();
        }

        vector<int> res(k);
        while (!pq.empty()) {
            res[--k] = pq.top().second; pq.pop();
        }
        return res;
    }
};
```

2. ##### hashmap with quick sort

```c++
#include <experimental/random>
typedef pair<int, int> Count;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counter;
        for (auto & num : nums)
            counter[num]++;

        vector<Count> c;
        for (auto & it : counter)
            c.push_back(make_pair(it.first, it.second));

        k = c.size() - k;
        int lo = 0, hi = c.size() - 1;
        while (lo < hi) {
            int i = lo, j = hi;
            swap(c[i], c[std::experimental::randint(i, j)]);
            auto pivot = c[i];
            while (i < j) {
                while (i < j && c[j].second >= pivot.second) j--;
                c[i] = c[j];
                while (i < j && c[i].second < pivot.second) i++;
                c[j] = c[i];
            }
            c[i] = pivot;
            if (i <= k) lo = i + 1;
            if (i >= k) hi = i - 1;
        }

        k = c.size() - k;
        vector<int> res(k, 0);
        for (int i = 0; i < k; i++) {
            res[i] = c[c.size() - i - 1].first;
        }

        return res;
    }
};
```

or

```c++
class Solution {
public:
    template <typename V>
    void move_median_to_first(V & v, int res, int a, int b, int c) {
        if (v[a] < v[b]) {
            if (v[b] < v[c])
                swap(v[res], v[b]);
            else if (v[a] < v[c])
                swap(v[res], v[c]);
            else
                swap(v[res], v[a]);
        }
        else if (v[a] < v[c])
            swap(v[res], v[a]);
        else if (v[b] < v[c])
            swap(v[res], v[c]);
        else
            swap(v[res], v[b]);
    }
    template <typename V>
    void quick_select(V & v, int lo, int nth, int hi) {
        while (lo < hi) {
            int i = lo, j = hi, mid = lo + (hi - lo) / 2;
            move_median_to_first(v, lo, lo + 1, mid, hi);
            auto pivot = v[lo];
            while (i < j) {
                while (i < j && pivot < v[j]) j--;
                v[i] = v[j];
                while (i < j && v[i] < pivot) i++;
                v[j] = v[i];
            }
            v[i] = pivot;
            if (i <= nth) lo = i + 1;
            if (i >= nth) hi = i - 1;
        }
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counter;
        for (const auto n : nums)
            counter[n]++;
        
        using pii = pair<int, int>;
        vector<pii> vp;
        for (auto & [k, v] : counter)
            vp.emplace_back(v, k);
        
        k = vp.size() - k;
        quick_select(vp, 0, k, vp.size() - 1);
        
        vector<int> res;
        for (auto it = vp.begin() + k; it != vp.end(); it++)
            res.push_back(it->second);
        
        return res;
    }
};
```

or

```c++
#include <experimental/random>
class Solution {
public:
    template <typename It, typename Cmp>
    void nth_element(It lo, It mid, It hi, Cmp && cmp) {
        typename iterator_traits<It>::difference_type zero {0};
        while (lo < hi) {
            iter_swap(lo, lo + std::experimental::randint(zero, hi - lo - 1));
            auto pivot = *lo;
            It st = lo, ed = hi - 1;
            while (st < ed) {
                while (st < ed && !cmp(*ed, pivot)) --ed;
                *st = *ed;
                while (st < ed && cmp(*st, pivot)) ++st;
                *ed = *st;
            }
            *st = pivot;
            if (!(mid < st)) lo = st + 1;
            if (!(st < mid)) hi = st;
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (auto n : nums) m[n]++;
        
        vector<int> res;
        for (auto [k, v] : m) res.push_back(k);

        nth_element(res.begin(), res.begin() + k, res.end(), 
        [&](auto n1, auto n2) {
            return m[n1] > m[n2];
        });
        
        return {res.begin(), res.begin() + k};
    }
};
```

3. ##### bucket sort with hash map

- Collect items into buckets based on their frequency.

```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int maxc = 0;
        unordered_map<int, int> counter;
        for (auto n : nums)
            maxc = max(maxc, ++counter[n]);
        
        vector<vector<int>> buckets(maxc + 1);
        
        for (auto & [k, c] : counter)
            buckets[c].push_back(k);
        
        vector<int> res;
        for (int i = buckets.size() - 1; i >= 0 && res.size() < k; i--)
            res.insert(res.end(), buckets[i].begin(), buckets[i].end());
        
        return res;
        
    }
};
```