#### Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.

In a UNIX-style file system, a period . refers to the current directory. Furthermore, a double period .. moves the directory up a level. For more information, see: Absolute path vs relative path in Linux/Unix

Note that the returned canonical path must always begin with a slash /, and there must be only a single slash / between two directory names. The last directory name (if it exists) must not end with a trailing /. Also, the canonical path must be the shortest string representing the absolute path.

 

```
Example 1:

Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:

Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:

Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Example 4:

Input: "/a/./b/../../c/"
Output: "/c"

Example 5:

Input: "/a/../../b/../c//.//"
Output: "/c"

Example 6:

Input: "/a//b////c/d//././/.."
Output: "/a/b/c"
```

#### Solutions

- Note: substrings containing dot other than "../" "./" are valid folder names.

1. ##### stack

```c++
class Solution {
public:
    string simplifyPath(string path) {
        list<string> st;
        int i = 0;
        string prev;
        path.push_back('/');

        while (i < path.size()) {
            if (path[i] == '/') {
                if (prev.size()) {
                    if (prev == "..") {
                        if (st.size()) st.pop_back();
                    }
                    else if (prev != ".")
                        st.push_back(prev);
                }
                prev = "";
                i++;
            }
            else
                prev.push_back(path[i++]);
        }

        string res = "/";
        for (auto & p : st)
            res += p + "/";
        if (st.size())
            res.pop_back();
        return res;
    }
};
```


Python version

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        res = []
        for s in path.split('/'):
            if s == "..":
                if res:
                    res.pop()
            elif s and s != ".":
                res.append(s)

        return "/" + "/".join(res)
```