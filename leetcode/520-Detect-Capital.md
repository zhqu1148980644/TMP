#### Given a word, you need to judge whether the usage of capitals in it is right or not.

#### We define the usage of capitals in a word to be right when one of the following cases holds:

-    All letters in this word are capitals, like "USA".
-    All letters in this word are not capitals, like "leetcode".
-    Only the first letter in this word is capital, like "Google".

Otherwise, we define that this word doesn't use capitals in a right way.

 

```
Example 1:

Input: "USA"
Output: True

 

Example 2:

Input: "FlaG"
Output: False
```
 

#### Note: The input will be a non-empty word consisting of uppercase and lowercase latin letters.

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    bool detectCapitalUse(string word) {
        if (word.size() <= 1) return true;
        // leetcode or Google
        if (islower(word[0]) || (isupper(word[0]) && islower(word[1]))) {
            for (int i = 1; i < word.size(); i++)
                if (isupper(word[i]))
                    return false;
        }
        // USA
        else {
            for (int i = 1; i < word.size(); i++)
                if (islower(word[i]))
                    return false;
        }
        return true;
    }
};
```

or

```c++
class Solution {
public:
    bool detectCapitalUse(string word) {
        if (word.size() <= 1) return true;
        bool forbidupper = islower(word[0]) || (isupper(word[0]) && islower(word[1]));
        for (int i = 1; i < word.size(); i++)
            // isupper may not return 1 if isupper, for example: 256 ...
            if ((bool)isupper(word[i]) == forbidupper)
                return false;

        return true;
    }
};
```