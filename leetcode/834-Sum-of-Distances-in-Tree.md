An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.

The ith edge connects nodes edges[i][0] and edges[i][1] together.

Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.

```
Example 1:

Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: 
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.
```
Note: 1 <= N <= 10000


#### Solutions

1. ##### dynamic programming O(n)

- Borrowed from official answer.
- Suppose `x` and `y` are two neighboring node. ie: linked by a single edge.
- `X` and `Y` are two disjoint subtree rooted at `x/y` and `X | Y = Tree && X & Y = 0`
- `sum(y)` is the sum of distances between every node in subtree `Y` and the root node `y`.
- `count(y)` is the total number of nodes in subtree `Y`.
    - Then `ans[x] = sum(x) + sum(y) + count(y)`
    - if `x` is the parent node of `y` and `ans[x]` is available, according to the formula above, `ans[y]` can be calculated as `ans[y] = ans[x] + sum(x) - sum(y)`
- We use dfs to update `count` and `sum` in a bottom-up way.
- After the first dfs, `sum(0)` equals to `ans[0]`, thus we can do dfs the second time and update `ans[i]` in a top-down manner with the second formula mentioned above.


```c++
class Solution {
public:
    vector<int> count;
    vector<int> dis;
    vector<unordered_set<int>> g;

    void dfs(int node, int parent) {
        for (auto child : g[node]) {
            if (child != parent) {
                dfs(child, node);
                count[node] += count[child];
                dis[node] += dis[child] + count[child];
            }
        }
    }
    void dfs(int node, int parent, int N) {
        for (auto child : g[node]) {
            if (child != parent) {
                dis[child] = dis[node] + (N - count[child]) - count[child];
                dfs(child, node, N);
            }
        }
    }
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        g = vector<unordered_set<int>>(N);
        for (auto & e : edges) {
            g[e[0]].insert(e[1]);
            g[e[1]].insert(e[0]);
        }

        dis = vector<int>(N);
        count = vector<int>(N, 1);
        dfs(0, -1);
        dfs(0, -1, N);

        return dis;
    }
};
```