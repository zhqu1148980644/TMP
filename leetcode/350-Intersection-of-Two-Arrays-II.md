#### Given two arrays, write a function to compute their intersection.

```
Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
```

#### Note:

-    Each element in the result should appear as many times as it shows in both arrays.
-    The result can be in any order.

#### Follow up:

-    What if the given array is already sorted? How would you optimize your algorithm?
-    What if nums1's size is small compared to nums2's size? Which algorithm is better?
-    What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

#### Solutions

1. ##### hash map o(n) S(n)

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size())
            return intersect(nums2, nums1);
        unordered_map<int, int> m;
        for (auto & num : nums1)
            m[num]++;
        int k = 0;
        for (int i = 0; i < nums2.size() && m.size(); i++) {
            if (m.count(nums2[i])) {
                nums1[k++] = nums2[i];
                if (--m[nums2[i]] <= 0)
                    m.erase(nums2[i]);
            }
        }

        return vector<int>(nums1.begin(), nums1.begin() + k);
    }
};
```

2. ##### binary search O(nlog(n))

- Follow up: when two arrays are already sorted, this method is preferred.

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int i = 0, j = 0, k = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j])
                i++;
            else if (nums1[i] > nums2[j])
                j++;
            else {
                nums1[k++] = nums1[i];
                i++; j++;
            }
        }
        return vector(nums1.begin(), nums1.begin() + k);
    }
};
```