### Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

```
Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

### Solutions

1. #### Find the rotate point, than do binary search. O(log(n) + log(n))

- Use binary search to find the rotate point. ie. The first number whose next number is smaller than itself.
- Determin which side of array contains the target.
- Do binary seach in that side.

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (!nums.size()) return -1;
        int lo = 0, hi = nums.size();
        if (nums[hi - 1] < nums[lo]) {
            hi = hi - 1;
            while (lo < hi) {
                int mid = lo + ((hi - lo) / 2);
                if (nums[mid] > nums[hi])
                    lo = mid + 1;
                else
                    hi = mid;
            }
            bool right = target <= nums[nums.size() - 1];
            hi = right ? nums.size() : lo;
            lo = right ? lo : 0;
        }
        
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (target < nums[mid]) hi = mid;
            else lo = mid + 1;
        }
        if (lo > 0 && lo <= nums.size() && nums[lo - 1] == target)
            return lo - 1;
        else
            return -1;
    }
};
```

2. #### Integrate rotate information into binary search O(log(n))

Be cautious about the selection of lo and hi. 

```c++
class Solution {
public:
    int search(vector<int> & nums, int target) {
        if (!nums.size()) return -1;
        int lo = 0, hi = nums.size(), mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (nums[mid] > nums[hi - 1]) {
                if (target >= nums[mid] ||  target <= nums[hi - 1])
                    lo = mid + 1;
                else
                    hi = mid;
                // if (target >= nums[lo] && target < nums[mid])
                //     hi = mid;
                // else
                //     lo = mid + 1;
            } else {
                if (target >= nums[mid] && target <= nums[hi - 1])
                    lo = mid + 1;
                else
                    hi = mid;
            }
        }
        return (lo && nums[lo - 1] == target) ? lo - 1 : -1;
    }
};
```
Or

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (!nums.size()) return -1;
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (nums[mid] < nums[hi]) {
                if (nums[mid] < target && nums[hi] >= target)
                    lo = mid + 1;
                else
                    hi = mid;
            } else {
                if (target < nums[lo] || target > nums[mid])
                    lo = mid + 1;
                else
                    hi = mid;
            }
        }
        return nums[lo] == target ? lo : -1;
    }
};
```

3. #### Maitain the moving direction when binary searching O(log(n))

- Borrowed from stephan.
- Matain the basic operation in binary search.
- Fake the value of `nums[mid]` when to ensure the moving direction are always right.

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2;

            double num = (nums[mid] < nums[0]) == (target < nums[0])
                       ? nums[mid]
                       : target < nums[0] ? -INFINITY : INFINITY;
            // upper bound
            if (target < num)
                hi = mid;
            else
                lo = mid + 1;
        }
        return (lo && nums[lo - 1] == target) ? lo - 1 : -1;
    }
};
```

or

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            int midval = (nums[mid] >= nums[lo] == target >= nums[lo]) 
                ? nums[mid] : (target >= nums[lo] ? INT_MAX : INT_MIN);
            // lower bound
            if (target > midval)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo != nums.size() && nums[lo] == target ? lo : -1;
    }
};
```