---
title: Kill Process
date: 2021-01-04
---
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).

Each process only has one parent process, but may have one or more children processes. This is just like a tree structure. Only one process has PPID that is 0, which means this process has no parent process. All the PIDs will be distinct positive integers.

We use two list of integers to represent a list of processes, where the first list contains PID for each process and the second list contains the corresponding PPID.

Now given the two lists, and a PID representing a process you want to kill, return a list of PIDs of processes that will be killed in the end. You should assume that when a process is killed, all its children processes will be killed. No order is required for the final answer.

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.
Note:
The given kill id is guaranteed to be one of the given PIDs.
n >= 1.

#### Solutions

1. ##### bfs search

```cpp
class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < ppid.size(); i++)
            m[ppid[i]].push_back(pid[i]);
        
        vector<int> res;
        queue<int> q; q.push(kill);
        while (!q.empty()) {
            res.push_back(q.front());
            if (m.count(q.front()))
                for (auto child : m[q.front()])
                    q.push(child);
            q.pop();
        }
        return res;
    }
};
```


2. ##### UnionFind

```cpp
struct UnionFind {
    vector<int> nodes;
    UnionFind(int size) : nodes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        while(nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
        return node;
    }
    void merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 != f2) nodes[f1] = f2;
    }
};

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, int> m;
        int i = 0;
        for (auto & p : pid)
            m[p] = i++;
        m[0] = i++;

        UnionFind uf(i);
        for (int i = 0; i < pid.size(); i++) {
            if (pid[i] == kill) continue;
            uf.merge(m[pid[i]], m[ppid[i]]);
        }

        vector<int> res;
        int killnode = m[kill];
        for (int i = 0; i < pid.size(); i++)
            if(uf.find(m[pid[i]]) == killnode)
                res.push_back(pid[i]);
        
        return res;
    }
};
```