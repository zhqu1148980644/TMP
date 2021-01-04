---
title: Sentence Similarity II
date: 2021-01-04
---
Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

```
For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.

Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
```

#### Note:

-    The length of words1 and words2 will not exceed 1000.
-    The length of pairs will not exceed 2000.
-    The length of each pairs[i] will be 2.
-    The length of each words[i] and pairs[i][j] will be in the range [1, 20].


#### Solutions

1. ##### Union Find O(n) S(numwords * wordlen) n: number of pairs

- Make sure the id for unseen words are reversed.

```cpp
struct UnionFind {
    int * nodes;
    int * sizes;
    UnionFind(int size) {
        nodes = new int[size];
        sizes = new int[size];
        for (int i = 0; i < size; i++) {
            nodes[i] = i;
            sizes[i] = 1;
        }
    }
    int find(int node) {
        while (nodes[node] != node) {
            nodes[node] = nodes[nodes[node]];
            node = nodes[node];
        }
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1);
        int f2 = find(node2);
        if (f1 == f2)
            return false;
        else {
            if (sizes[f1] > sizes[f2])
                swap(f1, f2);
            nodes[f1] = f2;
            sizes[f2] += sizes[f1];
            return true;
        }
    }
};

class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        if (words1.size() != words2.size())
            return false;
        unordered_map<string, int> dict;
        // id 0 represents unseen words.
        int id = 1;
        for (auto & v : pairs) {
            for (auto & w : v)
                if (!dict.count(w))
                    dict[w] = id++;
        }

        UnionFind uf(id);

        for (auto & v : pairs)
            uf.merge(dict[v[0]], dict[v[1]]);

        for (int i = 0; i < words1.size(); i++) {
            if (uf.find(dict[words1[i]]) != uf.find(dict[words2[i]]))
                return false;
        }

        return true;
    }
};
```

2. ##### dfs


```cpp
class Solution {
public:
    unordered_map<string, unordered_set<string>> g;
    unordered_map<string, int> coms;
    void dfs(const string & w, int id) {
        coms[w] = id;
        for (auto & ow : g[w])
            if (coms[ow] != id)
                dfs(ow, id);
    }
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        if (words1.size() != words2.size())
            return false;
        
        for (auto & v : pairs) {
            g[v[0]].insert(v[1]);
            g[v[1]].insert(v[0]);
            coms[v[0]] = coms[v[1]] = -1;
        }
        int id = 1;
        for (auto & v : pairs)
            for (auto & w : v) {
                if (coms[w] == -1)
                    dfs(w, id++);
            }
        
        for (int i = 0; i < words1.size(); i++) {
            auto & w1 = words1[i];
            auto & w2 = words2[i];
            if (w1 == w2) continue;
            if (!coms.count(w1) || !coms.count(w1) || coms[w1] != coms[w2])
                return false;
        }

        return true;
    }
};
```