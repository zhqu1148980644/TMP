You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

Example:

Input: 4
Output: false 
Explanation: If there are 4 stones in the heap, then you will never win the game;
             No matter 1, 2, or 3 stones you remove, the last stone will always be 
             removed by your friend.



#### Solutions

1. ##### dynamic programming O(n)

- stackoverflow or time limit exceed

```c++
class Solution {
public:
    unordered_map<int, bool> m;
    bool canwin(int i) {
        if (i < 3) return true;
        if (m.count(i)) return m[i];
        return m[i] = !canwin(i - 1) || !canwin(i - 2) || !canwin(i - 3);
    }
    bool canWinNim(int n) {
        return canwin(n);
    }
};
```

```c++
class Solution {
public:

    bool canWinNim(int n) {
        if (n < 4) return true;
        bool ppprev, pprev, prev;
        ppprev = pprev = prev = true;
        for (int i = 4; i <= n; i++) {
            bool cur = !prev || !pprev || !ppprev;
            ppprev = pprev; pprev = prev; prev = cur;
        }
        return prev;
    }
};
```

2. ##### math O(1)

- When the first player has `4n` stones, the second player can always matain this state untill the first player gets `4` stones, then the second player could win.

```c++
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};
```