---
title: Defanging an IP Address
date: 2021-01-04
---
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

 

Example 1:

Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
Example 2:

Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"
 

Constraints:

The given address is a valid IPv4 address.

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    string defangIPaddr(string address) {
        string res;
        for (auto c : address)
            if (c == '.')
                res += "[.]";
            else
                res += c;
        return res;
    }
};
```

or


```cpp
class Solution {
public:
    string defangIPaddr(string address) {
        string res;
        int st = 0;
        while (st < address.size()) {
            auto find = address.find('.', st);
            if (find == -1) find = address.size();
            res += address.substr(st, find - st) 
                + (find == address.size() ? "" : "[.]");
            st = find + 1;
        }

        return res;
    }
};
```

or

```cpp
class Solution {
public:
    string defangIPaddr(string address) {
        int a, b, c, d;
        sscanf(address.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
        char buffer[30];
        sprintf(buffer, "%d[.]%d[.]%d[.]%d\0", a, b, c, d);
        return buffer;
    }
};
```