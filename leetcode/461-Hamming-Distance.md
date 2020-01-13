##### The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

#### Note:
0 ≤ x, y < 231.

```
Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
```

#### Solutions

1. ##### xor

- Use xor to set bit positions where two numbers differ to 1.

```c++
class Solution {
public:
    int hammingDistance(int x, int y) {
        int num = x ^ y;
        int dis = 0;
        while (num) {
            if (num & 1)
                dis++;
            num >>= 1;
        }
        return dis;
    }
};
```

Or

```c++
class Solution {
public:
    int hammingDistance(int x, int y) {
        return bitset<32>(x ^ y).count();
    }
};
```

Or

```python
class Solution:
    def hammingDistance(self, x: int, y: int) -> int:
        return bin(x ^ y).count('1');
```