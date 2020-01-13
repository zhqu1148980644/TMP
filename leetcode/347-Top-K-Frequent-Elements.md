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
typedef pair<int, int> Count;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counter;
        for (auto & num : nums)
            counter[num]++;

        auto cmp = [](Count & item1, Count & item2) {
            return item1.second > item2.second;
        };
        priority_queue<Count, vector<Count>, decltype(cmp)> pq(cmp);
        auto it = counter.begin();
        for (int i = 0; i < k; it++, i++)
            pq.push(make_pair(it->first, it->second));
        for (; it != counter.end(); it++) {
            pq.push(make_pair(it->first, it->second));
            pq.pop();
        }
        vector<int> res(k, 0);
        for (int i = 0; i < k; i++) {
            res[k - i - 1] = pq.top().first;
            pq.pop();
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

3. ##### hashmap with bucket sort

- Collect items into buckets based on their frequency.

```c++
#include <experimental/random>
typedef pair<int, int> Count;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counter;
        for (auto & num : nums)
            counter[num]++;
        int maxcount = 0;
        for (auto & it : counter)
            maxcount = max(maxcount, it.second);

        vector<vector<int>> buckets(maxcount + 1, vector<int>());

        for (auto & it : counter)
            buckets[it.second].push_back(it.first);

        vector<int> res;
        for (int i = buckets.size() - 1; i >=0 && res.size() < k; i--)
            res.insert(res.end(), buckets[i].begin(), buckets[i].end());

        return res;
    }
};
```