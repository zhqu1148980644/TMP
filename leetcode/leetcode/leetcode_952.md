---
title: Largest Component Size by Common Factor
date: 2021-01-04
---
Given a non-empty array of unique positive integers A, consider the following graph:

There are A.length nodes, labelled A[0] to A[A.length - 1];
There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.
Return the size of the largest connected component in the graph.

 

Example 1:

Input: [4,6,15,35]
Output: 4

Example 2:

Input: [20,50,9,63]
Output: 2

Example 3:

Input: [2,3,6,7,4,12,21,39]
Output: 8

Note:

1 <= A.length <= 20000
1 <= A[i] <= 100000

#### Solutions

1. ##### UnionFind O(n * sqrt(max))

- For each number connect it's all factors(>1) with himself, then all numbers has overlapping factors will be merge into a community.
- There are two ways to count the size of each community.
    - One is by directly counting the appearance of each father(community) node.
    - Another solution is to reuse the size array in UnionFind, however, only the given numbers can be set with size 1 initially(insetead of setting all nodes with size 1 in ordinary UnionFind method).

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        return node;
    }
    int merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return sizes[f1];
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
        return sizes[f2];
    }
};
class Solution {
public:

    int largestComponentSize(vector<int>& A) {
        int maxv = *max_element(A.begin(), A.end());
        UnionFind uf(maxv + 1);
        for (auto n : A)
            uf.sizes[n]++;

        int res = 0;
        for (auto n : A)
            for (int i = 2; i * i <= n; i++)
                if (n % i == 0) {
                    res = max(res, uf.merge(n, i));
                    res = max(res, uf.merge(n, n / i));
                }

        return res;
    }
};
```

- Instead of traversing all possible factors below sqrt(n), we can restrict the searching range to prime numbers.

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        return node;
    }
    int merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return sizes[f1];
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
        return sizes[f2];
    }
};
class Solution {
public:
    vector<int> get_primes(int n) {
        if (n < 2) return {};
        vector<int> primes;
        vector<bool> vis(n);
        vis[0] = vis[1] = true;
        for (int i = 2; i < n; i++) {
            if (!vis[i])
                primes.push_back(i);
            for (int j = 0; j < primes.size() && i * primes[j] < n; j++) {
                vis[i * primes[j]] = true;
                if (i % primes[j] == 0)
                    break;
            }
        }

        return primes;
    }
    int largestComponentSize(vector<int>& A) {
        int maxv = *max_element(A.begin(), A.end());
        auto primes = get_primes(sqrt(maxv) + 1);
        UnionFind uf(maxv + 1);
        for (auto n : A)
            uf.sizes[n]++;

        int res = 0;
        for (auto n : A) {
            int back = n;
            for (auto p : primes) {
                if (p >= n) break;
                if (n % p == 0) {
                    res = max(res, uf.merge(back, p));
                    while (n % p == 0)
                        n /= p;
                }
            }
            if (n != 1 && n != back)
                res = max(res, uf.merge(back, n));
        }
        return res;
    }
};
```


or connect numbers while filtering nonprime numbers(Can not use euler seives). `O(max(n)*loglog(max(n))) + n`

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        return node;
    }
    int merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return sizes[f1];
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
        return sizes[f2];
    }
};
class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        int n = *max_element(A.begin(), A.end()) + 1;
        UnionFind uf(n + 1);
        for (auto n : A)
            uf.sizes[n]++;

        int res = 0;
        vector<bool> isprime(n, true);
        //  Eratosthenes sieves
        for (int i = 2; i < n; i++) {
            if (!isprime[i]) continue;
            for (int j = i + i; j < n; j += i) {
                if (uf.sizes[j])
                    res = max(res, uf.merge(j, i));
                isprime[j] = false;
            }
        }

        return res;
    }
};
```