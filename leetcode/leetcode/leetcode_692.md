---
title: Top K Frequent Words
date: 2021-01-04
---
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.

#### Solutions

- Similar to `problem 347 Top K frequent elements`.

1. ##### count sort O(n + klog(k))


```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> count;
        int maxc = INT_MIN;
        for (auto & s : words)
            maxc = max(maxc, ++count[s]);

        int n = maxc + 1;
        vector<vector<const string*>> buckets(n);
        for (auto & [w, c] : count)
            buckets[c].push_back(&w);
        
        vector<string> res;
        for (int i = maxc; i >= 0 && res.size() < k; i--) {
            for (auto p : buckets[i])
                res.push_back(*p);
        }
        
        sort(res.begin(), res.end(), [&count](auto & s1, auto & s2) {
            if (count[s1] == count[s2])
                return s1 < s2;
            else
                return count[s1] > count[s2];
        });

        return {res.begin(), res.begin() + k};
    }
};
```


2. ##### heap O(nlog(k))

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> m;
        for (auto & s : words)
            m[s]++;
        using mit = unordered_map<string, int>::iterator;
        auto greater = [&m](auto it1, auto it2) {
            if (it1->second == it2->second)
                return it1->first < it2->first;
            else
                return it1->second > it2->second; 
        };

        priority_queue<mit, vector<mit>, decltype(greater)> pq(greater);
        auto it = m.begin();
        for (int i = 0; i < k; i++)
            pq.push(it++);
        for (int i = k; i < m.size(); i++) {
            pq.push(it++);
            pq.pop();
        }

        vector<string> res;
        while (!pq.empty()) {
            res.push_back(pq.top()->first);
            pq.pop();
        }

        return {res.rbegin(), res.rend()};
    }
};
```


3. ##### quick partition O(n + klog(k))

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string_view, int> m;
        for (auto & w : words) m[w]++;
        vector<string_view> vs;
        for (auto & [s, c] : m)
            vs.push_back(s);
        auto cmp = [&] (auto & s1, auto & s2) {
            int c1 = m[s1], c2 = m[s2];
            return c1 == c2 ? s1 < s2 : c1 > c2;
        };
        nth_element(vs.begin(), vs.begin() + k, vs.end(), cmp);
        vs.resize(k);
        sort(vs.begin(), vs.end(), cmp);

        vector<string> res;
        for (auto & s : vs) res.push_back(string(s));

        return res;
    }
};
```