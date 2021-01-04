---
title: K th Smallest Prime Fraction
date: 2021-01-04
---
A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, we consider the fraction p/q.

What is the K-th smallest fraction considered?  Return your answer as an array of ints, where answer[0] = p and answer[1] = q.

Examples:
Input: A = [1, 2, 3, 5], K = 3
Output: [2, 5]
Explanation:
The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
The third fraction is 2/5.

Input: A = [1, 7], K = 1
Output: [1, 7]
Note:

A will have length between 2 and 2000.
Each A[i] will be between 1 and 30000.
K will be between 1 and A.length * (A.length - 1) / 2.

#### Solutions

- Similar to `problem 719 378 373`

1. ##### binary search O(log(1e7)n) == O(cn)

- Bisearch for the k'th fraction. Count the number of fractions smaller thant the supposed fraction, if the count is larger than k, the supposed fraction must be overestimated.
- Note that for every denominater in the array, it's possible fractions are in mono-increasing order in accordance with the forwading of numerator from the front;


```cpp
class Solution {
public:
    pair<int, pair<int, int>> under(vector<int> & nums, double frac) {
        int i = 0, res = 0, numer = 0, denom = 0;
        double maxf = 0;
        for (int j = 1; j < nums.size(); j++) {
            while ((double)nums[i] / nums[j] < frac)
                i++;
            if (i > 0 && (double)nums[i - 1] / nums[j] > maxf) {
                maxf = (double)nums[i - 1] / nums[j];
                numer = nums[i - 1]; denom = nums[j];
            }
            res += i;
        }
        return {res, {numer, denom}};
    }
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        pair<int, int> res;
        double lo = 0, hi = 1;
        while (hi - lo > 1e-7) {
            double mid = lo + ((hi - lo) / 2);
            auto [num, maxf] = under(A, mid);
            if (num <= K) {
                lo = mid;
                res = maxf;
            }
            else
                hi = mid;
        }

        return {res.first, res.second};
    }
};
```

2. ##### priority queue O(Klog(n))

- Get TLE.
- This approach is conceptually similar to merge multiple sorted lists. Heads of lists are `1 / allnumbers`.
- Depending on the size of K, it may be more efficient to gradually append new factions.

```cpp
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        priority_queue<tuple<double, int, int>> pq;
        for (int i = 1; i < A.size(); i++)
            pq.emplace(-(double)A[0] / A[i], 0, i);

        while (--K) {
            auto [f, di, ni] = pq.top();
            pq.pop();
            if (di + 1 < ni)
                pq.emplace(-(double)A[di + 1] / A[ni], di + 1, ni);
        }
        auto [f, di, ni] = pq.top();

        return {A[di], A[ni]};
    }
};
```

or

```cpp
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        priority_queue<tuple<double, int, int>> pq;
        pq.emplace(-(double)A[0] / A.back(), 0, A.size() - 1);
        int curend = A.size() - 1;
        while (--K) {
            auto [f, di, ni] = pq.top();
            pq.pop();
            if (di + 1 < ni)
                pq.emplace(-(double)A[di + 1] / A[ni], di + 1, ni);
            if (di == 0 && ni == curend && curend > 1) {
                pq.emplace(-(double)A[0] / A[ni - 1], 0, ni - 1);
                curend--;
            }
        }
        auto [f, di, ni] = pq.top();

        return {A[di], A[ni]};
    }
};
```

3. ##### divide and conquer

- Treat this problem as searching tht k'th smallest fraction in the fraction 2d table with elements in both columns and rows are in ascending order.
- Then this problem is the same as `problem 378 373`, check these two problems for details.

```
    5    3    2    1
1  1/5  1/3  1/2  1/1

2  2/5  2/3  2/2  2/1

3  3/5  3/3  3/2  3/1

5  5/5  5/3  2/5  5/1

```

```cpp
template <typename T>
struct Matrix {
    using fn_type = function<T(int, int)>;
    fn_type fetch;
    Matrix(fn_type fn) : fetch(fn) {}
    T operator()(int i, int j) const {
        return fetch(i, j);
    }
};

template <typename T>
array<T, 2> _biselect(const Matrix<T> & matrix, vector<int> & indices, array<int, 2> ks) {
    vector<T> res(4); int w = 0;
    for (auto r : indices)
        for (auto c : indices)
            res[w++] = matrix(r, c);
    sort(res.begin(), res.end());
    return {res[ks[0]], res[ks[1]]};
}

template <typename T>
array<T, 2> biselect(const Matrix<T> & matrix, vector<int> & indices, array<int, 2> ks) {
    int n = indices.size(), w = 0;
    if (n <= 2) return _biselect(matrix, indices, ks);
    vector<int> indices_((n + 1) / 2 + (n % 2 == 0));
    for (int i = 0; i < n; i += 2)
        indices_[w++] = indices[i];
    if (n % 2 == 0)
        indices_[w++] = indices[n - 1];
    
    array<int, 2> ks_ = {ks[0] / 4, (n % 2) ? 
            (ks[1] + 2 * n + 1) / 4 : ks[1] / 4 + n + 1};
    // a slower version
    // int upper_bound = indices_.size() * indices_.size() - 1;
    // array<int, 2> ks_ = {ks[0] / 4, upper_bound};
    auto [x1, x2] = biselect(matrix, indices_, ks_);
    int nless = 0, nmore = 0, j1 = n, j2 = n;
    vector<T> between;
    auto M = [&](int i, int j) { return matrix(indices[i], indices[j]); };
    // less: [:x1) between: [x1:x2] more: (x2:] in the current submatrix
    // currow[indice[j1]] is the first number >= x1
    // currow[indice[j2]] is the first number >  x2
    for (int i = 0; i < n; i++) {
        while (j2 && M(i, j2 - 1) > x2) j2--;
        while (j1 && M(i, j1 - 1) >= x1) j1--;
        nmore += n - j2;
        nless += j1;
        for (int j = j1; j < j2; j++)
            between.push_back(M(i, j));
    }

    array<T, 2> xs;
    for (int i : {0, 1}) {
        T & x = xs[i];
        int k = ks[i];
        if (k < nless)
            x = x1;
        else if (k < (n * n) - nmore) {
            // should use median of midians to get the algorithm run in O(n)
            nth_element(between.begin(), between.begin() + k - nless, between.end());
            x = between[k - nless];
        }
        else
            x = x2;
    }

    return xs;
}

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int n = A.size();
        // do not reference n
        function<double(int, int)> fetch = [&A, n](int i, int j) {
            return (double)A[i] / A[n - j - 1];
        };
        if (K < n) n = max(2, K);
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        auto [maxfrac, _] = biselect(Matrix(fetch), indices, {K - 1, K - 1});
        int i = 0;
        for (int j = 1; j < A.size(); j++) {
            while ((double)A[i] / A[j] < maxfrac)
                i++;
            if ((double)A[i] / A[j] == maxfrac)
                return {A[i], A[j]};
        }
        return {0, 0};
    }
};
```