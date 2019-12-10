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

2. #### prime number multiplication

- The idea is that the mulplication result of different prime numbers in a set are unique.
    - map each character a-z to different prime numbers. Then use multiplication as the group key.