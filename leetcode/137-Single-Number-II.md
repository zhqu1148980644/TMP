Given a non-empty array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

#### Note:

- Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

```
Example 1:

Input: [2,2,3,2]
Output: 3

Example 2:

Input: [0,1,0,1,0,1,99]
Output: 99
```


#### Solutions


1. ##### math

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        long sum3 = accumulate(nums.begin(), nums.end(), 0l);
        set<long> s(nums.begin(), nums.end());
        long sum = accumulate(s.begin(), s.end(), 0l);

        return (3 * sum - sum3) / 2; 
    }
};
```

2. ##### counter

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> c;
        for (auto n : nums)
            c[n]++;
        
        for (auto && [k, v] : c)
            if (v == 1)
                return k;
        return 0;
    }
};
```

3. ##### bit operation

- `seen_once` records bits occurred onces.
- `seen_twice` records bits occurred twice.
- For example: `2 2 2`, seen_once = 0, seen_twice = 0
    - 2, seen_once will becomes to `0b10`, as `~seen_once` masks bits seen once, `seen_twice` will not change.
    - 2, seen_once will unset bits occurred `once` and becomes to `0b00`, `seen_twice` can sucessfully record this bit and becomes to `0b10`
    - 2, As the `2nd` bit is already recorded in `seen_twice`, `seen_once` will not record this bit and stay the same and the `2nd` bit occurred three times will be erased in `seen_twice`.
        - Numbers occurred three times can be recorded by using another variable, however this variable will never be used.
    - Thus only numbers occured 1 times will be matined in `seen_once`.

```
Occurence:     0     1     2    3    4 .....
once           0     1     0    0    1 
twice          0     0     1    0    0


```


```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int seen_once = 0, seen_twice = 0;

        for (auto n : nums) {
            seen_once = ~seen_twice & (seen_once ^ n);
            seen_twice = ~seen_once & (seen_twice ^ n);
        }

        return seen_once;
    }
};
```


4. ##### bit operation

- reference: https://leetcode-cn.com/problems/single-number-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--31/
- By using a single number the occurence of a bit has only two state: occurred `0` times or `1` times. This contriction can be breaked by using multiple numbers.
    - For example: 2 numbers can count each bit at most 3 times.
    - the lowest bit occurred 0 times: x2 = ..00  x1 = ..00
    -                         1 times: x2 = ..00  x1 = ..01
    -                         2 times: x2 = ..01  x1 = ..00
    -                         3 times: x2 = ..01  x1 = ..01
    - The combination of the lowest bit in two numbers represents the occurence number. `00 -> 01 -> 10 -> 11` `0 -> 1 -> 2 -> 3`
- `X(n), X(n - 1), X(n - 2) ... X(1)` is a set of numbers, `X(i)` means this number represent the `i'th` bit of the occurence number.
    - To simulate binary carry:
    - `X(n) ^= X(n - 1) & X(x - 2) & ... X(1) & n` representing `1111 = 0111 + 1`
    - Above updating rule should be applied to every number starting from the number representing the heightes bit.

- For array with every elements appears `k` times except for one appears exactly `j` times, `m = minimum number of bits to represent k = ceil(log(k))`.
- Another problem is that we want all bits are unset to zero when each bits occured `k` times, then only the number occured `j` times will be stored. 
    - `00 -> 01 -> 10 -> 11 -> 00`. As we can see, when `k` equals to `3`, bits representaion of the occurence(3) is `11` instead of `00`.
    - `mask` is used for resetting all `x` to `0` when `xmx(m-1)...x1` reaches `k`.
        - `yi = bin(k)[::-1][i - 1] == 1 ? xi : ~xi`
        - When `xmx(m-1)...x1` equals to `k`,  `y1 & y2 & ... ym` equals to `1`, thus ` ~(y1 & y2 ... ym) == ~1 == 0` and `x1, x2 ... xm` are reset to 0.
        - When `xmx(m-1)...x1` is lower than `k`, `y1 & y2 ... ym` equals to `0`, thus `~(y1 & y2 ... ym) == ~0 == 1` and `x1, x2 ... xm` are not changed.

```c++
int xm = x(m-1) = .... x1 = 0;
for (auto n : nums) {
    // update bit
    // ie: 000 -> 001 -> 010 -> 011 -> 100 -> 101 -> 111
    xm ^= (x(m-1) & x(m-2) & ... x1 & n);
    x(m-1) ^= (x(m-2) & .... x1 & n);
    ...
    x1 ^= n;

    mask = ~(y1 & y2 ... ym) with yi = xi if bin(k)[::-1][i - 1] == 1 else yi = ~xi

    // reset to zero if reaches k
    xm &= mask;
    x(m-1) &= mask;
    ...
    x1 &= mask;
}

// return x1 if j == 1, else return x1 or x2 or ... xm according to the value of j.
// if j == 2, bin(2) = 10, return x2;
// if j == 3, bin(3) = 11, return x1 or x2;
// if j == 4, bin(4) = 100, return x3;
// ....
return x1;
```


- In this problem, `k = 3 = 11`, `mask = ~(x2 & x1)`.

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int x2 = 0, x1 = 0;
        for (auto & n : nums) {
            x2 ^= (x1 & n);
            x1 ^= n;
            int mask = ~(x2 & x1);
            x2 &= mask;
            x1 &= mask;
        }

        return x1;
    }
};
```