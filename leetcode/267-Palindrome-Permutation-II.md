Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

Example 1:

Input: "aabb"
Output: ["abba", "baab"]
Example 2:

Input: "abc"
Output: []


#### Solutions


2. ##### backtrack O(n*(n!))

```c++
class Solution {
public:
    unordered_map<char, int> m;
    int neven = 0, odd = 0;
    vector<string> res;

    void dfs(string & s, int i) {
        if (i == s.size()) {
            string rs(s.rbegin(), s.rend());
            res.push_back(s + (odd ? string(1, odd) : "") + rs);
        }
        else {
            for (auto & [c, n] : m) {
                if (n <= 1) continue;
                s[i] = c; m[c] -= 2;
                dfs(s, i + 1);
                m[c] += 2;
            }
        }
    }
    vector<string> generatePalindromes(string s) {
        for (auto c : s)
            m[c]++;
        for (auto & [c, n] : m) {
            neven += n / 2;
            if (n % 2) {
                if (!odd) odd = c;
                else return {};
            }
        }
        if (odd && !neven) return {string(1, odd)};
        string half(neven, ' ');
        dfs(half, 0);
        return res;
    }
};
```