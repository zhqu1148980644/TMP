Given a picture consisting of black and white pixels, find the number of black lonely pixels.

The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

Example:
Input: 
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.
Note:
The range of width and height of the input 2D array is [1,500].

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int nrow = picture.size(); if (!nrow) return 0;
        int ncol = picture[0].size();
        vector<int> rows(nrow), cols(ncol);
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (picture[i][j] == 'B') {
                    rows[i]++; cols[j]++;
                }

        int res = 0;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (picture[i][j] == 'B' && rows[i] == 1 && cols[j] == 1)
                    res ++;
        
        return res;
    }
};
```