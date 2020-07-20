In English, we have a concept called root, which can be followed by some other words to form another longer word - let's call this word successor. For example, the root an, followed by other, which can form another word another.

Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor in the sentence with the root forming it. If a successor has many roots can form it, replace it with the root with the shortest length.

You need to output the sentence after the replacement.

 

Example 1:

Input: dict = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
 

Constraints:

The input will only have lower-case letters.
1 <= dict.length <= 1000
1 <= dict[i].length <= 100
1 <= sentence words number <= 1000
1 <= sentence words length <= 1000

##### Solutions


2. ##### trie

```c++
struct Trie {
    vector<Trie *> links{26};
    bool end = false;
    Trie * insert(const string & word) {
        Trie * root = this;
        for (auto c : word) {
            if (!root->links[c - 'a'])
                root->links[c - 'a'] = new Trie;
            root = root->links[c - 'a'];
        }
        root->end = true;
        return root;
    }
    int find(const string & word) {
        Trie * root = this;
        int num = 0;
        for (auto c : word) {
            if (!root->links[c - 'a'])
                return -1;
            root = root->links[c - 'a'];
            num++;
            if (root->end)
                return num;
        }
        return -1;
    }
};
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        Trie root;
        for (auto & w : dict)
            root.insert(w);
        
        int i = 0, w = 0;
        sentence.push_back(' ');
        for (int j = 0; j < sentence.size(); j++) {
            if (sentence[j] == ' ') {
                if (j - i > 0) {
                    int psize = root.find(sentence.substr(i, j - i));
                    int wlen = psize != -1 ? psize : j - i;
                    sentence.replace(w, wlen, sentence, i, wlen);
                    sentence[w + wlen] = ' '; w += wlen + 1;
                }
                i = j + 1;
            }
        }
        sentence.resize(w - 1);

        return sentence;
    }
};
```

or

```c++
struct Trie {
    vector<Trie *> links{26};
    string word;
    Trie * insert(const string & word) {
        Trie * root = this;
        for (auto c : word) {
            if (!root->links[c - 'a'])
                root->links[c - 'a'] = new Trie;
            root = root->links[c - 'a'];
        }
        root->word = word;
        return root;
    }
    //can not use const string & in passsing in word would be destruct when find functions ends
    string find(const string & word) {
        Trie * root = this;
        for (auto c : word) {
            if (!root->links[c - 'a'])
                break;
            root = root->links[c - 'a'];
            if (root->word.size())
                return root->word;
        }
        return word;
    }
};
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        Trie root;
        for (auto & w : dict)
            root.insert(w);
        
        int i = 0, w = 0;
        sentence.push_back(' ');
        for (int j = 0; j < sentence.size(); j++) {
            if (sentence[j] == ' ') {
                if (j - i > 0) {
                    const string & s =  root.find(sentence.substr(i, j - i));
                    sentence.replace(w, (int)s.size(), s); 
                    w += s.size();
                    sentence[w++] = ' ';
                }
                i = j + 1;
            }
        }
        sentence.resize(w - 1);

        return sentence;
    }
};
```