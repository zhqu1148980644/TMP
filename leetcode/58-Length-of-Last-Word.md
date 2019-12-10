### Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

### Note: 

A word is defined as a character sequence consists of non-space characters only.

```
Example:

Input: "Hello World"
Output: 5
```

### Solutions

1. #### Straight foward


```c++
class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0;
        int j = s.length() - 1;
        while(j >= 0 && s[j] == ' ') j--;
        while(j >= 0 && s[j] != ' ') {j--; count++;}
        return count;
    }
};
```

tricky version borrowed from other.

```c++
int lengthOfLastWord(char * s){
    int len = 0;
    while (*s) {
        if (*s++ != ' ')
            len += 1;
        else if (*s && *s != ' ')
            len = 0;
    }
    return len;
}
```