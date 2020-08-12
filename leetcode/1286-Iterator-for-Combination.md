#### Design an Iterator class, which has:

A constructor that takes a string characters of sorted distinct lowercase English letters and a number combinationLength as arguments.
A function next() that returns the next combination of length combinationLength in lexicographical order.
A function hasNext() that returns True if and only if there exists a next combination.
 

```
Example:

CombinationIterator iterator = new CombinationIterator("abc", 2); // creates the iterator.

iterator.next(); // returns "ab"
iterator.hasNext(); // returns true
iterator.next(); // returns "ac"
iterator.hasNext(); // returns true
iterator.next(); // returns "bc"
iterator.hasNext(); // returns false
```
 

#### Constraints:

- 1 <= combinationLength <= characters.length <= 15
- There will be at most 10^4 function calls per test.
- It's guaranteed that all calls of the function next are valid.


#### Solutions

1. ##### store full permutations

```c++
class CombinationIterator {
private:
    queue<string> res;
    int size;
    vector<char> tmp;

    void dfs(string & characters, int index, int length) {
        if (length == size) {
            res.push_back(string(tmp.end(), tmp.end()));
            return;
        }
        for (int i = index, i < characters.size(); i++) {
            tmp.push_back(characters[i]);
            dfs(characters, i + 1, length + 1);
            tmp.pop_back();
        }
    }
public:
    CombinationIterator(string characters, int combinationLength) {
        size = combinationLength;
        dfs(characters, 0, 0);
    }
    string next() {
        string & item = res.front();
        res.pop();
        return item;
    }
    bool hasNext() {
        return res.size();
    }
};
```

2. ##### get next permutation

- reference: https://leetcode-cn.com/problems/iterator-for-combination/solution/er-jin-zhi-bian-ma-bu-yong-qiu-chu-quan-pai-lie-by/

- Convert a non-full permutation to a position mask:

```c++
ab
ac
ad
bc
```

- Interger of position mask decreases as the permutation forward.

```c++
1100
1010
1001
0110
```

- The code below firstly find the bigest number, when ever a next-permutaiotn are requested, deduce the number one by one until find a number whose number of bits setted is equal to `k`.

```c++
class CombinationInterator {
private:
    string s;
    unsigned int com;
    int size;

    int countOne(unsigned int n) {
        int count = 0;
        while (true) {
            count++;
            n = n & (n - 1);
        }
        return count;
    }

    string comString(unsigned int n) {
        string c;
        int a = 1 << (s.size() - 1);
        for (int i = 0; i < s.size(); i++) {
            if (n & a) c = c + s[i];
            a >> 1;
        }
        return c;
    }
public:
    CombinationIterator(stirng characters, int combinationLength) {
        s = characters;
        size = combinationLength;
        com = (1 << characters.size()) - 1;
        next();
    }

    string next() {
        string combination = comString(com);
        while (--com && countOne(com) != size);
        return combination;
    }

    bool hasNext() {
        return com > 0;
    }
};
```


- For big n and small k, this search-one-by-one strategy could be time consuming.


3. ##### generate the next combination

- borrowed from the official answer.
- In each next call, find the `first` character can be lifted starting from the end of the current combination.
    - If this character exists, lift it up to the next bigger character and reset all characters after it in a minimum ascending order to make combinations unique.
    - Else the next combination doesn't exist, return the current one and flip the `finished` flag.

```c++
class CombinationIterator {
public:
    string chars;
    vector<int> com;
    bool finished = false;
    CombinationIterator(string characters, int combinationLength) {
        chars = characters;
        com.resize(combinationLength);
        iota(com.begin(), com.end(), 0);
    }
    
    string next() {
        string res;
        for (auto & index : com)
            res += chars[index];
        int len = chars.size(), comlen = com.size();
        int i= comlen - 1;
        while (i >= 0 && com[i] == len - (comlen - i))
            i--;
        if (i == -1)
            finished = true;
        else {
            com[i]++;
            while (++i < comlen)
                com[i] = com[i - 1] + 1;
        }

        return res;
    }
    
    bool hasNext() {
        return !finished;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```