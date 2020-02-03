Given a string S, consider all duplicated substrings: (contiguous) substrings of S that occur 2 or more times.  (The occurrences may overlap.)

Return any duplicated substring that has the longest possible length.  (If S does not have a duplicated substring, the answer is "".)

 

```
Example 1:

Input: "banana"
Output: "ana"

Example 2:

Input: "abcd"
Output: ""
```

 

#### Note:

-    2 <= S.length <= 10^5
-    S consists of lowercase English letters.


#### Solutions

1. ##### rabin-karp O(nlong(n))


- Use binary search to shrink the search range of the maximum length of repeated(more thant 2 times) subtring in log(n) times.
- Use rabin-karp algorithm to search repeated pattern in O(n) time.
- Follow up: Need to handle collisions.

```c++
#define num(x) ((x) - 'a')
class Solution {
public:
    int search(string & s, int n) {
        long m = pow(2, 32), R = 26, ML = 1, h = 0;
        for (int i = 1; i < n; i++)
            ML = (ML * R) % m;
        for (int i = 0; i < n; i++)
            h = (h * R + num(s[i])) % m;
        
        unordered_set<long> seen;
        seen.insert(h);

        for (int i = n; i < s.size(); i++) {
            h = (h - num(s[i - n]) * ML) % m;
            h = (h * R + num(s[i])) % m;
            if (h < 0) h += m;
            if (!seen.count(h))
                seen.insert(h);
            else
                return i - n + 1;
        }

        return -1;
    }

    string longestDupSubstring(string s) {
        if (s.size() <= 1) return s;
        // right must be s.size()
        int left = 1, right = s.size();
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (search(s, mid) != -1)
                left = mid + 1;
            else
                right = mid;
        }

        return left > 1 ? s.substr(search(s, left - 1), left - 1) : "";
    }
};
```

2. ##### suffix array


