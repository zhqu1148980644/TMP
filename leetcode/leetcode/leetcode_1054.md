---
title: Distant Barcodes
date: 2021-01-04
---
In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].

Rearrange the barcodes so that no two adjacent barcodes are equal.  You may return any answer, and it is guaranteed an answer exists.

 

Example 1:

Input: [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]
Example 2:

Input: [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,2,1,2,1]
 

Note:

1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000

##### Solutions

1. ##### tree map/priority_queue O(2nlog(n))

- At each step, put two distinct elements with the largest counts.

```cpp
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> count;
        for (auto n : barcodes) count[n]++;

        set<pair<int, int>, greater<>> s;
        for (auto [n, cnt] : count) s.emplace(cnt, n);

        int w = 0;
        while (w < barcodes.size()) {
            auto [c1, n1] = *s.begin(); s.erase(s.begin());
            barcodes[w++] = n1;
            if (s.size()) {
                auto [c2, n2] = *s.begin(); s.erase(s.begin());
                barcodes[w++] = n2;
                if (--c2 > 0) s.emplace(c2, n2);
            }
            if (--c1 > 0) s.emplace(c1, n1);
        }

        return barcodes;
    }
};
```

2. ##### sorting

- directly puting elements from the largest count to the smallest with two ajacent elements separated by anothor element.
- How to prove the correctness.

```cpp
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> m;
        for (auto n : barcodes) m[n]++;

        sort(barcodes.begin(), barcodes.end(), [&m](int n1, int n2) {
            return m[n1] != m[n2] ? m[n1] > m[n2] : n1 > n2;
        });

        vector<int> res(barcodes);
        int w = 0, size = barcodes.size();
        int l = 0, mid = (barcodes.size() + 1) / 2, r = mid;
        while (r < size) {
            res[w++] = barcodes[l++];
            res[w++] = barcodes[r++];
        }
        if (l < mid) res[w++] = barcodes[l];

        return res;
    }
};
``