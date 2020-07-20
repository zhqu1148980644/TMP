Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.

#### Solutions

- The maximum repeating time is `1 + (len(B) / len(A)) + 1`.
    - Suppose the correct upper bound is `1 + mid + 2`(Append a new A), since the first A within the middle part is the same as the new appended A, `mid + 2` would also contain `B`.

1. ##### straight forward O(n2)

```c++
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        int maxcnt = (B.size() / A.size()) + 2;
        int cnt = ceil((double)B.size() / A.size());
        string s;
        for (int i = 1; i <= cnt; i++)
            s += A;
        for (; cnt <= maxcnt; cnt++) {
            if(s.find(B) != string::npos)
                return cnt;
            s += A;
        }

        return -1;
    }
};
```


2. ##### kmp

```c++
class Solution {
public:
    vector<int> build_next(string & s) {
        vector<int> next(s.size());
        int i = next[0] = -1, j = 0;
        while (j < s.size() - 1) {
            if (i < 0 || s[j] == s[i]) {
                i++; j++;
                next[j] = s[i] == s[j] ? next[i] : i;
            }
            else
                i = next[i];
        }
        return next;
    }
    int strstr(string & s, string & p, vector<int> & next) {
        int i = 0, j = 0, pl = p.size(), sl = s.size();
        while (i < pl && j < sl) {
            if (i < 0 || s[j] == p[i]) {
                i++; j++;
            }
            else
                i = next[i];
        }
        return i == p.size() ? j - i : -1;
    }
    int repeatedStringMatch(string A, string B) {
        int maxcnt = (B.size() / A.size()) + 2;
        int cnt = ceil((double)B.size() / A.size());
        string s; s.reserve(maxcnt * s.size());
        for (int i = 1; i <= cnt; i++)
            s += A;
        vector<int> next = build_next(B);

        for (; cnt <= maxcnt; cnt++) {
            if(strstr(s, B, next) != -1)
                return cnt;
            s += A;
        }

        return -1;
    }
};
```


3. ##### rabin-karp