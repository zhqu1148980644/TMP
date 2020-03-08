### Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

```
Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
```

### Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

### Solutions

All substring matching algorithms.

1. #### kmp

```c++
int * build_next(char * pattern, int len) {
    int  * next = (int *) malloc(sizeof(int) * len);
    int i = 0;
    int t = next[0] = -1;
    while (i < len - 1) {
        if ((t < 0) || pattern[i] == pattern[t]) {
            i++; t++;
            next[i] = (pattern[i] != pattern[t]) ? t : next[t];
        } else
            t = next[t];
    }
    return next;
}

int strStr(char * haystack, char * needle){
    if (!needle[0]) return 0;
    int m = strlen(haystack);
    int n = strlen(needle);
    if (n > m) return -1;
    int * next = build_next(needle, n);
    int i = 0, j = 0;
    while ((i < m) && (j < n)) {
        if ((j < 0) || (haystack[i] == needle[j])) {
            i++; j++;
        } else {
            j = next[j];
        }
    }
    free(next);
    if (j == n) return i - j;
    else return -1;
}
```

2. #### bm


3. #### karp-rabin
