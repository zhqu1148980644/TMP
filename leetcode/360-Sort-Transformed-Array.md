Given a sorted array of integers nums and integer values a, b and c. Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.

Expected time complexity: O(n)

Example 1:

Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
Output: [3,9,15,33]
Example 2:

Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
Output: [-23,-5,1,7]

#### Solutions

1. ##### find the mid point then merge two sorted arrays

```c++
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int len = nums.size();
        auto fn = [&](int i) {
            if (i < 0 || i >= len) return  a > 0 ? INT_MAX : INT_MIN;
            return a * nums[i] * nums[i] + b * nums[i] + c;
        };
        if (a == 0) {
            for (int i = 0; i < nums.size(); i++)
                nums[i] = fn(i);
            return b > 0 ? nums : vector<int>{nums.rbegin(), nums.rend()};
        }
        else {
            // must be ceil, mid is the first element gt/eq to midval
            int midval = ceil(-b / (2 * (double)a));
            int mid = 0; while (mid < len && nums[mid] < midval) mid++;

            vector<int> res(len);
            int i = mid - 1, j = mid, w = 0;
            auto comp = [a](auto val1, auto val2) {
                return a > 0 ? val1 < val2 : val1 > val2;
            };
            while (i >= 0 || j < len) {
                int val1 = fn(i), val2 = fn(j);
                if (comp(val2, val1)) {
                    res[w++] = val2; j++;
                }
                else {
                    res[w++] = val1; i--;
                }
            }

            return a > 0 ? res : vector<int>{res.rbegin(), res.rend()};
        }
    }
};
```

or just start merging from two ends.

```c++
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int len = nums.size();
        auto fn = [&](int i) {
            return a * nums[i] * nums[i] + b * nums[i] + c;
        };
        if (a == 0) {
            for (int i = 0; i < nums.size(); i++)
                nums[i] = fn(i);
            return b > 0 ? nums : vector<int>{nums.rbegin(), nums.rend()};
        }
        else {
            vector<int> res(len);
            auto comp = [a](auto val1, auto val2) {
                return a > 0 ? val1 > val2 : val1 < val2;
            };
            int i = 0, j = len - 1, w = 0;
            while (i <= j) {
                int val1 = fn(i), val2 = fn(j);
                if (comp(val2, val1)) {
                    res[w++] = val2; j--;
                }
                else {
                    res[w++] = val1; i++;
                }
            }

            return a < 0 ? res : vector<int>{res.rbegin(), res.rend()};
        }
    }
};
```