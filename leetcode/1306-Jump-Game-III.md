#### Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.

Notice that you can not jump outside of the array at any time.

 

```
Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
```
 

#### Constraints:

- 1 <= arr.length <= 5 * 10^4
- 0 <= arr[i] < arr.length
- 0 <= start < arr.length

#### Solutions

1. ##### dfs with recursion

```c++
class Solution {
public:
    vector<int> visited;
    bool dfs(vector<int> & arr, int cur) {
        if (cur < 0 || cur >= arr.size() || visited[cur]++)
            return false;
        if (arr[cur] == 0) return true;
        return dfs(arr, cur + arr[cur]) || dfs(arr, cur - arr[cur]);
    }
    bool canReach(vector<int>& arr, int start) {
        visited = vector<int>(arr.size());
        return dfs(arr, start);
    }
};
```

2. ##### bfs with queue

```c++
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        if (arr[start] == 0) return true;
        queue<int> todos; todos.push(start);
        vector<int> visited(arr.size());
        visited[start]++;

        while (todos.size()) {
            auto cur = todos.front();
            todos.pop();
            int f = cur + arr[cur];
            int b = cur - arr[cur];
            if (f < arr.size() && !visited[f]++) {
                if (arr[f] == 0) return true;
                todos.push(f);
            }
            if (b >= 0 && !visited[b]++) {
                if (arr[b] == 0) return true;
                todos.push(b);
            }
        }

        return false;
    }
};
```