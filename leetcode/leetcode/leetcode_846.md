---
title: Hand of Straights
date: 2021-01-04
---
Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.

Return true if and only if she can.

 

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.
 

Constraints:

1 <= hand.length <= 10000
0 <= hand[i] <= 10^9
1 <= W <= hand.length
Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/

#### Solutions

1. ##### sort then group wors

- Note : The test case are flawless, method(the first codes below) uses lenear scanning would get TLE when the inputs contains too much duplicates. Check problem 1296 fot this kind of test case.

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        if (hand.size() % W) return false;

        sort(hand.begin(), hand.end());
        vector<bool> visited(hand.size());
        // this would lead to O(n2) time complexity when there too many duplicates
        for (int j = hand.size() - 1; j >= 0; j--) {
            if (visited[j]) continue;
            int n = hand[j], k = W - 1;
            for (int i = j - 1; i >= 0 && k > 0; i--)
                if (!visited[i]) {
                    if (hands[j] != n + 1)
                        return false;
                    n--; k--;
                    visited[i] = true;
                }
            if (k) return false;
        }
        return true;
    }
};
```

one possible solution is to prededuplicate the array.

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        if (hand.size() % W) return false;
        unordered_map<int, int> m;
        for (auto n : hand) m[n]++;
        if (m.size() < W) return false;

        vector<int> v(m.size());
        int w = 0;
        for (auto [n, cnt] : m)
            v[w++] = n;
        sort(v.begin(), v.end());
        
        int i = 0;
        while (i < v.size()) {
            if (!m[v[i]] && ++i) continue;
            int n = v[i], j = i + 1;
            for (int curk = 1; curk < W; curk++) {
                if (j < v.size() && m[v[j]] && v[j] == n + 1) {
                    n++; m[v[j++]]--;
                }
                else return false;
            }
            if (--m[v[i]] == 0) i++;
        }

        return true;
    }
};
```

2. ##### tree map O(nlog(n))


```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        map<int, int> m;
        for (auto n : hand) m[n]++;
        auto it = m.begin();
        while (it != m.end()) {
            int n = it->first;
            auto nit = next(it);
            for (int k = 1; k < W; k++) {
                if (nit != m.end() && nit->first == n + 1) {
                    if (--nit->second == 0)
                        nit = m.erase(nit);
                    else
                        nit++;
                    n++;
                }
                else return false;
            }
            if (--it->second == 0)
                it++;
        }
        return true;
    }
};
```

or

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        map<int, int> m;
        for (auto n : hand) m[n]++;

        while (m.size()) {
            int first = m.begin()->first;
            for (int card = first; card < first + W; card++) {
                if (!m.count(card)) return false;
                if (--m[card] == 0) m.erase(card);
            }
        }
        return true;
    }
};
```

3. ##### sort

- reference: https://leetcode-cn.com/problems/hand-of-straights/solution/mei-ri-suan-fa-day-103-lao-ti-xin-zuo-ji-hu-bu-hui/

```cpp
class Solution {
public:
    bool valid(vector<int> & counts, int W) {
        int len = counts.size(), need = 0;
        vector<int> deltas(len);

        for (int i = 0; i < len; i++) {
            need += deltas[i];
            if (counts[i] > need) {
                int delta = counts[i] - need;
                need = counts[i];
                // The end of new appended heads of consecutive sequences are recorded.
                if (i + W < len) deltas[i + W] -= delta;
            }
            else if (counts[i] < need)
                return false;
        }
        return true;
    }    
    bool isNStraightHand(vector<int>& hand, int W) {
        if (hand.size() % W) return false;
        sort(hand.begin(), hand.end());
        vector<int> counts;
        int i = 0, len = hand.size();
        while (i < len) {
            int j = i + 1;
            while (j < len && hand[j] == hand[i]) j++;
            counts.push_back(j - i);
            if (j < len && hand[j] != hand[j - 1] + 1)
                // push_back 0 as the mark of ending of consecutive sequence
                counts.push_back(0);
            i = j;
        }
        counts.push_back(0);

        return valid(counts, W);
    }
};
```