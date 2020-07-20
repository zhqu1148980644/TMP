#### Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

```
Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
```

#### Solutions

1. ##### Straight forward

```c++
#define num(x) ((x) - '0')
#define cha(x) ((x == 1) ? '1' : '0')
#define max(x, y) ((x > y) ? x : y)

char * addBinary(char * a, char * b){
    int l1 = strlen(a); if (!l1) return b;
    int l2 = strlen(b); if (!l2) return a;
    int remain = 0;
    char * res = (char *) malloc(sizeof(char) * (max(l1, l2) + 2));
    char * st = res;
    // from the end to start
    while (l1 || l2) {
        if (l1) remain += num(a[--l1]);
        if (l2) remain += num(b[--l2]);
        *res++ = cha(remain % 2);
        remain /= 2;
    }
    if (remain) {
        *res++ = '1';
    }
    *res-- = '\0';
    a = st;
    // reverse the binary string
    while (st < res) {
        char tmp = *st;
        *st++ = *res;
        *res-- = tmp;
    }
    return a;
}

```

c++ version

```c++
#define num(x) ((x) - '0')
#define chr(x) ((x) == 1 ? '1' : '0')
class Solution {
public:
    string addBinary(string a, string b) {
        int l1 = a.size(); if (!l1) return b;
        int l2 = b.size(); if (!l2) return a;
        int remain = 0;
        string res;
        
        while (l1 || l2 || remain) {
            if (l1) remain += num(a[--l1]);
            if (l2) remain += num(b[--l2]);
            res.push_back(chr(remain % 2));
            remain /= 2;
        }
        return {res.rbegin(), res.rend()};
    }
};
```