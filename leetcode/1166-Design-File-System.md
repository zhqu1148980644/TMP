You are asked to design a file system which provides two functions:

createPath(path, value): Creates a new path and associates a value to it if possible and returns True. Returns False if the path already exists or its parent path doesn't exist.
get(path): Returns the value associated with a path or returns -1 if the path doesn't exist.
The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.

Implement the two functions.

Please refer to the examples for clarifications.

 

Example 1:

Input: 
["FileSystem","createPath","get"]
[[],["/a",1],["/a"]]
Output: 
[null,true,1]
Explanation: 
FileSystem fileSystem = new FileSystem();

fileSystem.createPath("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:

Input: 
["FileSystem","createPath","createPath","get","createPath","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output: 
[null,true,true,2,false,-1]
Explanation: 
FileSystem fileSystem = new FileSystem();

fileSystem.createPath("/leet", 1); // return true
fileSystem.createPath("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.createPath("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.
 

Constraints:

The number of calls to the two functions is less than or equal to 10^4 in total.
2 <= path.length <= 100
1 <= value <= 10^9
NOTE: create method has been changed on August 29, 2019 to createPath. Please reset to default code definition to get new method signature.

#### Solutions

1. ##### hash map

```c++
struct Path {
    unordered_map<string, Path *> subpaths;
    int value = -1;
};
class FileSystem {
public:
    Path root;
    FileSystem() {

    }
    vector<string> split(string & path) {
        vector<string> paths;
        istringstream ss(path);
        string p;
        while (getline(ss, p, '/'))
            paths.push_back(p);
        return paths;
    }
    bool createPath(string path, int value) {
        vector<string> paths = split(path);
        Path * root = &(this->root);
        bool createnew = false;
        for (int i = 1; i < paths.size(); i++) {
            auto & p = paths[i];
            if (!root->subpaths.count(p)) {
                if (i != paths.size() - 1)
                    return false;
                createnew = true;
                root->subpaths.emplace(p, new Path);
            }
            root = root->subpaths[p];
        }
        if (createnew) {
            root->value = value;
            return true;
        }
        else return false;
    }
    
    int get(string path) {
        vector<string> paths = split(path);
        Path * root = &(this->root);
        for (int i = 1; i < paths.size(); i++) {
            auto & p = paths[i];
            if (!root->subpaths.count(p))
                return -1;
            root = root->subpaths[p];
        }
        return root->value;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
```

2. ##### trie