Let's define a function countUniqueChars(s) that returns the number of unique characters on s, for example if s = "LEETCODE" then "L", "T","C","O","D" are the unique characters since they appear only once in s, therefore countUniqueChars(s) = 5.

On this problem given a string s we need to return the sum of countUniqueChars(t) where t is a substring of s. Notice that some substrings can be repeated so on this case you have to count the repeated ones too.

Since the answer can be very large, return the answer modulo 10 ^ 9 + 7.

 

Example 1:

Input: s = "ABC"
Output: 10
Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
Evey substring is composed with only unique letters.
Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
Example 2:

Input: s = "ABA"
Output: 8
Explanation: The same as example 1, except countUniqueChars("ABA") = 1.
Example 3:

Input: s = "LEETCODE"
Output: 92
 

Constraints:

0 <= s.length <= 10^4
s contain upper-case English letters only.

#### Solution

1. ##### count for each character in`A-Z` O(26n)

- Count the contribution to the total count for each character in `A-Z`. 
- Suppose the string are `*****A******` and the current checking character is `A`, `*` represents any character except for `A`, substrings will count A as unique character are:
    - `A`, `*A` and `**A` and ... `*******A`, equals to `r - l`, `l` is the previous appearance index of `A`, in this case `r == -1`, `r` represents the index of the `A`.
    - `A*` and `*A*` and `**A*` and `***A*` .... `******A*`, equal to `r - l`
    - `A**` and `*A**` .... ``******A**`, equal to `r - l`
    - ....
    - `A********` and `*A*********` ... `********A******`, equal to `r - l`
    - This counting applies to all ranges without duplicate 'A'.
    - For each character, counting cost `O(n)` time.

```c++
class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        long long res = 0;
        for (char c = 'A'; c <= 'Z'; c++) {
            int l = -1, r = -1;
            for (int cur = 0; cur < n; cur++) {
                if (s[cur] == c)
                    l = r, r = cur;
                res += r - l;
            }
        }
        return res % 1000000007;
    }
};

```

or use hash map instead of linear scanning. O(2n)

```c++
class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        unordered_map<char, vector<int>> pos;
        for (int i = 0; i < n; i++)
            pos[s[i]].push_back(i);

        long long res = 0;
        for (auto & [c, indexes] : pos) {
            for (int i = 0; i < indexes.size(); i++) {
                int l = i ? indexes[i - 1] : -1;
                int mid = indexes[i];
                int r =  i < indexes.size() - 1 ? indexes[i + 1] : n;
                // has included self. ie s[mid:mid]
                res += (mid - l) * (r - mid);
            }
        }
        return res % 1000000007;
    }
};
```