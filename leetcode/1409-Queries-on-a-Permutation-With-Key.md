Given the array queries of positive integers between 1 and m, you have to process all queries[i] (from i=0 to i=queries.length-1) according to the following rules:

In the beginning, you have the permutation P=[1,2,3,...,m].
For the current i, find the position of queries[i] in the permutation P (indexing from 0) and then move this at the beginning of the permutation P. Notice that the position of queries[i] in P is the result for queries[i].
Return an array containing the result for the given queries.

 
```
Example 1:

Input: queries = [3,1,2,1], m = 5
Output: [2,1,2,1] 
Explanation: The queries are processed as follow: 
For i=0: queries[i]=3, P=[1,2,3,4,5], position of 3 in P is 2, then we move 3 to the beginning of P resulting in P=[3,1,2,4,5]. 
For i=1: queries[i]=1, P=[3,1,2,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,3,2,4,5]. 
For i=2: queries[i]=2, P=[1,3,2,4,5], position of 2 in P is 2, then we move 2 to the beginning of P resulting in P=[2,1,3,4,5]. 
For i=3: queries[i]=1, P=[2,1,3,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,2,3,4,5]. 
Therefore, the array containing the result is [2,1,2,1].  
Example 2:

Input: queries = [4,1,2,2], m = 4
Output: [3,1,2,0]
Example 3:

Input: queries = [7,5,5,8,3], m = 8
Output: [6,5,0,7,5]
```

Constraints:

1 <= m <= 10^3
1 <= queries.length <= m
1 <= queries[i] <= m

#### Solutions

1. ##### map

```c++
class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> v(m + 1);
        for (int i = 1; i < m + 1; i++)
            v[i] = i - 1;
        
        vector<int> res;
        for (auto q : queries) {
            res.push_back(v[q]);
            for (int i = 1; i < m + 1; i++) {
                if (v[i] < v[q]) v[i]++;
            }
            v[q] = 0;
        }
        
        return res;
        
    }
};
```

2. ##### linked list

- Simulate the whole process using linked list with `O(1)` insertion(push_front) cost;

```c++
class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        list<int> permut;
        for (int i = 1; i <= m; i++)
            permut.push_back(i);
        
        vector<int> res;
        for (auto q : queries) {
            auto findit = permut.begin();
            int index = 0;
            while (*findit != q) {
                findit++;
                index++;
            }
            res.push_back(index);
            permut.erase(findit);
            permut.push_front(q);
        }

        return res;
    }
};
```

3. ##### FenwickTree O(nlog(n))

- reference: https://leetcode-cn.com/problems/queries-on-a-permutation-with-key/comments/343837
- Use fenwick tree to fetch the index of each query number by counting the number of elements before it in `O(log(n))` time.
- In order to simulate the insertion process, additional space are reserved at the front of the fenwicktree.

```c++
// FenwickTree template
struct FenwickTree {
    vector<int> nums;
    FenwickTree(int n) : nums(n + 1) {}
    void update(int i, int delta) {
        while (i < nums.size()) {
            nums[i] += delta;
            i += lowbit(i);
        }
    }
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += nums[i];
            i -= lowbit(i);
        }
        return sum;
    }
    static int lowbit(int n) {
        return n & (-n);
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        FenwickTree ft(queries.size() + m); // addtional queries.size() positions for insertion
        vector<int> lookup(m + 1);
        int insert_pos = queries.size();
        for (int i = 1; i <= m; i++) {
            ft.update(i + insert_pos, 1);
            lookup[i] = i + insert_pos;
        }

        vector<int> res;
        for (auto q : queries) {
            res.push_back(ft.query(lookup[q]) - 1); // convert 1-based index to 0-based.
            ft.update(lookup[q], -1); // 1 - 1 = 0. indexes of numbers after q remain unchanged
            ft.update(lookup[q] = insert_pos--, 1); // indexes of numbers before q are increased by 1
        }
        return res;
    }
};
```