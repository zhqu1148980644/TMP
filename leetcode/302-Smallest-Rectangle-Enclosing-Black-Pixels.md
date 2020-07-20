An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

Example:

Input:
[
  "0010",
  "0110",
  "0100"
]
and x = 0, y = 2

Output: 6

#### Solutions

- Find four borders of the black region.

1. ##### bfs O(n)

```c++
class Solution {
public:
    int nrow, ncol;
    inline int node(int x, int y) {
        return x * ncol + y;
    }
    int minArea(vector<vector<char>>& image, int x, int y) {
        nrow = image.size(); ncol = image[0].size();
        int dirs[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        queue<int> q;
        q.push(node(x, y));

        int minx, miny, maxx, maxy;
        minx = miny = INT_MAX; maxx = maxy = INT_MIN;
        unordered_set<int> visited; visited.insert(q.front());

        while (!q.empty()) {
            int x = q.front() / ncol;
            int y = q.front() % ncol; q.pop();
            minx = min(minx, x); maxx = max(maxx, x);
            miny = min(miny, y); maxy = max(maxy, y);
            for (auto & d : dirs) {
                int i = x + d[0], j = y + d[1];
                if (i < 0 || j < 0 
                || i >= nrow || j >= ncol 
                || visited.count(node(i, j)) 
                || image[i][j] == '0')
                    continue;
                q.push(node(i, j));
                // must insert here, otherwise the same node could be inserted multiple times. thuse causing time limit exceed error.
                visited.insert(node(i, j));
            }
        }
        return (maxx - minx + 1) * (maxy - miny + 1);
    }
};
```


2. ##### dfs

```c++
class Solution {
public:
    int nrow, ncol;
    int minx = INT_MAX, miny = INT_MAX;
    int maxx = INT_MIN, maxy = INT_MIN;
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    unordered_set<int> visited;
    inline int node(int x, int y) {
        return x * ncol + y;
    }
    void dfs(vector<vector<char>> & image, int x, int y) {
        if (x < 0 || y < 0 
        || x >= nrow || y >= ncol 
        || image[x][y] == '0' 
        || visited.count(node(x, y)))
            return;
        visited.insert(node(x, y));
        minx = min(minx, x); maxx = max(maxx, x);
        miny = min(miny, y); maxy = max(maxy, y);
        for (auto & d : dirs) {
            int i = x + d[0], j = y + d[1];
            dfs(image, i, j);
        }
    }
    int minArea(vector<vector<char>>& image, int x, int y) {
        nrow = image.size(); ncol = image[0].size();
        dfs(image, x, y);
        return (maxx - minx + 1) * (maxy - miny + 1);
    }
};
```

3. ##### binary search O(mlog(n) + nlog(m))

- Use binary search to find the border. For example, search for the first column without `1` left the given `y`.
- Be careful when selecting the `lo` and `hi` in binary search.


```c++
class Solution {
public:
    int nrow, ncol;
    int search(vector<vector<char>>& image, int lo, int hi, bool col, bool blank2black) {
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            int i = 0;
            if (col)
                for (; i < nrow && image[i][mid] == '0'; i++);
            else
                for (; i < ncol && image[mid][i] == '0'; i++);
            bool blank = i == (col ? nrow : ncol);
            // blank2black means the blank region is at the lo side. ie: searching [0, y] or [0, x]
            if (blank == blank2black)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
    int minArea(vector<vector<char>>& image, int x, int y) {
        nrow = image.size(); ncol = image[0].size();
        // left to mid is using close mode: [0, nums.size() - 1], the returned lo is the first black boundary
        int left = search(image, 0, y, true, true);
        // mid to right is using open mode: [0, nums.size()], the returned lo is the index of the first black boundary, which could be equal to ncol.
        int right = search(image, y, ncol, true, false);
        int top = search(image, 0, x, false, true);
        int bottom = search(image, x, nrow, false, false);
        // [left, right) and [top, bottom) defines the rectangle of black pixels.
        return (bottom - top) * (right - left);
    }
};
```