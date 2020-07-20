Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note:
You may assume k is always valid, 1 ≤ k ≤ n2.

#### Solutions


1. ##### merge sorted array O(klog(n)) worst(n2log(n))

```c++
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        priority_queue<tuple<int, int, int>> pq;
        for (int i = 0; i < n; i++)
            pq.emplace(-matrix[i][0], i, 0);
        
        while (--k) {
            auto [val, x, y] = pq.top(); pq.pop();
            if (y + 1 < n)
                pq.emplace(-matrix[x][y + 1], x, y + 1);
        }

        return -get<0>(pq.top());        
    }
};
```


2. ##### binary search O(nlog(hi - lo))

- Use binsearch to find the k'th smallest number. For each suspected number `mid`, if the number of elements `slower/eq` than this number is smaller than k, then it must not be the k'th smallest number, the right target must be at least(>=) `mid + 1`
- Counting the number of elements under some number could be done in `O(n)` time, which leads to `O(log(hi - lo)n)` time.

```c++
class Solution {
public:
    inline int under(vector<vector<int>> & matrix, int target) {
        int res = 0, n = matrix.size();
        int i = n - 1, j = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= target)
                j++;
            else {
                res += j; i--;
            }
        }
        if (i >= 0) res += (i + 1) * j;
        return res;
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(); if (!n) return -1;
        int lo = matrix[0][0], hi = matrix[n - 1][n - 1];
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            // under means lower or equal
            // it count of numbers under mid is slower than k, it can not be the target
            if (under(matrix, mid) < k)
                lo = mid + 1;
            else
                hi = mid;
        }

        return lo;
    }
};
```

3. ##### divide and conquer O(n)

- reference: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85201/c-on-time-on-space-solution-with-detail-intuitive-explanation && https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85170/on-from-paper-yes-orows

```c++
class Solution {
public:
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

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if (matrix.size() == 1) return matrix[0][0];
        vector<int> indices(matrix.size());
        iota(indices.begin(), indices.end(), 0);
        function<int(int, int)> fetch = [&matrix](size_t i, size_t j) {
            return matrix[i][j];
        };
        auto [res, _] = biselect(Matrix(fetch), indices, {k - 1, k - 1});

        return res;
    }
};
```