#### Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

```
Example 1:

Input: [3,4,5,1,2] 
Output: 1
Example 2:

Input: [4,5,6,7,0,1,2]
Output: 0
```

#### Solutions

1. ##### binary search worst(On)

- This problem is equivalent to find the reverse pivot.
- Though the first solution may seems more complicated, it's actually more generic in most binary search problems, the idea is the make the moving direction in each step correct with the normal binary search strategy.
    - If the binsearch algorithm doesn't works in some circumstances, fake the comparing element.

```c++
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size(), len = nums.size();

        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            // make sure the direction is right.
            // when nums[mid] > nums[len - 1], the range must be after mid. ie lo = mid + 1;
            // when nums[mid] == nums[len - 1], only  two possibilities:
            // [1, 2] or [2, 1], in both two cases, hi = mid works too.
            int midnum = nums[mid] > nums[len - 1] ? INT_MIN : INT_MAX;
            if (nums[lo] < midnum)
                hi = mid;
            else
                lo = mid + 1;
        }
        return nums[lo];
    }
};
```

Or
Caution: do not use [) mode.

```c++
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;

        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            // must compare with the last element.
            if (nums[mid] < nums[hi])
                hi = mid;
            // nums[mid] > nums[hi]
            else
                lo = mid + 1;
        }
        return nums[lo];
    }
};
```


OR

```c++
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int lo = 0, hi = nums.size();
        if (nums[lo] <= nums[hi - 1])
            return nums[0];
        else {
            while (lo < hi) {
                int mid = lo + ((hi - lo) / 2);
                if (nums[mid] > nums[lo])
                    lo = mid;
                else
                    hi = mid;
            }
            return nums[lo + 1];
        }
    }
};
```