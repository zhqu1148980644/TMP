---
title: Divide Array in Sets of K Consecutive Numbers
date: 2021-01-04
---
#### Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into sets of k consecutive numbers
Return True if its possible otherwise return False.

 

```
Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
Example 3:

Input: nums = [3,3,2,2,1,1], k = 3
Output: true
Example 4:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.
```
 

#### Constraints:

- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 1 <= k <= nums.length


#### Solutions


1. ##### hashmap

- Put each item in an ordered hashmap, at each iteration:
    - staring from the minimum number, trying to find k consecutive numbers and deduce the corresponding count, return false when the search fails.

```cpp
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int K) {
        map<int, int> m;
        for (auto n : nums) m[n]++;
        auto it = m.begin();
        while (it != m.end()) {
            int n = it->first;
            auto nit = next(it);
            for (int k = 1; k < K; k++) {
                if (nit != m.end() && nit->first == n + 1) {
                    if (--nit->second == 0)
                        nit = m.erase(nit);
                    else
                        nit++;
                    n++;
                }
                else return false;
            }
            if (--it->second == 0)
                it++;
        }

        return true;
    }
};
```


2. ##### sort

```cpp
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k) return false;
        unordered_map<int, int> m;
        for (auto n : nums) m[n]++;
        if (m.size() < k) return false;

        vector<int> v(m.size());
        int w = 0;
        for (auto [n, cnt] : m)
            v[w++] = n;
        sort(v.begin(), v.end());
        
        int i = 0;
        while (i < v.size()) {
            if (!m[v[i]] && ++i) continue;
            int n = v[i], j = i + 1;
            for (int curk = 1; curk < k; curk++) {
                if (j < v.size() && m[v[j]] && v[j] == n + 1) {
                    n++; m[v[j++]]--;
                }
                else return false;
            }
            if (--m[v[i]] == 0) i++;
        }

        return true;
    }
};
```

3. ##### sort

- reference: https://leetcode-cn.com/problems/hand-of-straights/solution/mei-ri-suan-fa-day-103-lao-ti-xin-zuo-ji-hu-bu-hui/

```cpp

class Solution {
public:
    bool valid(vector<int> & counts, int W) {
        int len = counts.size(), need = 0;
        vector<int> deltas(len);

        for (int i = 0; i < len; i++) {
            need += deltas[i];
            if (counts[i] > need) {
                int delta = counts[i] - need;
                need = counts[i];
                // The end of new appended heads of consecutive sequences are recorded.
                if (i + W < len) deltas[i + W] -= delta;
            }
            else if (counts[i] < need)
                return false;
        }
        return true;
    }
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k) return false;
        sort(nums.begin(), nums.end());
        vector<int> counts;
        int i = 0, len = nums.size();
        while (i < len) {
            int j = i + 1;
            while (j < len && nums[j] == nums[i]) j++;
            counts.push_back(j - i);
            if (j < len && nums[j] != nums[j - 1] + 1)
                // push_back 0 as the mark of ending of consecutive sequence
                // used in valid function, when traversed at this 0, the `need` should be zero too.
                counts.push_back(0);
            i = j;
        }
        counts.push_back(0);

        return valid(counts, k);
    }
};
```