#### There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.

```
Example 1:

Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.

Example 2:

Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
```

#### Note:

-    N is in range [1,200].
-    M[i][i] = 1 for all students.
-    If M[i][j] = 1, then M[j][i] = 1.

#### Solutions

- Treat the adjacent matrix as a graph contains only N(N students) nodes.

1. ##### dfs O(n2) S(n)

```c++
class Solution {
public:
    void dfs(int i, vector<vector<int>> & M, vector<bool> & visited) {
        for (int j = 0; j < M.size(); j++) {
            if (!visited[j] && M[i][j]) {
                visited[j] = true;
                dfs(j, M, visited);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& M) {
        vector<bool> visited(M.size(), false);
        int num_com = 0;
        for (int i = 0; i < M.size(); i++)
            if (!visited[i]) {
                // visited[i] = true; // this is not compulsory
                dfs(i, M, visited);
                num_com++;
            }
        return num_com;
    }
};
```


2. ##### bfs O(n2) S(n)

```c++
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        queue<int> q;
        int num_com = 0;
        vector<bool> visited(M.size());

        for (int i = 0; i < M.size(); i++) {
            if (visited[i]) continue;
            // visited[i] = true; // this is not compulsory
            q.push(i);
            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                for (int j = 0; j < M.size(); j++) {
                    if (!visited[j] && M[cur][j]) {
                        visited[j] = true;
                        q.push(j);
                    }
                }
            }
            num_com++;
        }

        return num_com;
    }
};
```

3. ##### Union Find O(n2) S(n)

```c++
class UnionFind {
private:
    int * nodes;
    int * sizes;
public:
    UnionFind(int size) {
        nodes = new int[size];
        sizes = new int[size];
        for (int i = 0; i < size; i++) {
            nodes[i] = i;
            sizes[i] = 1;
        }
    }
    ~UnionFind() {
        delete [] nodes; delete [] sizes;
    }
    int find(int node) {
        while (nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
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
    int findCircleNum(vector<vector<int>>& M) {
        UnionFind uf(M.size());
        int num_com = M.size();
        for (int i = 0; i < M.size(); i++)
            for (int j = i; j < M.size(); j++)
                if (M[i][j] && uf.merge(i, j))
                    num_com--;

        return num_com;
    }
};
```