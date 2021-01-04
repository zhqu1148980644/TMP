---
title: X of a Kind in a Deck of Cards
date: 2021-01-04
---
In a deck of cards, each card has an integer written on it.

Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:

Each group has exactly X cards.
All the cards in each group have the same integer.
 

Example 1:

Input: deck = [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].
Example 2:

Input: deck = [1,1,1,2,2,2,3,3]
Output: false´
Explanation: No possible partition.
Example 3:

Input: deck = [1]
Output: false
Explanation: No possible partition.
Example 4:

Input: deck = [1,1]
Output: true
Explanation: Possible partition [1,1].
Example 5:

Input: deck = [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2].
 

Constraints:

1 <= deck.length <= 10^4
0 <= deck[i] < 10^4

#### Solutions

1. ##### hash set

```cpp
class Solution {
public:
    inline int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    bool hasGroupsSizeX(vector<int>& deck) {
        unordered_map<int, int> m;
        for (auto n : deck)
            m[n]++;
        int mins = m.begin()->second;
        for (auto [n, cnt] : m) {
            int g = gcd(cnt, mins);
            if (g != 0)
                mins = min(mins, g);
        }
        if (mins < 2) return false;
        for (auto [n, cnt] : m)
            if (cnt % mins != 0)
                return false;
        return true;
    }
};
```

or

```cpp
class Solution {
public:
    inline int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    bool hasGroupsSizeX(vector<int>& deck) {
        vector<int> count(10000);
        for (auto n : deck)
            count[n]++;
        
        int g = -1;
        for (int i = 0; i < 10000; i++)
            if (count[i])
                if (g == -1)
                    g = count[i];
                else
                    g = gcd(g, count[i]);

        return g >= 2;
    }
};
```