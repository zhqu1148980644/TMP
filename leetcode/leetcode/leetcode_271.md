---
title: Encode and Decode Strings
date: 2021-01-04
---
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

```cpp
string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
```

So Machine 1 does:

```cpp
string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
```
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

 

Note:

The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.


#### Solutions

1. ##### http encode

```cpp
class Codec {
public:
    string len2s(unsigned int n) {
        string res;
        char * c = (char*)&n;
        // store hex from least significant byte to most significant byte
        for(int i = 0; i < 4; i++)
            res.push_back(*(c + i));
        return res;
        // or. note the char may be negative. When bit or with a int, it should be casted to unsigned char.
        // string lens(4, ' ');
        // for (int i = 0; i < 4; i++)
        //     lens[i] = (n >> (i * 8) & 0xff);
        // return lens;
    }
    int s2len(string str) {
        int *p = (int *)str.data();
        return *p;
        // or. unsigned char is compulsory, since the signed char has sign bit(could be 1 or 0)
        // int len = 0;
        // for (int i = 0; i < 4; i++) {
        //     len = (len << 8) | (unsigned char)s[( 4 - i - 1)];
        // }
        // return len;
    }
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string es;
        for (auto & s : strs)
            es += len2s(s.size()) + s;
        return es;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> ds;
        int i = 0;
        while (i < s.size()) {
            int len = s2len(s.substr(i, 4)); i += 4;
            ds.push_back(s.substr(i, len));
            i += len;
        }
        return ds;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
```