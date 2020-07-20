#### Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

```
Example 1:

Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.

Example 2:

Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.

Example 3:

Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
```


#### Solutions

1. ##### set

- Mainting an ordered set with size 3.

```c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> s;
        for (auto & n : nums) {
            s.insert(n);
            if (s.size() > 3)
                s.erase(s.begin());
        }

        return s.size() == 3 ? *s.begin() : *s.rbegin();

    }
};
```

```c++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        vector<int> res;

        for (auto n : nums) {
            bool within = false;
            for (auto num : res)
                if (n == num) {
                    within = true;
                    break;
                }
            if (within) continue;
            for (auto & num : res)
                if (n > num)
                    swap(n, num);
            if (res.size() < 3)
                res.push_back(n);
        }

        return res.size() < 3 ? res.front() : res.back();
    }
};
```