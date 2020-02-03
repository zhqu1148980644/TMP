Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y. Also two strings X and Y are similar if they are equal.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list A of strings.  Every string in A is an anagram of every other string in A.  How many groups are there?

 

```
Example 1:

Input: A = ["tars","rats","arts","star"]
Output: 2
```

 

#### Constraints:

-    1 <= A.length <= 2000
-    1 <= A[i].length <= 1000
-    A.length * A[i].length <= 20000
-    All words in A consist of lowercase letters only.
-    All words in A have the same length and are anagrams of each other.
-    The judging time limit has been increased for this question.


#### Solutions

- One way is check all pairs of words and build a graph based on their similarities. `O(n2 * l)  l: length of each word.`
- Another way is to generate all possible similar strings for each word. `O(n * l2) l: length of each word.`

1. ##### union find O(n2 * l)

- Use unordered set to dedup the input vector of words.

```c++
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
    bool similar(const string & s1, const string & s2) {
        int diff = 0;
        for (int i = 0; i < s1.size(); i++)
            if (s1[i] != s2[i] && ++diff > 2)
                return false;
        return true;
    }

    int numSimilarGroups(vector<string>& A) {
        unordered_set<string> seen(A.begin(), A.end());
        vector<string> v(seen.begin(), seen.end());

        UnionFind uf(v.size());
        int numcom = v.size();

        for (int i = 0; i < v.size(); i++)
            for (int j = i + 1; j < v.size(); j++)
                if (similar(v[i], v[j]))
                    if (uf.merge(i, j))
                        numcom--;

        return numcom;
    }
};
```


2. ##### dfs O(n2 * l)

```c++
class Solution {
public:
    vector<unordered_set<int>> g;
    vector<int> coms;

    bool similar(const string & s1, const string & s2) {
        int diff = 0;
        for (int i = 0; i < s1.size(); i++)
            if (s1[i] != s2[i] && ++diff > 2)
                return false;
        return true;
    }
    
    void dfs(int node, int id) {
        coms[node] = id;
        for (auto & outnode : g[node]) {
            if (coms[outnode] == id)
                continue;
            dfs(outnode, id);
        }
    }

    int numSimilarGroups(vector<string>& A) {
        unordered_set<string> seen(A.begin(), A.end());
        vector<string> v(seen.begin(), seen.end());

        int n = v.size();
        coms = vector<int>(n);
        g = vector<unordered_set<int>>(n);
        for (int i = 0; i < n; i++) {
            coms[i] = -1;
            for (int j = i + 1; j < n; j++)
                if (similar(v[i], v[j])) {
                    g[i].insert(j);
                    g[j].insert(i);
                }
        }

        int id = 0;
        for (int node = 0; node < n; node++)
            if (coms[node] == -1) 
                dfs(node, id++);
        
        return id;
    }
};
```