### Given an array of strings, group anagrams together.

```
Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
```

### Note:

All inputs will be in lowercase.
The order of your output does not matter.

### Solutions

The main idea is to map the items in the same group to the same key.

1. #### Convert to keys based on occurrence of each character

```python
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        from collections import defaultdict
        m = defaultdict(list)
        for s in strs:
            m[tuple(sorted(s))].append(s)
        return list(m.values())
```

Use rabix sorting.

```python
# may be slow in python due to dynamic typing.
class Solution:
    @staticmethod
    def countstr(s: str) -> str:
        c = [0] * 26
        for _s in s:
            c[ord(_s) - 97] += 1
        return "".join(str(c))

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        from collections import defaultdict
        m = defaultdict(list)
        for s in strs:
            m[self.countstr(s)].append(s)
        return list(m.values())
```


2. ##### sorting

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (auto & s : strs) {
            auto key = s;
            // or use count sort incase of the string is too long
            sort(key.begin(), key.end());
            m[key].push_back(move(s));
        }

        vector<vector<string>> res;
        for (auto & [k, vs] : m)
            res.push_back(move(vs));

        return res;
    }
};
```

3. #### prime number multiplication

- The idea is that the mulplication result of different prime numbers within a set are unique.
    - map each character a-z to different prime numbers. Then use multiplication as the group key.
- Use double to avoid interger overflow.

```c++
template <unsigned int N>
constexpr array<int, N> primenums() {
    array<int, N> primes;
    for (int i = 2, cur = 0; i <= INT_MAX && cur < N; i++) {
        bool isprime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isprime = false;
                break;
            }
        }
        if (isprime)
            primes[cur++] = i;
    }
    return primes;
}

auto primes = primenums<26>();

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<double, vector<string>> m;
        for (auto & s : strs) {
            double mulkey = 1;
            for (auto c : s)
                mulkey *= primes[c - 'a'];
            m[mulkey].push_back(s);
        }
        
        vector<vector<string>> res;
        for (auto & [k, vs] : m)
            res.push_back(move(vs));

        return res;
    }
};
```