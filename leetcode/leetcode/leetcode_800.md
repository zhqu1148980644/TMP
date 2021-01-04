---
title: Similar RGB Color
date: 2021-01-04
---
In the following, every capital letter represents some hexadecimal digit from 0 to f.

The red-green-blue color "#AABBCC" can be written as "#ABC" in shorthand.  For example, "#15c" is shorthand for the color "#1155cc".

Now, say the similarity between two colors "#ABCDEF" and "#UVWXYZ" is -(AB - UV)^2 - (CD - WX)^2 - (EF - YZ)^2.

Given the color "#ABCDEF", return a 7 character color that is most similar to #ABCDEF, and has a shorthand (that is, it can be represented as some "#XYZ"

Example 1:
Input: color = "#09f166"
Output: "#11ee66"
Explanation:  
The similarity is -(0x09 - 0x11)^2 -(0xf1 - 0xee)^2 - (0x66 - 0x66)^2 = -64 -9 -0 = -73.
This is the highest among any shorthand color.
Note:

color is a string of length 7.
color is a valid RGB color: for i > 0, color[i] is a hexadecimal digit from 0 to f
Any answer which has the same (highest) similarity as the best answer will be accepted.
All inputs and outputs should use lowercase letters, and the output is 7 characters.

##### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<int> m;
    inline int sim(const array<int, 3> & com, array<int, 3> & tgt) {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            sum -= pow(tgt[i] -m[com[i]], 2);
        return sum;
    }
    string similarRGB(string color) {
        for (int i = 0; i < 16; i++)
            m.push_back(i * 16 + i);
        
        array<int, 3> tgt = {0};
        for (int i = 0; i < 3; i++)
            sscanf(color.substr(1 + i * 2, 2).c_str(), "%x", &tgt[i]);

        int maxsim = INT_MIN, cursim;
        int d1 = 0, d2 = 0, d3 = 0;
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                for (int k = 0; k < 16; k++)
                    if ((cursim = sim({i, j, k}, tgt)) > maxsim) {
                        maxsim = cursim;
                        d1 = m[i]; d2 = m[j]; d3 = m[k];
                    }
        
        char s[] = "0123456";
        sprintf(s, "#%02x%02x%02x", d1, d2, d3);
        return s;
    }
};
```

2. ##### math O(1)

- borrowed from others
- Directly get the nearest hex number.
- Spacing between adjecent valid two-char hex numbers is `0x33 - 0x22 == 0x22 - 0x11 = 0x11 = 17`. Thus, the nearest y in `0xyy` for a given `n` is `(n / 17) + (n % 17 > 8 ? 1 : 0)`.


```cpp
class Solution {
public:
    string similarRGB(string color) {
        char hex[] = "0123456789abcdef";
        auto num = [&](char c) {
            int i = 0;
            while (hex[i++] != c)
                continue;
            return i - 1;
        };
        
        char res[] = "#1234567", * w = res + 1;
        for (int i = 0; i < 3; i++) {
            int n = num(color[1 + i * 2]) * 16 + num(color[2 + i * 2]);
            int neigh = (n / 17) + (n % 17 > 8 ? 1 : 0);
            sprintf(w, "%x%x", neigh, neigh);
            w += 2;
        }
        return res;
    }
};
```