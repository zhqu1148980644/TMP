---
title: Queue Reconstruction by Height
date: 2021-01-04
---
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

 
Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]


#### Solutions

1. ##### greedy approach.

- Check the official answer.
- The key point is: Inserting a person with lower height into the queue(at any place) would not change the results(number of gt person) of former inserted person.

```cpp
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n = people.size();
        if (!n) return {};
        // sort by [-h, k]
        sort(people.begin(), people.end(), [](auto & p1, auto & p2) {
            return p1[0] == p2[0] ? p1[1] < p2[1] : p1[0] > p2[0];
        });

        // start inserting person from the heighest to the lowest.
        list<vector<int>> q;
        for (auto & p : people) {
            auto it = q.begin();
            advance(it, p[1]);
            q.insert(it, move(p));
        }

        return {q.begin(), q.end()};
    }
};
```

2. ##### Other Solutions

- Starting from the shorted one.