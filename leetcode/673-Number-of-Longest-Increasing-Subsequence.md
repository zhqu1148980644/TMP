#### Given an unsorted array of integers, find the number of longest increasing subsequence.

```
Example 1:

Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:

Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
```

#### Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int. 


#### Solutions

1. ##### dynamic programming O(n2)

- Add another `dp table` to record the `number` of longest increasing subsequences ending with each position based on the solution in `problem 300`.

```c++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int> maxlen(nums.size(), 1);
        vector<int> count(nums.size(), 1);
        int final_maxlen = 1;

        for (int j = 0; j < nums.size(); j++) {
            int curlen = 1;
            int curcount = 1;
            for (int i = 0; i < j; i++) {
                if (nums[i] < nums[j]) {
                    if (maxlen[i] + 1 > curlen) {
                        curlen = maxlen[i] + 1;
                        curcount = count[i];
                    }
                    else if (maxlen[i] + 1 == curlen)
                        curcount += count[i];
                }
            }
            maxlen[j] = curlen;
            count[j] = curcount;
            final_maxlen = max(final_maxlen, curlen);
        }
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
            if (maxlen[i] == final_maxlen)
                res += count[i];
        return res;
    }
};
```

2. ##### interval tree O(nlog(n))

3. ##### binary search O(n(log(n)))

- https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/solution/yi-bu-yi-bu-tui-dao-chu-zui-you-jie-fa-2-zui-chang/
- Based on the binary search method described in `problem 300`
- Internally, this method will record the whole process while updating the lcs sequence using binary search, further more, it will also assign a count value to each number, representing the count of lcs ending with `nums >= cur`.
    - To improve the counting complexity from O(n) to O(log(n)), use both binary search and prefix-sum.

```c++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (!nums.size()) return 0;
        vector<vector<int>> lcs, cnts;

        int pos, cnt;
        for (auto n : nums) {
            // this part is the same as method in problem 300
            if (lcs.empty() || n > lcs.back().back()) {
                pos = lcs.size();
                lcs.push_back({}); cnts.push_back({});
            }
            else
                pos = lower_bound(lcs.begin(), lcs.end(), n, [](auto & v, auto target) {
                    return v.back() < target;
                }) - lcs.begin();
            lcs[pos].push_back(n);
            // here comes the different, count the number of lcs end with `num >= cur`
            int prevcnt = 0;
            if (pos > 0) {
                auto & prev = lcs[pos - 1];
                prevcnt = cnts[pos - 1]. back();
                int gtindex = upper_bound(prev.begin(), prev.end(), n, greater<int>()) - prev.begin();
                prevcnt -= gtindex > 0 ? cnts[pos - 1][gtindex - 1] : 0;
            }
            else
                prevcnt = 1;
            cnt = prevcnt + (cnts[pos].size() ? cnts[pos].back() : 0); 
            cnts[pos].push_back(cnt);
        }

        return cnts.back().back();
    }
};
```


or tuple maxlen and cnt into a pair.


```c++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.size() <= 0) return 0;

        vector<vector<pair<int, int>>> lcs;
        auto vit = lcs.begin();
        for (auto n : nums) {
            if (lcs.empty() || lcs.back().back().first < n)
                vit = lcs.insert(lcs.end(), {{}});
            else
                vit = lower_bound(lcs.begin(), lcs.end(), n, [](auto & v, int target) {
                    return v.back().first < target;
                });
            int prevcnt = 1;
            if (vit != lcs.begin()) {
                auto & pre = *prev(vit);
                prevcnt = pre.back().second;
                if (pre.front().first >= n)
                    prevcnt -= prev(upper_bound(pre.begin(), pre.end(), 
                        make_pair(n, 0), greater<pair<int, int>>()))->second;
            }
            int cnt = prevcnt +  (vit->size() ? vit->back().second : 0);
            vit->emplace_back(n, cnt);
        }

        return lcs.back().back().second;
    }
};
```

4. ##### binary index tree O(nlog(n))

- reference: https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/solution/yi-bu-yi-bu-tui-dao-chu-zui-you-jie-fa-2-zui-chang/

```c++
// the same as normal FenwickTree, except that the node type is variable
template <typename T>
struct FenwickTree {
    vector<T> sums;
    FenwickTree(int size) : sums(size + 1) {}
    void update(int n, T value) {
        while (n < sums.size()) {
            sums[n] += value;
            n += lowbit(n);
        }
    }
    T query(int n) {
        T sum;
        while (n) {
            sum += sums[n];
            n -= lowbit(n);
        }
        return sum;
    }
    static inline int lowbit(int n) {
        return n & -n;
    }
};

class Solution {
public:
    // maxlen represents the length of the maximum LIS ended in the current number
    // cnt represents the counts of the LIS
    struct Node {
        int maxlen, cnt;
        Node(int len = 0, int cnt = 0) : maxlen(len), cnt(cnt) {}
        Node & operator+=(Node & b) {
            // merge two nonoverlapping node
            if (b.maxlen == maxlen)
                cnt += b.cnt;
            else if (b.maxlen > maxlen) {
                maxlen = b.maxlen;
                cnt = b.cnt;
            }
            return *this;
        }
    };
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.size() <= 1)
            return nums.size();

        vector<int> sorted(nums);
        sort(sorted.begin(), sorted.end());
        FenwickTree<Node> ft(nums.size());
        // why insert each element based on their ordering index?
        // ft.query works if we use the default index(Suppose all former node are correctly calculated).
        // However, the maxlen/count in the current node is impossible to be determined, only if the query results are based on nodes with values smaller than self, the maxlen can be easily calculated by `premaxlen + 1`.
        Node res;
        for (auto num : nums) {
            int rank = lower_bound(sorted.begin(), sorted.end(), num) - sorted.begin();
            Node prev = ft.query(rank);
            Node now(prev.maxlen + 1, prev.cnt ? prev.cnt : 1);
            res += now;
            ft.update(rank + 1, now);
        }

        return res.cnt;
    }
};
```