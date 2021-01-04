---
title: Reorganize String
date: 2021-01-04
---
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

If possible, output any possible result.  If not possible, return the empty string.

Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""
Note:

S will consist of lowercase letters and have length in range [1, 500].

#### Solutions

1. ##### greedy strategy priority queue

- Return false if the `max(count)` of all characters is larger than `(n + 1) / 2`;
    - It seems like all strings with `max(count) <= (n + 1) / 2` can yield valid results.
    - How to prove?
- Iteratively add two different characters that with the highest frequency.

```cpp
class Solution {
public:
    string reorganizeString(string S) {
        int n = S.size();
        vector<int> count(26);
        for (auto c : S)
            if (++count[c - 'a'] > (n + 1 ) / 2)
                return "";

        using pic =  pair<int, char>;
        priority_queue<pic, vector<pic>> pq;
        for (int i = 0; i < 26; i++)
            if (count[i]) pq.emplace(count[i], i + 'a');

        string res;
        while (pq.size() >= 2) {
            auto [n1, c1] = pq.top(); pq.pop();
            auto [n2, c2] = pq.top(); pq.pop();
            // no need to check if c1 == res.back()
            // For example: a, b are characters puted last time
            // In the current time, by any means, b will not shown before a, as both count and lexi order are small or eq than a.
            res += c1; res += c2;
            if (n1 - 1) pq.emplace(n1 - 1, c1);
            if (n2 - 1) pq.emplace(n2 - 1, c2);
        }
        // This piece of code be repalced by res += pq.top().second. No idea how to prove it.
        if (pq.size()) {
            if ((res.size() && res.back() == pq.top().second) 
                || pq.top().first > 1)
                return "";
            else
                res += pq.top().second;
        }

        return res;
    }
};
```


2. ##### greedy strategy with sort

- Iteratively putting the same character with another character spaced. As there is only one possiblity when `max(count) == (n + 1) / 2`, e.g `aba`, make sure the character with the maximum count will be putted at the last position.

```cpp
class Solution {
public:
    string reorganizeString(string S) {
        int n = S.size();
        vector<int> count(26);
        for (auto c : S)
            if (++count[c - 'a'] > (n + 1 ) / 2)
                return "";
        vector<pair<int, int>> avail;

        for (int i = 0; i < 26; i++)
            if (count[i]) avail.emplace_back(count[i], i + 'a');
        // if you sort by descending order, make sure to make max(count) character is putted at the end
        // change w to 0 and reset w to 1 if w exceed
        sort(avail.begin(), avail.end());

        int w = 1;
        string res(S.size(), ' ');
        for (auto [n, c] : avail)
            for (int i = 0; i < n; i++, w += 2) {
                if (w >= S.size()) w = 0;
                res[w] = c;
            }

        return res;
    }
};
```