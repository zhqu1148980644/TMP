You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:

Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]] 
Explanation: The first 3 pairs are returned from the sequence: 
             [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:

Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [1,1],[1,1]
Explanation: The first 2 pairs are returned from the sequence: 
             [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:

Input: nums1 = [1,2], nums2 = [3], k = 3
Output: [1,3],[2,3]
Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]

#### Solutions

- Similar to problem 378 and 786

1. ##### binary search O(nlog(hi - lo)) = O(cn)

- Use binary search to search for the n'th pair sum.

```c++
class Solution {
public:
    // use sliding window to count the number of pair sums <= target
    inline int under(vector<int> & nums1, vector<int> & nums2, int target) {
        int n1 = nums1.size(), n2 = nums2.size();
        int res = 0, i = 0, j = n2 - 1;
        // use sliding window strategy
        while (i < n1 && j >= 0) {
            while (j >= 0 && nums1[i] + nums2[j] > target)
                j--;
            res += j + 1;
            i++;
        }
        return res;
    }
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        if (!n1 || !n2) return {};
        int lo = nums1[0] + nums2[0], hi = nums1[n1 - 1] + nums2[n2 - 1];
        
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (under(nums1, nums2, mid) < k)
                lo = mid + 1;
            else
                hi = mid;
        }

        list<vector<int>> res;
        int i = 0, j = n2 - 1, maxsum = INT_MIN;
        while (i < n1 && j >= 0) {
            while (j >= 0 && nums1[i] + nums2[j] > lo)
                j--;
            for (int k = 0; k <= j; k++) {
                maxsum = max(maxsum, nums1[i] + nums2[k]);
                res.push_back({nums1[i], nums2[k]});
            }
            i++;
        }
        
        k = max((int)res.size() - k, 0);
        auto it = res.begin();
        while (k > 0)
            if ((*it)[0] + (*it)[1] == maxsum) {
                k--;
                it = res.erase(it);
            }
            else
                it++;
        
        return {move_iterator(res.begin()), move_iterator(res.end())};
    }
};
```

- Another perspective: binary search in virtual 2d table. i.e. Use binary search to find the k'th sum pair in a virtual 2d table whose elements are `nums[i] + nums[j]` in row i and column j and all element in the same row/column are in ascending order.
- Check the official answer in problem 378
- It's clearly that codes of this version is the same as the previous one which uses sliding window for counting, thought we see them in a different way.


```c++
class Solution {
public:
    inline int under(vector<int> & nums1, vector<int> & nums2, int target) {
        int n1 = nums1.size(), n2 = nums2.size();
        int i = 0, j = n2 - 1, res = 0;
        // for each row, find the last column with value <= target
        while (i < n1 && j >= 0) {
            while (j >= 0 && nums1[i] + nums2[j] > target)
                j--;
            res += j + 1;
            i++;
        }
        return res;
    }
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (!nums1.size() || !nums2.size()) return {};
        int n1 = nums1.size(), n2 = nums2.size();
        int lo = nums1[0] + nums2[0], hi = nums1[n1 - 1] + nums2[n2 - 1];
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (under(nums1, nums2, mid) < k)
                lo = mid + 1;
            else
                hi = mid;
        }

        list<vector<int>> res;
        int i = 0, j = n2 - 1, maxsum = INT_MIN;
        while (i < n1 && j >= 0) {
            while (j >= 0 && nums1[i] + nums2[j] > lo)
                j--;
            for (int k = 0; k <= j; k++) {
                maxsum = max(maxsum, nums1[i] + nums2[j]);
                res.push_back({nums1[i], nums2[k]});
            }
            i++;       
        }
        // or simply sort then slice[:k]
        k = max((int)res.size() - k, 0);
        auto it = res.begin();
        while (k > 0)
            if ((*it)[0] + (*it)[1] == maxsum) {
                it = res.erase(it);
                k--;
            }
            else
                it++;
        
        return {move_iterator(res.begin()), move_iterator(res.end())};
    }
};
```



2. ##### priority queue O(klog(n)) worse(O(n2log(n)))

- Similar to merge multiple sorted lists.

```c++
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (!nums1.size() || !nums2.size())
            return {};
        int n1 = nums1.size(), n2 = nums2.size();
        priority_queue<tuple<int, int, int>> pq;
        // or just put all (0, 0), (0, 1), (0, 2) ... pairs into the pq
        pq.emplace(-(nums1[0] + nums2[0]), 0, 0);

        int end2 = 0, w = 0;
        vector<vector<int>> res(k);
        while (k-- && pq.size()) {
            auto [sum, i1, i2] = pq.top(); pq.pop();
            res[w++] = {nums1[i1], nums2[i2]};
            if (i1 + 1 < n1)
                pq.emplace(-(nums1[i1 + 1] + nums2[i2]), i1 + 1, i2);
            if (i2 == end2 && end2 + 1 < n2) {
                pq.emplace(-(nums1[0] + nums2[end2 + 1]), 0, end2 + 1);
                end2++;
            }
        }
        res.erase(res.begin() + w, res.end());
        return res;
    }
};
```

3. ##### divide and conquer O(n)

- check problem 378 for details and reference

```c++
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
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (!nums1.size() || !nums2.size())
            return {};
        const int INF = 0x3f3f3f3f;
        int m = nums1.size(), n = nums2.size();
        // must check
        k = min(k, m * n);
        // start using biselect method
        function<int(int, int)> fetch = [&](int i, int j) {
            if (i < m && j < n)
                return nums1[i] + nums2[j];
            else
                return INF;
        };
        vector<int> indices(max(m, n));
        iota(indices.begin(), indices.end(), 0);
        auto [maxsum, _] = biselect(Matrix(fetch), indices, {k - 1, k - 1});
        // build results
        list<vector<int>> res;
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            while (j >= 0 && nums1[i] + nums2[j] > maxsum)
                j--;
            for (int k = 0; k <= j; k++)
                res.push_back({nums1[i], nums2[k]});
            i++;
        }

        k = max((int)res.size() - k, 0);
        auto it = res.begin();
        while (k > 0) {
            if ((*it)[0] + (*it)[1] == maxsum) {
                it = res.erase(it);
                k--;
            }
            else
                it++;
        }

        return {move_iterator(res.begin()), move_iterator(res.end())};
    }
};
```