---
title: Majority Element
date: 2021-01-04
---
#### Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

```
Example 1:

Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2
```

#### Solutions

1. ##### Brute force O(n) S(n)

- use hashmap to count each item's occurence and upate max_count when looping through the array.


2. ##### sorting  O(nlog(n)) S(1)/S(n)

- The problem assume the majority must exist.
- We wiil find the majority element in sorted_array[n / 2]

3. ##### devide and conquer O(nlog(n)) S(log(n))

- In each step, divide the majority problem into two independent problem.
- When majorities of two part are the same, then it's the global majority.
- Otherwise count these two number and return the one appeared more times.
- Base condition is when the size of the problem reduces to 1.

- Be careful about the lo and hi selection.
- It's similar to merge sort.

```cpp
int countRange(int * nums, int lo, int hi, int target) {
    int count = 0;
    while (lo <= hi)
        if (nums[lo++] == target)
            count++;
    return count;
}

int majority(int * nums, int lo, int hi) {
    if (lo == hi) return nums[lo];
    int mid = lo + (hi - lo) / 2;
    int left = majority(nums, lo, mid);
    int right = majority(nums, mid + 1, hi);
    if (left == right)
        return left;
    else {
        if (countRange(nums, lo, hi, left) > countRange(nums, lo, hi, right))
            return left;
        else
            return right;
    }
}

int majorityElement(int* nums, int numsSize){
    return majority(nums, 0, numsSize - 1);
}
```


4. ##### deduce and conquer or Boyer-Moore Voting Algorithm


- For a sequece `P`, `P[:2n]` is the `prefix` with majority `y` and `y` appeared `n` times in `P[:2n]`, then the majority of `P` is the majority of `P[2n:]`.
- Proof:
    - if the majority of `P` is `y`, since `y` and `non-y` deduces the same number of times, `y` will still be the majority of `P[2n:]`.
    - if the majority of `P` is `x != y`, then because `x` deduces less than `non-x(y and other nonx in P[:2n])`, `x` will still be the majority of `P[2n:]`.


```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int num = 1;
        int cur = nums[0];
        int len = nums.size();
        for (int i = 1; i < len; ++i) {
            if (num == 0) {
                cur = nums[i];
                num = 1;
            } else
            (nums[i] == cur) ? num++: num--;
        }
        // When the program did not say the majority element must exist, need to check if the proportion of this element is larger than 0.5.
        // for (int i = 0; i < len; ++i) {
        //     if (nums[i] == cur)
        //         max_num += 1;
        // }
        return cur;
    }
};

```
