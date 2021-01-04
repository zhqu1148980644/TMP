---
title: Find Latest Group of Size M
date: 2021-01-04
---
Given an array arr that represents a permutation of numbers from 1 to n. You have a binary string of size n that initially has all its bits set to zero.

At each step i (assuming both the binary string and arr are 1-indexed) from 1 to n, the bit at position arr[i] is set to 1. You are given an integer m and you need to find the latest step at which there exists a group of ones of length m. A group of ones is a contiguous substring of 1s such that it cannot be extended in either direction.

Return the latest step at which there exists a group of ones of length exactly m. If no such group exists, return -1.

 

Example 1:

Input: arr = [3,5,1,2,4], m = 1
Output: 4
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "00101", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "11101", groups: ["111", "1"]
Step 5: "11111", groups: ["11111"]
The latest step at which there exists a group of size 1 is step 4.
Example 2:

Input: arr = [3,1,5,4,2], m = 2
Output: -1
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "10100", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "10111", groups: ["1", "111"]
Step 5: "11111", groups: ["11111"]
No group of size 2 exists during any step.
Example 3:

Input: arr = [1], m = 1
Output: 1
Example 4:

Input: arr = [2,1], m = 2
Output: 2
 

Constraints:

n == arr.length
1 <= n <= 10^5
1 <= arr[i] <= n
All integers in arr are distinct.
1 <= m <= arr.length

#### Solutions

1. ##### UnionFind

- Use unionfind for checking/recording the connectivity between ajacent positions and the size of each contiguous region can also be maintained in unionfind.

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) :nodes(size), sizes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }  
    int find(int node) {
        return nodes[node] == node ? node : (nodes[node] = find(nodes[node]));
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size(), res = -1, num = 0, step = 1;
        // different to ordinary UnionFind, we firstly set sizes of all node to 0
        UnionFind uf(n + 1);
        for (auto index : arr) {
            if (uf.sizes[index]) continue;
            uf.sizes[index]++;
            // check if can be connected with neighbors
            for (auto nei : {index - 1, index + 1}) {
                if (nei < 1 || nei > n) continue;
                int ns = uf.sizes[uf.find(nei)];
                if (ns <= 0) continue;
                // if neighbors's size == m, record the last position
                if (ns == m && --num == 0)
                    res = max(step - 1, res);
                uf.merge(index, nei);
            }
            // if the current step's size == m. record
            if (uf.sizes[uf.find(index)] == m) {
                num++; res = max(step, res);
            }
            step++;
        }

        return num > 0 ? step - 1 : res;
    }
};
```

- Another approach is to reverse the whole process, then the first time encountered regions with size equal to `m` is the answer.