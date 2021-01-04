---
title: Couples Holding Hands
date: 2021-01-04
---
N couples sit in 2N seats arranged in a row and want to hold hands. We want to know the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.

The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).

The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.

Example 1:

Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
Example 2:

Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.
Note:

len(row) is even and in the range of [4, 60].
row is guaranteed to be a permutation of 0...len(row)-1.

#### Solutions


1. ##### greedy strategy O(n)

- How to prove the correctness.
- Iteratively make two adjacent numbers a couple.
- After numbers has been swapped, don't forget to update the index info in hash map.
    - Or simply search for the correct index at each step in linear time, thus the time complexity becomes O(n2).

```cpp
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        unordered_map<int, int> m;
        for (int i = 0; i < row.size(); i++)
            m[row[i]] = i;

        int res = 0, i = 0;
        while (i < row.size()) {
            int half = (row[i] % 2) ? row[i] - 1 : row[i] + 1;
            if (row[i + 1] != half) {
                // make back up
                int replaced = row[i + 1];
                swap(row[m[half]], row[i + 1]);
                // must do this to make sure m remains correct
                swap(m[half], m[replaced]);
                res++;
            }
            i += 2;
        }
        return res;
    }
};
```