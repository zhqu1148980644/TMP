---
title: Decoded String at Index
date: 2021-01-04
---
An encoded string S is given.  To find and write the decoded string to a tape, the encoded string is read one character at a time and the following steps are taken:

If the character read is a letter, that letter is written onto the tape.
If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.
Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.

 

Example 1:

Input: S = "leet2code3", K = 10
Output: "o"
Explanation: 
The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
Example 2:

Input: S = "ha22", K = 5
Output: "h"
Explanation: 
The decoded string is "hahahaha".  The 5th letter is "h".
Example 3:

Input: S = "a2345678999999999999999", K = 1
Output: "a"
Explanation: 
The decoded string is "a" repeated 8301530446056247680 times.  The 1st letter is "a".
 

Constraints:

2 <= S.length <= 100
S will only contain lowercase letters and digits 2 through 9.
S starts with a letter.
1 <= K <= 10^9
It's guaranteed that K is less than or equal to the length of the decoded string.
The decoded string is guaranteed to have less than 2^63 letters.

#### Solutions

1. ##### recursion

```cpp
class Solution {
public:
    struct Word {
        size_t size = 0;
        string val;
        Word * subword = nullptr;
        Word() {}
        Word(Word & w) : size(w.size), subword(w.subword), val(move(w.val)) {}
        ~Word() noexcept {
            delete subword;
        }
        Word & operator+=(char c) {
            if (isalpha(c)) {
                val += c; size++;
            }
            else {
                subword = new Word(*this);
                size = (c - '0') * size;
            }
            return *this;
        }
        char index(int index) {
            if (index >= (size - val.size()))
                return val[index - (size - val.size())];
            else
                return subword->index(index % subword->size);
        }
    };
    string decodeAtIndex(string S, int K) {
        K--;
        Word w;
        for (auto c : S) {
            w += c;
            if (isdigit(c) && w.size > K)
                return string(1, w.index(K));
        }
        return string(1, w.index(K));
    }
};
```


2. ##### iteration


```cpp
class Solution {
public:
    string decodeAtIndex(string S, int K) {
        size_t size = 0, i = 0;
        while (i < S.size()) {
            if (isalpha(S[i]))
                size++;
            else {
                size *= S[i] - '0';
                if (size >= K)
                    break;
            }
            i++;
        }
        i = min(i, S.size() - 1);
        while (i >= 0) {
            // must add this step
            K %= size;
            // incase of asdas123123, S[i] would be a digit
            if (K == 0 && isalpha(S[i]))
                return S.substr(i, 1);
            if (isdigit(S[i]))
                size /= S[i] - '0';
            else
                size--;
            i--;
        }
        return "";
    }
};
```