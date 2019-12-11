#### Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

#### Note: 
For the purpose of this problem, we define empty string as valid palindrome.

```
Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false
```

#### Solutions

1. ##### Straight forward

- Skip the undesirable characters when checking pakubdrome in the normal way(Two pointers).

```c++
#define lower(x) (((x) <= 90) ? (x + 32) : (x)) 
#define ischar(x) (x >='A' && x<='Z') || (x>='a' && x<='z') ||( x>='0' && x<='9')
#define notchar(x) (!ischar(x))
#define equal(x, y) (lower(x) == lower(y))
#define convert(x) (ischar(x) ? (x) : 0)

class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.length() - 1;
        char left = '\0';
        char right = '\0';
        while (i < j) {
            if (!convert(s[i])) {
                i++;
            } else if (!convert(s[j])) {
                j--;
            } else {
                // cout << s[i] << " " << s[j] << endl;
                if (!equal(s[i], s[j]))
                    return false;
                else
                {i++;j--;}
            }
        }
        return true;
    }
};
```
