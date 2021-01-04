---
title: Sequential Digits
date: 2021-01-04
---
#### An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

 

```
Example 1:

Input: low = 100, high = 300
Output: [123,234]
Example 2:

Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]
```
 

#### Constraints:

- 10 <= low <= high <= 10^9

##### Solutions

1. ##### generare all possible sequential digist

```cpp
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> coms, res;
        for (int i = 1; i < 9; i++) {
            int num = i, curd = i;
            while (curd < 9) {
                num = num * 10 + ++curd;
                if (num > 0) coms.push_back(num);
                else break;
            }
        }
        sort(coms.begin(), coms.end());
        for (auto c : coms)
            if (c >= low && c < high)
                res.push_back(c);

        return res;
    }
};
```

```python
class Solution:
    def sequentialDigits(self, low: int, high: int) -> List[int]:
        res = []
        for i in range(1, 9):
            num = curd = i
            while curd < 9:
                curd += 1
                num = num * 10 + curd
                res.append(num)
        return [num for num in sorted(res)
                if (num >= low) and (num < high)]
```