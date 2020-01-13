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

```c++
typedef pair<string, int> Vedio;
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {

        int curlevel = 0;
        queue<int> q; q.push(id);
        unordered_set<int> visited;
        visited.insert(id);

        while (curlevel < level && !q.empty()) {
            int size = q.size();
            while (size--) {
                auto cur = q.front(); q.pop();
                for (auto f : friends[cur])
                    // push to queue only if this friend is not visited before
                    if (!visited.count(f)) {
                        q.push(f);
                        // add to visited set
                        visited.insert(f);
                    }
            }
            curlevel++;
        }
        if (curlevel < level)
            return {};
        // count the frequency of each movie.
        unordered_map<string, int> counts;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            for (auto & vedio : watchedVideos[cur])
                counts[vedio]++;
        }

        vector<Vedio> vedios;
        for (const auto & it : counts)
            vedios.push_back(make_pair(it.first, it.second));
        // sort movies by count and lexicographical order
        sort(vedios.begin(), vedios.end(), [](Vedio & v1, Vedio & v2) {
            if (v1.second == v2.second)
                return v1.first < v2.first;
            else
                return v1.second < v2.second;
        });

        vector<string> res;
        for (auto & v : vedios)
            res.push_back(v.first);

        return res;
    }
};
```