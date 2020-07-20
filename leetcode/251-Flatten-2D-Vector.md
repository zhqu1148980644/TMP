#### Design and implement an iterator to flatten a 2d vector. It should support the following operations: next and hasNext.

 

```
Example:

Vector2D iterator = new Vector2D([[1,2],[3],[4]]);

iterator.next(); // return 1
iterator.next(); // return 2
iterator.next(); // return 3
iterator.hasNext(); // return true
iterator.hasNext(); // return true
iterator.next(); // return 4
iterator.hasNext(); // return false
```

 

#### Notes:

-    Please remember to RESET your class variables declared in Vector2D, as static/class variables are persisted across multiple test cases. Please see here for more details.
-    You may assume that next() call will always be valid, that is, there will be at least a next element in the 2d vector when next() is called.

 

#### Follow up:

As an added challenge, try to code it using only iterators in C++ or iterators in Java.

#### Solutions

1. ##### iterator

```c++
class Vector2D {
public:
    vector<vector<int>::iterator> gen;
    int cur = 0;
    Vector2D(vector<vector<int>>& v) {
        for (auto & vv : v) {
            gen.push_back(vv.begin());
            gen.push_back(vv.end());
        }
    }
    
    int next() {
        while (gen[cur] == gen[cur + 1])
            cur += 2;
        int res = *gen[cur]++;
        return res;
    }
    
    bool hasNext() {
        while (cur < gen.size() && gen[cur] == gen[cur + 1])
            cur += 2;
        return cur != gen.size();
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(v);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```

or

```c++
class Vector2D {
public:
    vector<vector<int>> v;
    int i = 0, j = 0;
    Vector2D(vector<vector <int>>& v) {
        this->v = v;
    }
    
    int next() {
        while (i < v.size() && j >= v[i].size()) {
            i++; j = 0;
        }
        if (i >= v.size()) return -1;
        return v[i][j++];
    }
    
    bool hasNext() {
        while (i < v.size() && j >= v[i].size()) {
            i++; j = 0;
        }
        return i < v.size();
    }
};
```