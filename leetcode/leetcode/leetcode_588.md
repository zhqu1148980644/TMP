---
title: Design In Memory File Syste
date: 2021-01-04
---
Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that only contains this file's name. If it is a directory path, return the list of file and directory names in this directory. Your output (file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new directory according to the path. If the middle directories in the path don't exist either, you should create them as well. This function has void return type.

addContentToFile: Given a file path and file content in string format. If the file doesn't exist, you need to create that file containing given content. If the file already exists, you need to append given content to original content. This function has void return type.

readContentFromFile: Given a file path, return its content in string format.

 

Example:

Input: 
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]

Output:
[null,[],null,null,["a"],"hello"]

Explanation:

 

Note:

You can assume all file or directory paths are absolute paths which begin with / and do not end with / except that the path is just "/".
You can assume that all operations will be passed valid parameters and users will not attempt to retrieve file content or list a directory or file that does not exist.
You can assume that all directory names and file names only contain lower-case letters, and same names won't exist in the same directory.

#### Solutions

1. ##### path tree

```cpp
struct File {
    bool isfile;
    string content;
    map<string, File *> files;
    File(bool isfile = false) : isfile(isfile) {};
};

class FileSystem {
public:
    File root;

    FileSystem() {

    }
    vector<string> splitpath(const string & path, char d = '/') {
        vector<string> splits;
        string token;
        istringstream tokenstream(path);
        while (getline(tokenstream, token, d))
            splits.push_back(token);
        return splits;
    }
    File * locatedir(const string & path) {
        File * root = &(this->root);
        vector<string> ps = splitpath(path);
        for (auto & p : ps) {
            if (!root->files.count(p))
                root->files[p] = new File;
            root = root->files[p];
        }
        return root;
    }
    vector<string> ls(string path) {
        auto root = locatedir(path);
        // Notion, return file name if it's a file
        if (root->isfile) return {splitpath(path).back()};
        vector<string> res;
        for (auto & [k, v] : root->files)
            res.push_back(k);
        return res;
    }
    
    void mkdir(string path) {
        locatedir(path);
    }
    
    void addContentToFile(string filePath, string content) {
        auto root = locatedir(filePath);
        root->isfile = true;
        root->content += content;
    }
    
    string readContentFromFile(string filePath) {
        auto root = locatedir(filePath);
        return root->content;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
```