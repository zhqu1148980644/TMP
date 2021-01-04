---
title: Count Number of Teams
date: 2021-01-04
---
There are n soldiers standing in a line. Each soldier is assigned a unique rating value.

You have to form a team of 3 soldiers amongst them under the following rules:

Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
A team is valid if:  (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).

 

```
Example 1:

Input: rating = [2,5,3,4,1]
Output: 3
Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1). 
Example 2:

Input: rating = [2,1,3]
Output: 0
Explanation: We can't form any team given the conditions.
Example 3:

Input: rating = [1,2,3,4]
Output: 4
```
 

Constraints:

n == rating.length
1 <= n <= 200
1 <= rating[i] <= 10^5

#### Solutions

1. ##### enumerate all tripairs O(n3)

2. ##### enumerate all mid points O(n2)

```cpp
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int res = 0;
        for (int i = 0; i < rating.size(); i++) {
            int lscnt, lbcnt, rscnt, rbcnt;
            lscnt = lbcnt = rscnt = rbcnt = 0;
            int mid = rating[i];
            for (int l = 0; l < i; l++) {
                if (rating[l] > mid)
                    lbcnt++;
                else
                    lscnt++;
            }
            for (int r = i + 1; r < rating.size(); r++) {
                if (rating[r] > mid)
                    rbcnt++;
                else
                    rscnt++;
            }
            res += lscnt * rbcnt + lbcnt * rscnt;
        }

        return res;
    }
};
```

3. ##### FenwickTree

- Optimize the counting step(inner for-loop) in the second solution by using fenwick tree in `O(log(n))` time(Originally `O(n)`)
- Discretize ratings by mapping all ratings to their corresponding positions in the sorted array.

```cpp
//  FenwickTree template
struct FWTree {
    vector<int> sums;
    FWTree(int num) : sums(num + 1) {}
    int query(int n) {
        int sum = 0;
        while (n > 0) {
            sum += sums[n];
            n -= lowbit(n);
        }
        return sum;
    }
    void update(int n, int value) {
        while (n < sums.size()) {
            sums[n] += value;
            n += lowbit(n);
        }
    }
    int lowbit(int n) {
        return n & (-n);
    }
};

class Solution {
public:
    int numTeams(vector<int>& rating) {
        vector<int> sorted(rating);
        sort(sorted.begin(), sorted.end());
        // 1-based
        auto get_pos = [&sorted](int target) {
            return lower_bound(sorted.begin(), sorted.end(), target) - sorted.begin() + 1;
        };

        int num = rating.size();
        FWTree ft(num);
        vector<int> iless(num), imore(num), kless(num), kmore(num);

        // O(n * 3logn)
        for (int i = 0; i < num; i++) {
            int pos = get_pos(rating[i]);
            iless[i] = ft.query(pos);
            imore[i] = ft.query(num) - iless[i];
            ft.update(pos, 1);
        }
        // O(n * 3logn)
        fill(ft.sums.begin(), ft.sums.end(), 0);
        for (int i = num - 1; i >= 0; i--) {
            int pos = get_pos(rating[i]);
            kless[i] = ft.query(pos);
            kmore[i] = ft.query(num) - kless[i];
            ft.update(pos, 1);
        }
        
        int res = 0;
        for (int i = 0; i < num; i++)
            res += iless[i] * kmore[i] + imore[i] * kless[i];

        return res;
    }
};
```