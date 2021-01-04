---
title: Get Watched Videos by Your Friends
date: 2021-01-04
---
#### There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.

Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest. 

 

```
Example 1:

Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
Output: ["B","C"] 
Explanation: 
You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
Person with id = 1 -> watchedVideos = ["C"] 
Person with id = 2 -> watchedVideos = ["B","C"] 
The frequencies of watchedVideos by your friends are: 
B -> 1 
C -> 2

Example 2:

Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
Explanation: 
You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
```

 

#### Constraints:

-    n == watchedVideos.length == friends.length
-    2 <= n <= 100
-    1 <= watchedVideos[i].length <= 100
-    1 <= watchedVideos[i][j].length <= 8
-    0 <= friends[i].length < n
-    0 <= friends[i][j] < n
-    0 <= id < n
-    1 <= level < n
-    if friends[i] contains j, then friends[j] contains i


#### Solutions

1. ##### bfs

- Find all friends in the requested level by using bfs search with queue.
- Be carefully to filter friends that may be counted many times.

```cpp
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int curl = 0;
        queue<int> q; q.push(id);
        vector<int> visited(friends.size());
        visited[id] = 1;
        // get friend of this level by bfs
        while (curl < level && q.size()) {
            int size = q.size();
            while (size--) {
                auto cur = q.front(); q.pop();
                for (auto f : friends[cur])
                    if (!visited[f]++)
                        q.push(f);
            }
            curl++;
        }
        
        if (curl < level) return {};
        // counting vedioes
        unordered_map<string, int> count;
        while (q.size()) {
            int f = q.front(); q.pop();
            for (auto & vedio : watchedVideos[f])
                count[vedio]++;
        }

        // sorting by freq and lexigraphical order
        vector<pair<string, int>> vp;
        for (auto [v, c] : count)
            vp.emplace_back(move(v), c);
        sort(vp.begin(), vp.end(), [&](auto & p1, auto & p2) {
            return p1.second == p2.second
                ? p1.first < p2.first : p1.second < p2.second;
        });
        vector<string> res;
        for (auto & [s, c] : vp)
            res.push_back(move(s));

        return res;
    }
};
```