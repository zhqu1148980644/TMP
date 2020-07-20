The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, which results in repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]
Note:
The given array size will in the range [2, 10000].
The given array's numbers won't have any order.

#### Solutions

1. ##### Pigeonhole principle

```c++
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        for (auto & n : nums)
            // for each element, put it at the right position
            while (nums[n - 1] != n)
                swap(nums[n - 1], n);

        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != i + 1)
                return {nums[i], i + 1};

        return {0, 0};
    }
};
```


2. ##### inplace hash map

- Only positions of the miss number and duplicate number will be positive.

```c++
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int dup = -1;
        for (auto n : nums) {
            n = abs(n);
            if (nums[n - 1] < 0)
                dup = n;
            nums[n - 1] = -nums[n - 1];
        }
        
        int miss = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0 && i + 1 != dup)
                miss = i + 1;
            else
                // try to restore the original array
                nums[i] = -nums[i];
        }

        return {dup, miss};
    }
};
```

3. ##### bit operations

```c++
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int full = 0, part = 0;
        // 1 ^ 2 ^ 3 ^ 4 ^ 5
        for (int i = 1; i <= nums.size(); i++)
            full ^= i;
        // 1 ^ 2 ^ 2 ^ 4 ^ 5
        for (auto n : nums)
            part ^= n;
        // full ^ part = 1 ^ 1 ^ 2 ^ 2 ^ 2 ^ 3...^ 5 ^ 5 = dup ^ miss
        // diff is the right most bit dup and miss differs
        int diff = (full ^ part) & -(full ^ part);
        // sepratate these two numbers n1 and n2
        int n1 = 0, n2 = 0;
        for (int i = 1; i <= nums.size(); i++)
            if (i & diff) n1 ^= i;
            else n2 ^= i;
        for (auto n : nums)
            if (n & diff) n1 ^= n;
            else n2 ^= n;
        // check which number is dup(only dup exists in the original array)
        for (auto n : nums)
            if (n == n1)
                return {n1, n2};

        return {n2, n1};
    }
};
```