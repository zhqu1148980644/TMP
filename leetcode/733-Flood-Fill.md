An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input: 
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: 
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected 
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].

#### Solutions

- In summary, recolor all pixels with the same color as the source pixel that are connected(4 directions) with the source pixel to new color.

1. ##### dfs

```c++
class Solution {
public:
    void dfs(vector<vector<int>> & image, int x, int y, int oldcolor, int newColor) {
        if (x < 0 || y < 0 || x >= image.size() 
            || y >= image[0].size() || image[x][y] != oldcolor)
            return;
        image[x][y] = newColor;
        dfs(image, x + 1, y, oldcolor, newColor);
        dfs(image, x, y + 1, oldcolor, newColor);
        dfs(image, x - 1, y, oldcolor, newColor);
        dfs(image, x, y - 1, oldcolor, newColor);
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (image[sr][sc] == newColor) return image;
        dfs(image, sr, sc, image[sr][sc], newColor);
        return image;
    }
};
```

2. ##### bfs

```c++
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (image[sr][sc] == newColor) return image;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        int m = image.size(), n = image[0].size();

        int oldcolor = image[sr][sc];
        queue<int> q; q.push(node(sr, sc));
        while (!q.empty()) {
            int x = q.front() / n, y = q.front() % n;
            image[x][y] = newColor;
            q.pop();
            for (auto & d : dirs) {
                int i = x + d[0], j = y + d[1];
                if (i < 0 || j < 0 || i >= m 
                || j >= n || image[i][j] != oldcolor)
                    continue;
                q.push(node(i, j));
            }
        }
        return image;
    }
};
```

3. ##### union find