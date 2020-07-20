Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits.

Note: You should try to optimize your time and space complexity.

Example 1:

Input:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
Output:
[9, 8, 6, 5, 3]
Example 2:

Input:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
Output:
[6, 7, 6, 0, 4]
Example 3:

Input:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
Output:
[9, 8, 9]

#### Solutions

1. ##### find maximun number independently in two vectors O(kn)

- reference: https://leetcode-cn.com/problems/create-maximum-number/solution/cshou-xian-qiu-jie-zi-wen-ti-zai-he-bing-zi-wen-ti/

```c++
class Solution {
public:
    // find the maximum number with length of len and reserved ordering
    vector<int> maxnums(vector<int> & nums, int len) {
        if (!len || len > nums.size()) return {};
        vector<int> s; s.push_back(nums[0]);
        int pop = 0;
        for (int i = 1; i < nums.size(); i++) {
            while (!s.empty() && s.back() < nums[i] && nums.size() - pop > len) {
                s.pop_back(); pop++;
            }
            s.push_back(nums[i]);
        }
        return s;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int len1 = nums1.size(), len2 = nums2.size();
        int minl = max(0, k - len2), maxl = min(len1, k);
        vector<int> res;
        for (int k1 = minl; k1 <= maxl; k1++) {
            vector<int> seq1 = maxnums(nums1, k1);
            vector<int> seq2 = maxnums(nums2, k - k1);
            vector<int> mseq(k);
            auto it1 = seq1.begin(), it2 = seq2.begin();
            auto w = mseq.begin();
            while (w != mseq.end())
                *w++ = lexicographical_compare(it1, seq1.end(), it2, seq2.end()) 
                        ? *it2++ : *it1++;
            if (!res.size() || lexicographical_compare(res.begin(), res.end(), mseq.begin(), mseq.end()))
                res = mseq;
        }
        return res;
    }
};
```