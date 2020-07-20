#### Given a column title as appear in an Excel sheet, return its corresponding column number.

```
For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...

Example 1:

Input: "A"
Output: 1
Example 2:

Input: "AB"
Output: 28
Example 3:

Input: "ZY"
Output: 701
```


#### Solutions

1. ##### Straight forward

```c++
int titleToNumber(char * s){
    long num = 0;
    while (*s)
        num = num * 26 + *s++ - 'A' + 1;
    return num;
}
```

2. ##### base conversion

- `1234 = 1 * 10^3 + 2 * 10^2 + 3 * 10^1 + 4 * 10^0`

```c++
int titleToNumber(char * s) {
    int len = strlen(s);
    long num = 0;
    for (int i = len; i > 0; i--)
        num = num + (s[i - 1] - '@') * pow(26, len - i);
    return num;
}
```
