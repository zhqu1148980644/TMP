---
title: Design Excel Sum Formula
date: 2021-01-04
---
Your task is to design the basic function of Excel and implement the function of sum formula. Specifically, you need to implement the following functions:

Excel(int H, char W): This is the constructor. The inputs represents the height and width of the Excel form. H is a positive integer, range from 1 to 26. It represents the height. W is a character range from 'A' to 'Z'. It represents that the width is the number of characters from 'A' to W. The Excel form content is represented by a height * width 2D integer array C, it should be initialized to zero. You should assume that the first row of C starts from 1, and the first column of C starts from 'A'.

#### void Set(int row, char column, int val): Change the value at C(row, column) to be val.

#### int Get(int row, char column): Return the value at C(row, column).

#### int Sum(int row, char column, List of Strings : numbers): This function calculate and set the value at C(row, column), where the value should be the sum of cells represented by numbers. This function return the sum result at C(row, column). This sum formula should exist until this cell is overlapped by another value or another sum formula.

numbers is a list of strings that each string represent a cell or a range of cells. If the string represent a single cell, then it has the following format : ColRow. For example, "F7" represents the cell at (7, F).

If the string represent a range of cells, then it has the following format : ColRow1:ColRow2. The range will always be a rectangle, and ColRow1 represent the position of the top-left cell, and ColRow2 represents the position of the bottom-right cell.

```
Example 1:

Excel(3,"C"); 
// construct a 3*3 2D array with all zero.
//   A B C
// 1 0 0 0
// 2 0 0 0
// 3 0 0 0

Set(1, "A", 2);
// set C(1,"A") to be 2.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 0

Sum(3, "C", ["A1", "A1:B2"]);
// set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the rectangle range whose top-left cell is C(1,"A") and bottom-right cell is C(2,"B"). Return 4. 
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 4

Set(2, "B", 2);
// set C(2,"B") to be 2. Note C(3, "C") should also be changed.
//   A B C
// 1 2 0 0
// 2 0 2 0
// 3 0 0 6
```

#### Note:

-    You could assume that there won't be any circular sum reference. For example, A1 = sum(B1) and B1 = sum(A1).
-    The test cases are using double-quotes to represent a character.
-    Please remember to RESET your class variables declared in class Excel, as static/class variables are persisted across multiple test cases. Please see here for more details.


#### Solutions

1. ##### straight forward

- Lazy mode. Record the dependency of each cell in sum operation.
- Use recursion to handle dependency of calculations.

```cpp
#define node(r, c) ((r) * 26 + ((c) - 'A'))
class Excel {
    vector<vector<int>> e;
    unordered_map<int, vector<string>> dep;

public:
    Excel(int H, char W) {
        e = vector<vector<int>>(H, vector<int>(W - 'A' + 1));
    }
    
    void set(int r, char c, int v) {
        if (dep.count(node(r, c)))
            dep.erase(node(r, c));
        e[r - 1][c - 'A'] = v;
    }
    
    int get(int r, char c) {
        if (dep.count(node(r, c)))
            return sum(r, c, dep[node(r, c)]);
        else
            return e[r - 1][c - 'A'];
    }
    
    int sum(int r, char c, vector<string> strs) {
        int res = 0;
        for (auto & range : strs) {
            int found = range.find(':');
            if (found == string::npos)
                res += this->get(stoi(range.substr(1)), range[0]);
            else {
                string start = range.substr(0, found);
                string end = range.substr(found + 1);
                int r1 = stoi(start.substr(1)), r2 = stoi(end.substr(1));
                int c1 = start[0], c2 = end[0]; 
                for (int i = r1; i <= r2; i++)
                    for (int j = c1; j <= c2; j++)
                        res += this->get(i, j);
            }
        }

        dep[node(r, c)] = strs;
        return res;
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(H, W);
 * obj->set(r,c,v);
 * int param_2 = obj->get(r,c);
 * int param_3 = obj->sum(r,c,strs);
 */
```


2. ##### topological sort

- Use topological sort to record the dependency.
- Update values in the dependency graph voluntarily when a node is updated by set operation.
- See the official answer.

```cpp

```