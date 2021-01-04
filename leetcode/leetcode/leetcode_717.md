---
title: 1 bit and 2 bit Characters
date: 2021-01-04
---
We have two special characters. The first character can be represented by one bit 0. The second character can be represented by two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given string will always end with a zero.

Example 1:
Input: 
bits = [1, 0, 0]
Output: True
Explanation: 
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.
Example 2:
Input: 
bits = [1, 1, 1, 0]
Output: False
Explanation: 
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.
Note:

1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.

#### Solutions

1. ##### straight forward

- checking each character from beginning to the end.

```cpp
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0;
        while (i < (int)bits.size() - 1)
            i += bits[i] ? 2 : 1;

        return i == bits.size() - 1;
    }
};
``

As `0` must be the end bit of a character, we can start checking characters after the first `0` to the left of the final `0`.

```cpp
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        if (!bits.size() || bits.back() > 0) return false;
        int res = 1;
        for (int i = bits.size() - 2; i >= 0; i--) {
            if (bits[i]) res ^= 1;
            else break;
        }
        return res;
    }
};
```