Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.

Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5

#### Solutions

1. ##### trie

```c++
class MapSum {
public:
    struct TrieNode {
        TrieNode * links[26] = {nullptr};
        int sumval = 0;
        TrieNode * insert(const string & key, int val, unordered_map<string, int> & m) {
            TrieNode * root = this;
            int inc = val - m[key]; m[key] = val;
            for (auto c : key) {
                if (!root->links[c - 'a'])
                    root->links[c - 'a'] = new TrieNode;
                root = root->links[c - 'a'];
                root->sumval += inc;
            }
            return root;
        }
        int sum(string & prefix) {
            TrieNode * root = this;
            for (auto c : prefix) {
                if (!root->links[c - 'a'])
                    return 0;
                root = root->links[c - 'a'];
            }
            return root->sumval;
        }
    };
    TrieNode root;
    unordered_map<string, int> m;

    /** Initialize your data structure here. */
    MapSum() {

    }
    
    void insert(string key, int val) {
        root.insert(key, val, m);
    }
    
    int sum(string prefix) {
        return root.sum(prefix);
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
```

- Another way is to directly store/update values in trie word nodes, and search for all words with the target prefix, summing up their values as the result.