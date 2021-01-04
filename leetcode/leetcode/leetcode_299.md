---
title: Bulls and Cows
date: 2021-01-04
---
You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. 

Please note that both secret number and friend's guess may contain duplicate digits.

Example 1:

Input: secret = "1807", guess = "7810"

Output: "1A3B"

Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
Example 2:

Input: secret = "1123", guess = "0111"

Output: "1A1B"

Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
Note: You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.

#### Solutions

1. ##### hashmap

```cpp
class Solution {
public:
    string getHint(string secret, string guess) {
        vector<int> ss(10), gs(10);
        int bull = 0, cow = 0;
        // since their length is the same, this step can be passed.
        auto [minl, maxl] = minmax({secret.size(), guess.size()});
        for (int i = 0; i < maxl; i++) {
            if (i < minl && secret[i] == guess[i])
                bull++;
            else {
                if (i < secret.size()) ss[secret[i] - '0']++;
                if (i < guess.size()) gs[guess[i] - '0']++;
            }
        }
        for (int i = 0; i < 10; i++)
            if (gs[i]) cow += min(ss[i], gs[i]);

        return to_string(bull) + "A" + to_string(cow) + "B";
    }
};
```

or just one pass.

```cpp
class Solution {
public:
    string getHint(string secret, string guess) {
        vector<int> ss(10);
        int bull = 0, cow = 0;
        for (int i = 0; i < secret.size(); i++) {
            if (secret[i] == guess[i])
                bull++;
            else {
                if (ss[secret[i] - '0'] < 0)
                    cow++;
                ss[secret[i] - '0']++;
                if (ss[guess[i] - '0'] > 0)
                    cow++;
                ss[guess[i] - '0']--;    
            }
        }

        return to_string(bull) + "A" + to_string(cow) + "B";
    }
};
```