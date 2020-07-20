#### Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

Your algorithm should run in O(n) complexity.

```
Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
```

#### Solutions

1. ##### sort O(nlog(n)) S(1)

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (!nums.size()) return 0;
        sort(nums.begin(), nums.end());
        int count = 1, maxcount = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                count++;
            } else if (nums[i] != nums[i - 1]) {
                if (count > maxcount)
                    maxcount = count;
                count = 1;
            }
        }
        if (count > maxcount)
            maxcount = count;
        return maxcount;
    }
};
```

2. ##### hashmap O(n) S(n)

- Add every number into the hashset.
- Check every number that may be the first number of a consecutive sequence. ie: can not find `num - 1` in the hashset.

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (!nums.size()) return 0;
        unordered_set<int> m;
        for (auto & n : nums)
            m.insert(n);
        
        int c, maxc = 1;
        for (auto n : m) {
            if (!m.count(n - 1)) {
                c = 1;
                while (m.count(n + 1)) {
                    n++; c++;
                }
                maxc = max(maxc, c);
            }
        }
        return maxc;
    }
};
```

3. ##### interval merging

- Each unique number is inserted once. Only update the boundary of a contiguous region.

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> count;
        int cur, maxcount = 0, left , right;
        for (auto num : nums) {
            if (count.find(num) != count.end())
                continue;
            left = right = 0;
            if (count.find(num - 1) != count.end())
                left = count[num - 1];
            if (count.find(num + 1) != count.end())
                right = count[num + 1];

            cur = left + right + 1;
            // update self. if one of left and right is 0, then self is a boundary
            count[num] = cur;
            count[num - left] = cur;
            count[num + right] = cur;
            if (cur > maxcount)
                maxcount = cur;
        }
        return maxcount;
    }
};
```