Given a picture consisting of black and white pixels, and a positive integer N, find the number of black pixels located at some specific row R and column C that align with all the following rules:

Row R and column C both contain exactly N black pixels.
For all rows that have a black pixel at column C, they should be exactly the same as row R
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

Example:
Input:                                            
[['W', 'B', 'W', 'B', 'B', 'W'],    
 ['W', 'B', 'W', 'B', 'B', 'W'],    
 ['W', 'B', 'W', 'B', 'B', 'W'],    
 ['W', 'W', 'B', 'W', 'B', 'W']] 

N = 3
Output: 6
Explanation: All the bold 'B' are the black pixels we need (all 'B's at column 1 and 3).
        0    1    2    3    4    5         column index                                            
0    [['W', 'B', 'W', 'B', 'B', 'W'],    
1     ['W', 'B', 'W', 'B', 'B', 'W'],    
2     ['W', 'B', 'W', 'B', 'B', 'W'],    
3     ['W', 'W', 'B', 'W', 'B', 'W']]    
row index

Take 'B' at row R = 0 and column C = 1 as an example:
Rule 1, row R = 0 and column C = 1 both have exactly N = 3 black pixels. 
Rule 2, the rows have black pixel at column C = 1 are row 0, row 1 and row 2. They are exactly the same as row R = 0.

Note:
The range of width and height of the input 2D array is [1,200].

#### Solutions

1. ##### straight forward worst case O(n4)

- The time complexity could be improvement by hashing each row into a unique key.

```c++
class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int N) {
        int nrow = picture.size(); if (!nrow) return 0;
        int ncol = picture[0].size();
        vector<vector<int>> rows(nrow);
        vector<vector<int>> cols(ncol);
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (picture[i][j] == 'B') {
                    rows[i].push_back(j);
                    cols[j].push_back(i);
                }
        
        int res = 0;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (picture[i][j] == 'B' 
                && rows[i].size() == cols[j].size() 
                && rows[i].size() == N) {
                    auto & currow = picture[i];
                    bool allsame = true;
                    for (auto c : cols[j]) {
                        if (c == i) continue;
                        if (picture[c] != currow) {
                            allsame = false;
                            break;
                        }
                    }
                    res += allsame;
                }
        return res;
    }
};
```


or with preexisting.

```c++
class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int N) {
        int nrow = picture.size(); if (!nrow) return 0;
        int ncol = picture[0].size();
        vector<vector<int>> rows(nrow);
        vector<vector<int>> cols(ncol);
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (picture[i][j] == 'B') {
                    rows[i].push_back(j);
                    cols[j].push_back(i);
                }
        
        int res = 0;
        vector<bool> visited_cols(ncol);
        for (int j = 0; j < ncol; j++)
            for (int i = 0; i < nrow; i++) {
                if (visited_cols[j]) break;
                if (picture[i][j] == 'B' 
                && rows[i].size() == cols[j].size() 
                && rows[i].size() == N) {
                    auto & currow = picture[i];
                    bool allsame = true;
                    for (auto c : cols[j]) {
                        if (c == i) continue;
                        if (picture[c] != currow) {
                            allsame = false;
                            break;
                        }
                    }
                    if (allsame) {
                        visited_cols[j] = true;;
                        res += N;
                    }
                }
            }
        return res;
    }
};
```