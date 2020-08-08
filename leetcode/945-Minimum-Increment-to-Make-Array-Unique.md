Given an array of integers A, a move consists of choosing any A[i], and incrementing it by 1.

Return the least number of moves to make every value in A unique.

 

```
Example 1:

Input: [1,2,2]
Output: 1
Explanation:  After 1 move, the array could be [1, 2, 3].

Example 2:

Input: [3,2,1,2,1,7]
Output: 6
Explanation:  After 6 moves, the array could be [3, 4, 1, 2, 5, 7].
It can be shown with 5 or less moves that it is impossible for the array to have all unique values.
```
 

#### Note:

    0 <= A.length <= 40000
    0 <= A[i] < 40000


##### Solutions


1. ##### counting O(range)

- Use buckets to store each unique value.

```c++
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        vector<int> buckets(100000);
        for (auto & n : A)
            buckets[n]++;
        
        int remain = 0, res = 0;
        for (int i = 0; i < 100000; i++) {
            if (buckets[i] >= 2) {
                remain += buckets[i] - 1;
                res -= i * (buckets[i] - 1);
            } else if (remain && buckets[i] == 0) {
                remain--;
                res += i;
            }
        }

        return res;
    }
};
```

2. ##### sort/greedy O(nlog(n))

```c++
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        if (!A.size()) return 0;
        sort(A.begin(), A.end());

        int prev = A[0], steps = 0;
        for (int i = 1; i < A.size(); i++) {
            if (A[i] <= prev)
                steps += prev++ - A[i] + 1;
            else
                prev = A[i];
        }
        
        return steps;
    }
};
```


3. ##### UnionFind

- reference: https://leetcode-cn.com/problems/minimum-increment-to-make-array-unique/solution/tan-xin-suan-fa-bing-cha-ji-java-by-liweiwei1419/
- Merge connected nodes(Has no space within) with the highest number, then the next time a duplicate(within the community) element is meeted, the next available empty space can be find in `O(1)` time.
- There is one change should be made: when merging two groups, always merge the smaller one to the larger one.



```c++
struct UnionFind {
    vector<int> nodes;
    UnionFind(int size, int initial = -1) : nodes(size) {
        if (initial == -1)
            iota(nodes.begin(), nodes.end(), 0);
        else
            fill(nodes.begin(), nodes.end(), initial);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        //  merger the smaller to the larger
        if (f1 > f2) swap(f1, f2);
        nodes[f1] = f2;
        return true;
    }
};

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        // creat an empty node repsents all elements are empty now
        int empty = 99999;
        UnionFind uf(100000, empty);

        int step = 0;
        for (auto n : A) {
            if (uf.find(n) != empty) {
                int newn = uf.find(n) + 1;
                step += newn - n;
                n = newn;
            }
            uf.nodes[n] = n;
            if (n - 1 >= 0 && uf.find(n - 1) != empty)
                uf.merge(n - 1, n);
            if (uf.find(n + 1) != empty)
                uf.merge(n, n + 1);    
        }

        return step;
    }
};
```